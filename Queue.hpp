#ifndef QUEUE_HPP
#define QUEUE_HPP


// Cola FIFO "thread-safe" de tamanio maximo fijo


#include <memory>

#include <mutex>

#include <array>

#include <thread>

#include <condition_variable>

#include <iostream>



template<class T, size_t N>
class Queue {

private:

    // Contenedor primario
    
    std::array<T,N> data;


    // Indices

    int front;

    int rear;


    // Variables para sincronizacion

    mutable std::mutex m;

    std::condition_variable full_cond;

    std::condition_variable empty_cond;



    // Deteccion de Queue vacia. Sin lock

    const bool empty() const;


    // Deteccion de Queue llena

    const bool full() const;
    

public:

    // Constructor por defecto
    
    Queue();


    // Constructor copia

    Queue(const Queue& q);


    // Deteccion de Queue vacia

    const bool isEmpty() const;


    // Deteccion de Queue llena

    const bool isFull() const;
    
    
    // Insercion de elemento nuevo en el array
    
    void put(const T& val);


    // Lectura de copia elemento mas viejo

    void get(T* val);

};




// Constructor por defecto

template<class T, size_t N>
Queue<T,N>::Queue()
    : front(-1),
      rear(-1) {}


// Constructor copia

template<class T, size_t N>
Queue<T,N>::Queue(const Queue& q) {

    std::lock_guard<std::mutex> lg(q.m);

    data = q.data;

}



// Deteccion de Queue vacia

template<class T, size_t N>
const bool Queue<T,N>::empty() const {

    // std::lock_guard<std::mutex> lg(m);

    return (front == -1) ? true : false;

}


// Deteccion de Queue vacia

template<class T, size_t N>
const bool Queue<T,N>::isEmpty() const {

    std::lock_guard<std::mutex> lg(m);

    return empty();

}


// Deteccion de Queue llena

template<class T, size_t N>
const bool Queue<T,N>::full() const {

    // std::lock_guard<std::mutex> lg(m);

    bool isFull(false);

    if( (front == 0)  &&  (rear == N - 1) )
	isFull = true;

    if( front == rear + 1 )
	isFull = true;
	
    return isFull;

}



// Deteccion de Queue llena

template<class T, size_t N>
const bool Queue<T,N>::isFull() const {

    std::lock_guard<std::mutex> lg(m);
	
    return full();

}


    
// Insercion de elemento nuevo en el array

template<class T, size_t N>
void Queue<T,N>::put(const T& val) {

    
    std::unique_lock<std::mutex> lg(m);

    
    // Espera por la variable de condicion full_cond (si esta llena la cola, vuelve a abrirse con Queue::get)
    
    full_cond.wait(lg,[this]{return !full();});

    if(front == -1)
	front = 0;
	    
    rear = (rear + 1) % N;

    data[rear] = val;
    std::cout << "Inserting value " << val << std::endl;

    

    // Notificar para habilitar lectura

    empty_cond.notify_one();    

}


// Lectura de elemento mas viejo

template<class T, size_t N>
void Queue<T,N>::get(T* val) {

    // std::lock_guard<std::mutex> lg(m);

    // if( !empty() ) {

    // 	*val = data[front];

    // 	if(front == rear){
		
    // 	    front = -1;
		
    // 	    rear = -1;
		
    // 	}
	    
    // 	else {
		
    // 	    front = (front+1) % N;
		
    // 	}

    // 	full_cond.notify_one();

    // }

    // else {

    // 	val = new T;

    // }



    

    std::unique_lock<std::mutex> lg(m);
    

    // Espera por la variable de condicion empty. Si la cola esta vacia, se habilita con un put

    empty_cond.wait(lg,[this]{return !empty();});


    *val = data[front];

    if(front == rear){
		
	front = -1;
		
	rear = -1;
		
    }
	    
    else {
		
	front = (front+1) % N;
		
    }


    std::cout << "Extracting value " << *val << std::endl;

    // Habilita la posicion de un nuevo elemento (por si la cola estaba llena)
    
    full_cond.notify_one();

    
	
}


#endif // QUEUE_HPP
