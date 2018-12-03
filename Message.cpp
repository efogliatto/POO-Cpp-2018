#include "Message.hpp"

using namespace std;


// Message::Message() {}

// Message::~Message() {}


// Message* Message::clone() {

//     return new Message(this);

// }



ConnectMsg::ConnectMsg(const string& user, const string& pswd)
    : username(user),
      password(pswd)  {

    type = Type::CONNECT;

}




ConnectMsg* ConnectMsg::clone() {

    return new ConnectMsg(*this);

}

// Message* ConnectMsg::clone() {}



