#ifndef TOPICSLIST_HPP
#define TOPICSLIST_HPP

/*
Topicos admisibles para subscripcion/publicacion

Seleccion aleatoria
 */

#include <string>

#include <vector>

#include <random>


class TopicsList {

private:

    std::vector< std::string > topics = { "Temperatura/Techo",
					  "Temperatura/Piso",
					  "Temperatura/Exterior",
					  "Velocidad/Viento" };    

public:

    const std::string randomTopic() const {
	
	std::random_device rd;

	std::mt19937 rng(rd());
       
	std::uniform_int_distribution<int> uni(0, topics.size() - 1);

	return topics[ uni(rng) ];

    }
    
};


#endif // TOPICSLIST_HPP
