#ifndef SUBSCRIPTION_HPP
#define SUBSCRIPTION_HPP

#include "Message.hpp"

class Client;

struct Subscription {

    TopicName topic;

    Client* owner;

};

#endif // SUBSCRIPTION_HPP
