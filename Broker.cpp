#include "Broker.hpp"

#include <iostream>

using namespace std;


BrokerOpsIF* Broker::registerClient( ClientOpsIF* c ) {

    // Falta Sincronizacion para registro de clientes
    
    clients.push_back( new Client(c) );

    return clients.back();

}
