#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>


#include "Crypt/Crypt.h"
#include "Socket/Socket.h"
using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::cin;

string ClientPubKey;
string ClientPriKey;


//Client side
int main(int argc, char *argv[])
{
    /***************************
    *       COMMAND LINE       *
    *  Usage: ip_address port  *
    ***************************/
    if(argc != 3)
    {
        cerr << "Usage: ip_address port" << endl; 
        exit(0); 
    } 
    //grab the IP address and port number 
    char *serverIp = argv[1];
    int port = atoi(argv[2]); 

    CLR_Socket_client Socket(serverIp, port);

    /*************************
    *       HANDSHAKE        *
    *************************/

    Socket.InitHandshake();
    InitCrypt();
    //Send key to the server
    Socket.SendKey(ClientPubKey);
    //Get key from the server
    string ServerKey;
    Socket.RecvKey(ServerKey);
    Socket.EndHandshake();

    cout<<"Handshake completed correctly"<<endl;

    /*************************
    *       CONNECTION       *
    *************************/

    if(Socket.Connect() < 0){
        cout<<"Error in the connection"<<endl;
        exit(-1);
    };

    cout<<"Connected correctly to the server!"<<endl;

    /*************************
    *       DIALOUGUE        *
    *************************/

    string data;
    while(true)
    {
        cout << ">";
        getline(cin, data);
        PrepareString(data, ServerKey);
        
        if(Socket.Send(data)){
            break;
        }
        if(Socket.Recv(data)){ //Actual message plus server key
            cout<<"Server has closed the session"<<endl;
            break;
        }

        //Get server key from data
        ExtractKey(data, ServerKey);
        DecryptString(data, ClientPriKey);
        cout << "Server: " << data << endl;
    }
    return 0;    
}