#ifndef RETAINEDTOPIC_HPP
#define RETAINEDTOPIC_HPP

#include "Message.hpp"

class Client;

struct RetainedTopic {

    TopicName topic;

    TopicValue value;

    Client* owner;

};

#endif // RETAINEDTOPIC_HPP
