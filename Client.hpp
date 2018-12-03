#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "BrokerOpsIF.hpp"

#include "ClientOpsIF.hpp"

#include "Subscription.hpp"

#include "RetainedTopic.hpp"

#include <thread>


class Client : public BrokerOpsIF {

private:

    thread th;

    ClientOpsIF *cif;

    std::vector<Subscription*> subscriptions;

    std::vector<RetainedTopic*> topics;

    std::deque<Message*> recvQueue;


public:

    Client(ClientOpsIF* c);

    void sendMsg( const Message& m );

};

#endif // CLIENT_HPP
