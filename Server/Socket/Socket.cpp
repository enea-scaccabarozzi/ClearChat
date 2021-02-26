#include "Socket.h"

CLR_Socket_server::CLR_Socket_server(int port){
    bzero((char*)&servAddr, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(port);

    bytesRead = 0;
    bytesWritten = 0;
}

int CLR_Socket_server::InitHandshake(){
    serverSd = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSd < 0)
    {
        return -1;
    }
    //bind the socket to its local address
    int bindStatus = bind(serverSd, (struct sockaddr*) &servAddr, 
        sizeof(servAddr));
    if(bindStatus < 0)
    {
        return -2;
    }
    
    //listen for up to 5 requests at a time
    listen(serverSd, 5);

    socklen_t clieAddrSize = sizeof(clieAddr);
    
    clientSd = accept(serverSd, (sockaddr *)&clieAddr, &clieAddrSize);
    if(clientSd < 0)
    {
        return -1;
    }

    return 0;
}

int CLR_Socket_server::EndHandshake(){
    close(clientSd);
    close(serverSd);
    return 0;
}


int CLR_Socket_server::Open(){
    serverSd = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSd < 0)
    {
        return -1;
    }
    //bind the socket to its local address
    int bindStatus = bind(serverSd, (struct sockaddr*) &servAddr, 
        sizeof(servAddr));
    if(bindStatus < 0)
    {
        return -2;
    }
    
    //listen for up to 5 requests at a time
    listen(serverSd, 5);
    return 0;
}

int CLR_Socket_server::Listen(){
    socklen_t clieAddrSize = sizeof(clieAddr);
    
    clientSd = accept(serverSd, (sockaddr *)&clieAddr, &clieAddrSize);
    if(clientSd < 0)
    {
        return -1;
    }

    gettimeofday(&start, NULL);
    return 0;
}

void CLR_Socket_server::SendKey(std::string &key)
{
    //std::cout<<"Sending key..."<<std::endl;
    char msg[15000];
    memset(&msg, 0, sizeof(msg));//clear the buffer
    strcpy(msg, key.c_str());
    bytesWritten += send(clientSd, (char*)&msg, strlen(msg), 0);
    //std::cout<<"Sended key: "<<msg<<std::endl;
}

void CLR_Socket_server::RecvKey(std::string &key)
{
    //std::cout<<"Receiving key..."<<std::endl;
    key.clear();
    char msg[15000];
    memset(&msg, 0, sizeof(msg));//clear the buffer
    bytesRead += recv(serverSd, (char*)&msg, sizeof(msg), 0);
    key = msg;
    //std::cout<<"Recived key: "<<key << std::endl;
}

bool CLR_Socket_server::Recv(std::string &data){
    data.clear();
    char msg[1500];
    memset(&msg, 0, sizeof(msg));//clear the buffer
    bytesRead += recv(clientSd, (char*)&msg, sizeof(msg), 0);
    if(!strcmp(msg, "exit"))
    {
        return true;
    }
    data = msg;
    return false;
}

bool CLR_Socket_server::Send(std::string &data){
    char msg[1500];
    memset(&msg, 0, sizeof(msg)); //clear the buffer
    strcpy(msg, data.c_str());
    if(data == "exit")
    {
        //send to the client that server has closed the connection
        send(clientSd, (char*)&msg, strlen(msg), 0);
        return true;
    }
    //send the message to client
    bytesWritten += send(clientSd, (char*)&msg, strlen(msg), 0);
    return false;
}

CLR_Socket_server::~CLR_Socket_server(){
    struct timeval end;
    gettimeofday(&end, NULL);
    close(clientSd);
    close(serverSd);
    std::cout << "********Session********" << std::endl;
    std::cout << "Bytes written: " << bytesWritten << " Bytes read: " << bytesRead << std::endl;
    std::cout << "Elapsed time: " << (end.tv_sec- start.tv_sec) << " secs" << std::endl;
    std::cout << "Connection closed" << std::endl;
}

