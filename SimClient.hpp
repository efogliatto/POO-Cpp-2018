#ifndef SIMCLIENT_HPP
#define SIMCLIENT_HPP

#include "ClientOpsIF.hpp"

#include "Broker.hpp"

#include <thread>


class SimClient : public ClientOpsIF {

protected:

    
    // Own thread
    
    std::thread simth;

    
    // Referencia al broker
    
    Broker& broker;


    // Nombre de usuario (usado para mensajes de recepcion)

    std::string username;


    // Estado de la conexion

    lockedVar<ConnAckMsg::Status> status;


    // Variable de condicion para esperar la confirmacion de conexion

    std::condition_variable connection;



    // Interfase para simulacion

    virtual void runSim() = 0;


    // Procesamiento de mensaje ConnAck

    void proccessConnAck( const Message& m );
    

    
public:

    SimClient(Broker& b);

    SimClient(Broker& b, const std::string& name);

    void start();

    void recvMsg(const Message& m);

    void waitConnAck();

};


#endif // SIMCLIENT_HPP
