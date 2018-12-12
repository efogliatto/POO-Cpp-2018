#ifndef BROKER_HPP
#define BROKER_HPP

#include "Client.hpp"

#include "lockedVar.hpp"


class Broker {

    
private:

    
    // Registro de clientes
    
    std::vector<Client*> clients;


    // Registro de subscripciones
    
    // std::multiset<Subscription*> subs_cache;

    // std::mutex msub;

    lockedVar< std::multiset<Subscription*> > subs_cache;    
    


    // Registro de topicos retenidos

    // std::multiset<RetainedTopic*> topics_cache;

    // std::mutex mtop;

    lockedVar< std::multiset<RetainedTopic*> > topics_cache;


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
    

    // Envio de topico a subscriptores

    void sendTopic( const TopicName& name, const TopicValue& val );

    
};


#endif // BROKER_HPP
