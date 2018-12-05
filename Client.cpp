#include "Client.hpp"

#include <iostream>

using namespace std;


Client::Client(ClientOpsIF* c) {

    cif = c;

}



void Client::sendMsg( const Message& msg ) {

    
    // Incorporacion a la cola de mensages
    
    thread t( &myqueue::put, &recvQueue, msg.clone() );
    
    t.join();
    
    
}
