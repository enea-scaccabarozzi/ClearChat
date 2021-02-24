#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <netdb.h>
#include <cstring>
#include <iostream>



class CLR_Socket_client{
    public:
    sockaddr_in sendSockAddr;
    int clientSd;
    size_t bytesRead; 
    size_t bytesWritten;
    struct timeval start;

    //Methods
    CLR_Socket_client(const char* ServerIp, int port);
    ~CLR_Socket_client();
    int Connect();
    int InitHandshake();
    int EndHandshake();
    void SendKey(std::string &key);
    void RecvKey(std::string &key);
    bool Send(std::string &data);
    bool Recv(std::string &data);
};

