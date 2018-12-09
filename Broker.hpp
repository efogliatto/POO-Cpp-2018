#ifndef BROKER_HPP
#define BROKER_HPP

#include "Client.hpp"


class Broker {

    
private:

    
    // Registro de clientes
    
    std::vector<Client*> clients;


    // Registro de subscripciones
    
    std::multiset<Subscription*> subs_cache;

    std::mutex msub;
    


    // Registro de topicos retenidos

    std::multiset<RetainedTopic*> topics_cache;

    std::mutex mtop;


    // Mutex para registro de clientes

    std::mutex mreg;


public:


    // Registro de cliente
    
    BrokerOpsIF* registerClient( ClientOpsIF* c );


    // Nueva subscripcion

    void addSubscription( Subscription* sub );


    // Remocion de subscripcion

    void removeSubscription( Subscription* sub );


    // Actualizacion de topico retenido

    void updateRTopic( RetainedTopic* rt );
    

};


#endif // BROKER_HPP
