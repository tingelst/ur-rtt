#include "URRealTime-component.hpp"
#include <rtt/Component.hpp>
#include <rtt/Activity.hpp>
#include <iostream>
#include <vector>

URRealTime::URRealTime(std::string const& name) :
    TaskContext(name),
    host("127.0.0.1"),
    port(5002){
  std::cout << "URRealTime constructed!" <<std::endl;
}

bool URRealTime::configureHook(){
    createSocket();
    std::cout << "URRealTime configured!" <<std::endl;
    return true;
}

bool URRealTime::startHook(){
  std::cout << "URRealTime started!" <<std::endl;
  return true;
}

void URRealTime::updateHook(){
    recvPosition();

    reply_packet_.q[2] += 0.005;
    // here comes the position manipulation

    sendPosition();
    this->getActivity()->trigger();
  //std::cout << "URRealTime executes updateHook !" <<std::endl;
}

void URRealTime::stopHook() {
  std::cout << "URRealTime executes stopping !" <<std::endl;
}

void URRealTime::cleanupHook() {
  std::cout << "URRealTime cleaning up !" <<std::endl;
}


int URRealTime::createSocket(){
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
        std::cout << "Socket error" << std::endl;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(host);
    servaddr.sin_port = htons(port);
    status = connect(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr));
    if (status == -1)
        std::cout << "Connection error" << std::endl;
    return 0;
}

int URRealTime::sendPosition(){
    send(sockfd, (void*)&reply_packet_, sizeof(reply_packet_), 0);
    return 0;
}

int URRealTime::recvPosition(){
    ssize_t n_bytes;
    n_bytes = recv(sockfd, buf, BUFSIZE, 0);
    reply_packet_.id = *(char*) &buf[0];
    reply_packet_.cycle_number = *(unsigned int*) &buf[1];
    // extract actual joint positions
    // todo: rewrite and remove for loop if possible
    for (unsigned int i = 0; i < 6; i++){
         reply_packet_.q[i] = *(double*) &buf[5 + (sizeof(double) * i)];
    }
    return 0;
}

/*
 * Using this macro, only one component may live
 * in one library *and* you may *not* link this library
 * with another component library. Use
 * ORO_CREATE_COMPONENT_TYPE()
 * ORO_LIST_COMPONENT_TYPE(URRealTime)
 * In case you want to link with another library that
 * already contains components.
 *
 * If you have put your component class
 * in a namespace, don't forget to add it here too:
 */
ORO_CREATE_COMPONENT(URRealTime)
