#include "Broker.hpp"

#include <iostream>

using namespace std;


BrokerOpsIF* Broker::registerClient( ClientOpsIF* c ) {


    lock_guard<mutex> lg(mreg);
        
    clients.push_back( new Client(c, *this) );

    return clients.back();

}
