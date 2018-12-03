#include "Message.hpp"

using namespace std;



Message::Type Message::getType() const {

    return type;

}


ConnectMsg::ConnectMsg(const string& user, const string& pswd)
    : username(user),
      password(pswd)  {

    type = Type::CONNECT;

}


ConnectMsg* ConnectMsg::clone() {

    return new ConnectMsg(*this);

}


ConnAckMsg* ConnAckMsg::clone() {

    return new ConnAckMsg(*this);

}


PublishMsg* PublishMsg::clone() {

    return new PublishMsg(*this);

}


SubscribeMsg* SubscribeMsg::clone() {

    return new SubscribeMsg(*this);

}


UnsubscribeMsg* UnsubscribeMsg::clone() {

    return new UnsubscribeMsg(*this);

}


DisconnectMsg* DisconnectMsg::clone() {

    return new DisconnectMsg(*this);

}
