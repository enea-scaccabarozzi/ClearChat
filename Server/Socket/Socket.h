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

class CLR_Socket_server{
    public:
    sockaddr_in servAddr;
    sockaddr_in clieAddr;
    int serverSd;
    int clientSd;
    size_t bytesRead; 
    size_t bytesWritten;
    struct timeval start;

    //Methods
    CLR_Socket_server(int port);
    ~CLR_Socket_server();
    int InitHandshake();
    int EndHandshake();
    int Open();
    int Listen();
    void SendKey(std::string &key);
    void RecvKey(std::string &key);
    bool Send(std::string &data);
    bool Recv(std::string &data);
};
