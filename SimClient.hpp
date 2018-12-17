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

    
    // Interfase para simulacion

    virtual void runSim() = 0;


    // Procesamiento de mensaje ConnAck

    void proccessConnAck( const Message& m );
    

    
public:


    // Constructores

    SimClient(Broker& b);

    SimClient(Broker& b, const std::string& name);


    // Comienzo de simulacion
    
    void start();


    // Recepcion de mensajes. Interfase comun para SimPublisher y SimSubscriber

    void recvMsg(const Message& m);


    // Tiempo de espera para conexion.
    // Espera un tiempo fijo por la conexion. Si el estado sigue siendo UNDEFINED despues de ese tiempo, de mensaje de error

    void waitConnAck();

};


#endif // SIMCLIENT_HPP
