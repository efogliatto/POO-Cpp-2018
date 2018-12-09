#ifndef BROKER_HPP
#define BROKER_HPP

#include "Client.hpp"


class Broker {

    
private:

    
    // Registro de clientes
    
    std::vector<Client*> clients;


    // Registro de subscripciones
    
    std::vector<Subscription*> subs_cache;

    std::mutex msub;


    // Registro de topicos retenidos

    std::vector<RetainedTopic*> topics_cache;


    // Mutex para registro de clientes

    std::mutex mreg;


public:


    // Registro de cliente
    
    BrokerOpsIF* registerClient( ClientOpsIF* c );


    // Nueva subscripcion

    void addSubscription( const Subscription& sub );
    

};


#endif // BROKER_HPP
