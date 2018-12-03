#include "SimPublisher.hpp"

using namespace std;

void SimPublisher::runSim() {

    
    BrokerOpsIF* brops = broker.registerClient(this);

    brops->sendMsg( ConnectMsg("user","pass") );

    
    // Esperar connack

    for( cierta_cantidad_de_pasos ) {

	this_thread::sleep_for( un_rato_random );

	PublishMsg m;

	fill m;

	brops->sendMsg(m);

    }

    brops->sendMsg( DisconnectMsg{} );
    

}
