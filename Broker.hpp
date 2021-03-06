#ifndef BROKER_HPP
#define BROKER_HPP

#include "Client.hpp"

#include "lockedVar.hpp"


class Broker {

    
private:

    
    // Registro de clientes   

    lockedVar< std::multiset<Client*> > clients;
    

    // Registro de subscripciones    

    lockedVar< std::multiset<Subscription*> > subs_cache;    
    

    // Registro de topicos retenidos

    lockedVar< std::multiset<RetainedTopic*> > topics_cache;


    // Max number of clients

    const int maxClients;


public:


    // Constructor

    Broker();
    
    Broker(const int& maxc);


    // Registro de cliente
    
    BrokerOpsIF* registerClient( ClientOpsIF* c );


    // Nueva subscripcion

    void addSubscription( Subscription* sub );


    // Remocion de subscripcion

    void removeSubscription( Subscription* sub );


    // Actualizacion de topico retenido

    void updateRTopic( RetainedTopic* rt );


    // Remocion de subscripcion

    void removeRetainedTopic( RetainedTopic* rt );    
    

    // Envio de topico a subscriptores

    void sendTopic( const TopicName& name, const TopicValue& val );


    // Solicitud de conexion

    void connReq( Client* c );


    // Remocion de cliente

    void removeClient( Client* c );

    
};


#endif // BROKER_HPP
