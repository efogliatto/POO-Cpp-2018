#ifndef QUEUE_HPP
#define QUEUE_HPP


// Cola FIFO "thread-safe" de tamanio maximo fijo


#include <memory>

#include <mutex>

#include <array>

#include <thread>


template<class T, size_t N>
class Queue {

private:

    // Contenedor primario
    
    std::array<T,N> data;


    // Indices

    unsigned int i;

    unsigned int j;

    mutable std::mutex m;


public:

    // Constructor por defecto
    
    Queue() : i(0), j(N-1) {}


    // Constructor copia

    Queue(const Queue& q) {

	std::lock_guard<std::mutex> lg(q.m);

	data = q.data;

    }


    // Insercion de elemento nuevo en el array
    
    void put(const T& val) {

	std::lock_guard<std::mutex> lg(m);

	std::cout << i%N << std:: endl;
	
	// data[i%N] = val;

	// ++i;

    }


    // Lectura de elemento mas viejo

    void get(T* val) {

	val = *data[j];
	
    }

};


#endif // QUEUE_HPP
