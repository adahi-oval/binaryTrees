#pragma once

template<class Key>
class NodoB {
  // Miembros:
  protected:
    Key dato;
    NodoB *izdo; 
    NodoB *dcho;

  public:
    // Constructor:
    NodoB(const Key dat, NodoB<Key> *izq = nullptr, NodoB<Key> *der = nullptr) :
          dato(dat), izdo(izq), dcho(der) {}
    
    Key& getData() {
      return dato;
    }      
    
    NodoB<Key>*& getIzdo() {
        return this->izdo;
    }

    NodoB<Key>*& getDcho() {
        return this->dcho;
    }

};