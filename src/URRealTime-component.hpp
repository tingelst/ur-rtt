#ifndef OROCOS_URREALTIME_COMPONENT_HPP
#define OROCOS_URREALTIME_COMPONENT_HPP

// orocos includes
#include <rtt/RTT.hpp>

// socket includes
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUFSIZE 1024

class URRealTime : public RTT::TaskContext{
  public:
    URRealTime(std::string const& name);
    bool configureHook();
    bool startHook();
    void updateHook();
    void stopHook();
    void cleanupHook();
  private:
    int status;
    int sockfd, n;
    char* host;
    int port;
    char buf[BUFSIZE];
    struct sockaddr_in servaddr;

    // output ports
    RTT::OutputPort<std::vector<double> > q_from_robot;
    RTT::OutputPort<std::vector<double> > qdot_from_robot;
    // input ports
    RTT::InputPort<std::vector<double> > q_to_robot;


    // joint vectors
    std::vector<double> q_act_std; // actual joint position vector
    std::vector<double> qdot_act_std; //actual joint velocity vector
    std::vector<double> q_std; //desired joint vector

    // removes memory padding at compile time and ensures that
    // sizeof(outPacketStruct) = 53
    #pragma pack(1)
    typedef struct{
        char id;
        unsigned int cycle_number;
        double q[6];
    } ReplyPacket;
    #pragma pack()
    ReplyPacket reply_packet_;

    // socket methods
    int createSocket();
    int sendPosition();
    int recvPosition();
};
#endif
