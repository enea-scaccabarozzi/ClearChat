#include "Socket.h"


CLR_Socket_client::CLR_Socket_client(const char* ServerIp, int port){
    struct hostent* host = gethostbyname(ServerIp);  
    bzero((char*)&sendSockAddr, sizeof(sendSockAddr)); 
    sendSockAddr.sin_family = AF_INET; 
    sendSockAddr.sin_addr.s_addr = 
        inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));
    sendSockAddr.sin_port = htons(port);

    bytesRead = 0;
    bytesWritten = 0;
}

int CLR_Socket_client::InitHandshake(){
    clientSd = socket(AF_INET, SOCK_STREAM, 0);
    return connect(clientSd, (sockaddr*) &sendSockAddr, sizeof(sendSockAddr));
}

int CLR_Socket_client::EndHandshake(){
    close(clientSd);
    return 0;
}


int CLR_Socket_client::Connect(){
    gettimeofday(&start, NULL);
    clientSd = socket(AF_INET, SOCK_STREAM, 0);
    return connect(clientSd, (sockaddr*) &sendSockAddr, sizeof(sendSockAddr));
}

void CLR_Socket_client::SendKey(std::string &key)
{
    //std::cout<<"Sending key..."<<std::endl;
    char msg[15000];
    memset(&msg, 0, sizeof(msg));//clear the buffer
    strcpy(msg, key.c_str());
    bytesWritten += send(clientSd, (char*)&msg, strlen(msg), 0);
    //std::cout<<"Sended key: "<<msg<<std::endl;
}

void CLR_Socket_client::RecvKey(std::string &key)
{
    //std::cout<<"Receiving key..."<<std::endl;
    key.clear();
    char msg[15000];
    memset(&msg, 0, sizeof(msg));//clear the buffer
    bytesRead += recv(clientSd, (char*)&msg, sizeof(msg), 0);
    key = msg;
    //std::cout<<"Recived key: "<<key<<std::endl;
}

bool CLR_Socket_client::Send(std::string &data){
    char msg[15000];
    memset(&msg, 0, sizeof(msg));//clear the buffer
    strcpy(msg, data.c_str());
    if(data == "exit")
    {
        send(clientSd, (char*)&msg, strlen(msg), 0);
        return true;
    }
    bytesWritten += send(clientSd, (char*)&msg, strlen(msg), 0);

    return false; 
}

bool CLR_Socket_client::Recv(std::string &data){
    data.clear();
    char msg[15000];
    memset(&msg, 0, sizeof(msg));//clear the buffer
    bytesRead += recv(clientSd, (char*)&msg, sizeof(msg), 0);
    if(!strcmp(msg, "exit"))
    {
        return true;
    }
    data = msg;
    return false;
}

CLR_Socket_client::~CLR_Socket_client(){
    struct timeval end;
    gettimeofday(&end, NULL);
    close(clientSd);
    std::cout << "********Session********" << std::endl;
    std::cout << "Bytes written: " << bytesWritten << " Bytes read: " << bytesRead << std::endl;
    std::cout << "Elapsed time: " << (end.tv_sec- start.tv_sec) << " secs" << std::endl;
    std::cout << "Connection closed" << std::endl;
}
