#include "SimClient.hpp"

#include <iostream>

using namespace std;



SimClient::SimClient(Broker& b)
    : broker(b),
      username("undefined") {

    
    unique_access<ConnAckMsg::Status> stAccess( status );

    *stAccess = ConnAckMsg::Status::UNDEFINED;

}


SimClient::SimClient(Broker& b, const std::string& name)
    : broker(b),
      username(name) {

    unique_access<ConnAckMsg::Status> stAccess( status );

    *stAccess = ConnAckMsg::Status::UNDEFINED;

}



void SimClient::start() {
    
    simth = std::move( thread(&SimClient::runSim, this) );

    simth.join();
    
}



void SimClient::recvMsg(const Message& m) {

    
    const Message::Type mtype = m.getType();

    const PublishMsg* pmsg;


    switch( mtype ) {


    case Message::Type::PUBLISH:

    	pmsg = dynamic_cast<const PublishMsg*>(&m);

    	cout << pmsg->getTopic() + " [" + username + "]" + "\n";

    	break;

	
    case Message::Type::CONNACK:

	proccessConnAck(m);       

	break;
	    

    default:

    	break;

	    
    }

}





// Procesamiento de mensaje ConnAck

void SimClient::proccessConnAck( const Message& m ) {

    const ConnAckMsg* cmsg = dynamic_cast<const ConnAckMsg*>(&m);

    unique_access<ConnAckMsg::Status> stAccess( status );

    *stAccess = cmsg->getStatus();

}



// Espera a cambio del estado de la conexion

void SimClient::waitConnAck() {

    this_thread::sleep_for( chrono::seconds(1) );

    unique_access<ConnAckMsg::Status> stAccess( status );

    switch( *stAccess ) {

    case ConnAckMsg::Status::CONNECTION_OK:

	cout << "Usuario [" + username + "] conectado satisfactoriamente\n";

	break;
	
    case ConnAckMsg::Status::LOGIN_ERROR:

	cout << "Error de conexion para usuario [" + username + "]. Usuario o contraseña incorrectos\n";
	
	break;

    case ConnAckMsg::Status::UNREG_CLIENT:

	cout << "Error de conexion para usuario [" + username + "]. Usuario no registrado\n";
	
	break;	

    case ConnAckMsg::Status::UNDEFINED:

	cout << "Tiempo máximo de espera superado para usuario [" + username + "]. Fallo de conexión\n";
	
	break;	
	
    }

}
