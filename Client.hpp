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



class Client : public BrokerOpsIF {

private:

    std::thread th;

    ClientOpsIF* cif;

    std::vector<Subscription*> subscriptions;

    std::vector<RetainedTopic*> topics;

    myqueue recvQueue;

    void dispatch();


public:

    Client(ClientOpsIF* c);

    ~Client();

    void sendMsg( const Message& msg );

};

#endif // CLIENT_HPP
