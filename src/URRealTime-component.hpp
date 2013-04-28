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
