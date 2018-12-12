#ifndef LOCKEDVAR_HPP
#define LOCKEDVAR_HPP

/*
  
Wrapper para proteger una variable.
Sigue los lineamientos descriptos en https://accu.org/index.php/journals/1967
Implementacion de wrapper y accesor

 */


// Wrapper

template<typename T>
class unique_access;

template<typename T>
class lockedVar;



template<typename T>
class lockedVar {
    
public:
    
  lockedVar() : value() {}
    
  lockedVar(const T& value) : value(value) {}
    

private:
    
  friend class unique_access<T>;
    
  std::mutex mutex;
    
  T value;
    
};




// Accesor

template<typename T>
class unique_access {
    
public:
    
    unique_access(lockedVar<T>& guard) : lock(guard.mutex), valueRef(guard.value) {}

    T& operator* () { return valueRef; }
    
    T* operator-> () { return &valueRef; }

private:
    
    std::unique_lock<std::mutex> lock;
    
    T& valueRef;
    
};
		


#endif // LOCKEDVAR_HPP
