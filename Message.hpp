#ifndef MESAGGE_HPP
#define MESAGGE_HPP

#include <string>

using TopicName = std::string;
using TopicValue = std::string;


class Message {

public:

        
    enum class Type { CONNECT, CONNACK, PUBLISH, SUBSCRIBE, UNSUBSCRIBE, DISCONNECT };

    Type getType() const;

    
    virtual Message *clone() = 0;

    virtual ~Message() = default;


protected:

    Type type;    

};





class ConnectMsg : public Message {

public:

    ConnectMsg(const std::string& user, const std::string& pswd);

    virtual ConnectMsg* clone() override;
    
    
private:

    std::string username;

    std::string password;

};






class ConnAckMsg : public Message {

public:

    enum class Status { CONNECTION_OK, LOGIN_ERROR };

    virtual ConnAckMsg* clone() override;
    

private:

    Status status;

};




class PublishMsg : public Message {

public:

    virtual PublishMsg* clone() override;

    
private:

    TopicName topic;

    TopicValue value;

    bool retain;
    
};




class SubscribeMsg : public Message {

public:
    
    virtual SubscribeMsg* clone() override;

};



class UnsubscribeMsg : public Message {

public:
    
    virtual UnsubscribeMsg* clone() override;

};



class DisconnectMsg : public Message {

public:
    
    virtual DisconnectMsg* clone() override;

};




#endif // MESAGGE_HPP
