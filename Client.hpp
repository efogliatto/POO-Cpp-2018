#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "BrokerOpsIF.hpp"

#include "ClientOpsIF.hpp"

#include "Subscription.hpp"

#include "RetainedTopic.hpp"

#include <thread>

#include <vector>

#include <set>

#include "Queue.hpp"

#include "lockedVar.hpp"


using myqueue = Queue<Message*, 2>;

class Broker;

#include "Broker.hpp"



class Client : public BrokerOpsIF {

    
private:


    // Referencia al broker
    
    Broker& broker;


    // Thread para despacho de mensajes durante la vida del Client
    
    std::thread th;


    // Puntero a la interfase
    
    lockedVar<ClientOpsIF*> cif;


    // Subscripciones
    
    std::multiset<Subscription*> subscriptions;


    // Topicos

    std::multiset<RetainedTopic*> topics;


    // Cola de mensajes

    myqueue recvQueue;


    // Nombre de usuario

    std::string user;


    // Procesamiento de mensajes en general
    
    void dispatch();


    // Procesamiento de mensajes tipo PUBLISH

    void processPublish( const Message* msg );


    // Procesamiento de mensajes tipo CONNECT

    void processConnect( const Message* msg );


    // Procesamiento de mensajes tipo DISCONNECT

    void processDisconnect( const Message* msg );    


    // Procesamiento de mensajes tipo SUBSCRIBE

    void processSubscribe( const Message* msg );
    

    // Procesamiento de mensajes tipo UNSUBSCRIBE

    void processUnsubscribe( const Message* msg );


public:


    // Constructor
    
    Client( ClientOpsIF* c, Broker& br );


    // Destructor
    
    ~Client();


    // Envio de mensaje al broker

    void sendMsg( const Message& msg );


    // Referencia al cif

    unique_access<ClientOpsIF*> CIF() { return unique_access<ClientOpsIF*>(cif); }    

    
    

};

#endif // CLIENT_HPP
