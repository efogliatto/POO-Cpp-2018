#include "Message.hpp"

using namespace std;



Message::Type Message::getType() const {  return type; }


ConnectMsg::ConnectMsg(const string& user, const string& pswd)
    : username(user),
      password(pswd)  {

    type = Type::CONNECT;

}


ConnectMsg* ConnectMsg::clone() const {   return new ConnectMsg(*this);  }

const string& ConnectMsg::user() { return username; };

const string& ConnectMsg::pswd() { return password; };



ConnAckMsg::ConnAckMsg() { type = Type::CONNACK; }

ConnAckMsg* ConnAckMsg::clone() const {  return new ConnAckMsg(*this);  }



PublishMsg::PublishMsg(const TopicName& tn, const TopicValue& tv, const bool r)
    : topic(tn), value(tv), retain(r)  {

    type = Type::PUBLISH;

}

PublishMsg* PublishMsg::clone() const {  return new PublishMsg(*this);  }



SubscribeMsg::SubscribeMsg() { type = Type::SUBSCRIBE; }

SubscribeMsg* SubscribeMsg::clone() const {  return new SubscribeMsg(*this);  }



UnsubscribeMsg::UnsubscribeMsg() { type = Type::UNSUBSCRIBE; }

UnsubscribeMsg* UnsubscribeMsg::clone() const {  return new UnsubscribeMsg(*this);  }



DisconnectMsg::DisconnectMsg() { type = Type::DISCONNECT; }

DisconnectMsg* DisconnectMsg::clone() const {  return new DisconnectMsg(*this);  }
