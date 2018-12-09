#include "Message.hpp"

using namespace std;



const Message::Type Message::getType() const {  return type; }


ConnectMsg::ConnectMsg(const string& user, const string& pswd)
    : username(user),
      password(pswd)  {

    type = Type::CONNECT;

}


ConnectMsg* ConnectMsg::clone() const {   return new ConnectMsg(*this);  }

const string& ConnectMsg::user() const { return username; };

const string& ConnectMsg::pswd() const { return password; };



ConnAckMsg::ConnAckMsg() { type = Type::CONNACK; }

ConnAckMsg* ConnAckMsg::clone() const {  return new ConnAckMsg(*this);  }



PublishMsg::PublishMsg(const TopicName& tn, const TopicValue& tv, const bool r)
    : topic(tn), value(tv), retain(r)  {

    type = Type::PUBLISH;

}

PublishMsg* PublishMsg::clone() const {  return new PublishMsg(*this);  }

const TopicName& PublishMsg::getTopic() const { return topic; }

const TopicValue& PublishMsg::getValue() const { return value; }

const bool& PublishMsg::isRetained() const { return retain; }



SubscribeMsg::SubscribeMsg() { type = Type::SUBSCRIBE; }

SubscribeMsg* SubscribeMsg::clone() const {  return new SubscribeMsg(*this);  }

const TopicName& SubscribeMsg::getTopic() const { return topic; }



UnsubscribeMsg::UnsubscribeMsg() { type = Type::UNSUBSCRIBE; }

UnsubscribeMsg* UnsubscribeMsg::clone() const {  return new UnsubscribeMsg(*this);  }

const TopicName& UnsubscribeMsg::getTopic() const { return topic; }


DisconnectMsg::DisconnectMsg() { type = Type::DISCONNECT; }

DisconnectMsg* DisconnectMsg::clone() const {  return new DisconnectMsg(*this);  }
