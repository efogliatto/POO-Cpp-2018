#include "SimClient.hpp"

#include <iostream>

using namespace std;



SimClient::SimClient(Broker& b)
    : broker(b),
      status( ConnAckMsg::Status::LOGIN_ERROR ) {}



void SimClient::start() {
    
    simth = std::move( thread(&SimClient::runSim, this) );

    simth.join();
    
}



void SimClient::recvMsg(const Message& m) {

    
    const Message::Type mtype = m.getType();

    const PublishMsg* pmsg;

    const ConnAckMsg* cmsg;


    switch( mtype ) {


    case Message::Type::PUBLISH:

    	pmsg = dynamic_cast<const PublishMsg*>(&m);

    	cout << pmsg->getTopic() + " [" + username + "]" + "\n";

    	break;

	
    case Message::Type::CONNACK:

	cmsg = dynamic_cast<const ConnAckMsg*>(&m);

	status = cmsg->getStatus();

	break;
	    

    default:

    	break;

	    
    }

}
