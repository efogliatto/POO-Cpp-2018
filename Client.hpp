#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "BrokerOpsIF.hpp"

#include "ClientOpsIF.hpp"

#include "Subscription.hpp"

#include "RetainedTopic.hpp"

#include <thread>

#include <vector>

#include "Queue.hpp"


using myqueue = Queue<Message*, 2>;


class Broker;



class Client : public BrokerOpsIF {

    
private:

    Broker& broker;

    std::thread th;

    ClientOpsIF* cif;

    std::vector<Subscription*> subscriptions;

    std::vector<RetainedTopic*> topics;

    myqueue recvQueue;

    std::string user;


    // Procesamiento de mensajes en general
    
    void dispatch();


    // Procesamiento de mensajes tipo PUBLISH

    void processPublish( const Message* msg );


    // Procesamiento de mensajes tipo CONNECT

    void processConnect( const Message* msg );


    // Procesamiento de mensajes tipo SUBSCRIBE

    void processSubscribe( const Message* msg );
    

    // Procesamiento de mensajes tipo UNSUBSCRIBE

    void processUnsubscribe( const Message* msg );


public:

    Client( ClientOpsIF* c, Broker& br );

    ~Client();

    void sendMsg( const Message& msg );
    

};

#endif // CLIENT_HPP
