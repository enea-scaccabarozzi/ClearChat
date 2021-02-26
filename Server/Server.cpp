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

string ServerPubKey;
string ServerPriKey;


//Server side
int main(int argc, char *argv[])
{
    /***************************
    *       COMMAND LINE       *
    *        Usage: port       *
    ***************************/
    if(argc != 2)
    {
        cerr << "Usage: port" << endl;
        exit(0);
    }
    //grab the port number
    int port = atoi(argv[1]);

    cout<<"Waiting for a client to connect..."<<endl;
    
    CLR_Socket_server Socket(port);

    /*************************
    *       HANDSHAKE        *
    *************************/

    if(Socket.InitHandshake() < 0){
        cerr<<"Unable to init handshake"<<endl;
        exit(-1);
    }
    InitCrypt();
    //Ricevi chiave client
    string ClientKey;
    Socket.RecvKey(ClientKey);
    //Manda chiave server
    Socket.SendKey(ServerPubKey);
    Socket.EndHandshake();

    cout<<"Handshake completed correctly"<<endl;

    /*************************
    *         OPENING        *
    *       AND BINDING      *
    *************************/
    if(Socket.Open() < 0){
        cerr<<"Unable to open and bind the socket"<<endl;
        exit(-1);
    }

    /*************************
    *       CONNECTION       *
    *************************/

    if(Socket.Listen() < 0){
        cerr<<"Unable to accept incoming connection"<<endl;
        exit(-1);
    }
    
    cout << "Connected with client!" << endl;

    /*************************
    *       DIALOUGUE        *
    *************************/

    string data;
    while(1)
    {
        cout << "Awaiting client response..." << endl;
        if(Socket.Recv(data)){
            cout<<"Client has closed the session"<<endl;
            break;
        }
        ExtractKey(data, ClientKey);
        DecryptString(data, ServerPriKey);
        cout << "Client: " << data << endl;

        cout << ">";
        getline(cin, data);
        PrepareString(data, ClientKey);

        if(Socket.Send(data)){
            break;
        }
    }
    return 0;   
}
