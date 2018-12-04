#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "BrokerOpsIF.hpp"

#include "ClientOpsIF.hpp"

#include "Subscription.hpp"

#include "RetainedTopic.hpp"

#include <thread>

#include <vector>

#include <deque>



class Client : public BrokerOpsIF {

private:

    std::thread th;

    ClientOpsIF* cif;

    std::vector<Subscription*> subscriptions;

    std::vector<RetainedTopic*> topics;

    std::deque<Message*> recvQueue;


public:

    Client(ClientOpsIF* c);

    void sendMsg( const Message& msg );

};

#endif // CLIENT_HPP
