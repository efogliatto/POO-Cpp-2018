#include "Client.hpp"

#include "iostream"

using namespace std;


Client::Client(ClientOpsIF* c) {

    cif = c;

}



void Client::sendMsg( const Message& msg ) {
   
    recvQueue.push_back( msg.clone() );    
    
}
