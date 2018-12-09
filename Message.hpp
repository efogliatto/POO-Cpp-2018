#ifndef MESAGGE_HPP
#define MESAGGE_HPP

#include <string>

using TopicName = std::string;
using TopicValue = std::string;


class Message {

public:

        
    enum class Type { CONNECT, CONNACK, PUBLISH, SUBSCRIBE, UNSUBSCRIBE, DISCONNECT };

    const Type getType() const;

    
    virtual Message *clone() const = 0;

    virtual ~Message() = default;


protected:

    Type type;    

};





class ConnectMsg : public Message {

public:

    ConnectMsg(const std::string& user, const std::string& pswd);

    virtual ConnectMsg* clone() const;

    const std::string& user() const;

    const std::string& pswd() const;    
    
    
private:

    std::string username;

    std::string password;

};






class ConnAckMsg : public Message {

public:

    ConnAckMsg();

    enum class Status { CONNECTION_OK, LOGIN_ERROR };

    virtual ConnAckMsg* clone() const;
    

private:

    Status status;

};




class PublishMsg : public Message {

public:

    PublishMsg(const TopicName& tn, const TopicValue& tv, const bool r = true);
    
    virtual PublishMsg* clone() const;

    const TopicName& getTopic() const;

    const TopicValue& getValue() const;

    const bool& isRetained() const;    

    
private:

    TopicName topic;

    TopicValue value;

    bool retain;
    
};




class SubscribeMsg : public Message {

public:

    SubscribeMsg(const TopicName& tn);
    
    virtual SubscribeMsg* clone() const;

    const TopicName& getTopic() const;
    

private:

    TopicName topic;

};



class UnsubscribeMsg : public Message {

public:

    UnsubscribeMsg(const TopicName& tn);
    
    virtual UnsubscribeMsg* clone() const;

    const TopicName& getTopic() const;


private:

    TopicName topic;    

};



class DisconnectMsg : public Message {

public:

    DisconnectMsg();
    
    virtual DisconnectMsg* clone() const;

};




#endif // MESAGGE_HPP
