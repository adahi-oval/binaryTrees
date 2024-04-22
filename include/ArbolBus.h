#pragma once

#include "Nodo.h"
#include "ArbolBin.h"
#include <queue>
#include <iostream>

template <class Key>
class ABBusqueda : public AB<Key> {
public:
  // Constructor
  ABBusqueda() {
    this->raiz = nullptr;
  }

  int getNumNode() const {
    return this->numNodos;
  }

  // Método insert
  bool insert(const Key& k) override {
    if(search(k)) {
      return false;
    }
    
    NodoB<Key>* nuevo = new NodoB<Key>(k);
    NodoB<Key>* actual = this->getRaiz();
    if (actual == nullptr) {
      this->getRaiz() = nuevo;
      this->numNodos++;
      return true;
    }

    std::queue<NodoB<Key>*> cola;
    cola.push(actual);

    while (!cola.empty()) {
      NodoB<Key>* actual = cola.front();
      cola.pop();

      if(nuevo->getData() < actual->getData()) {
        if (actual->getIzdo() == nullptr) {
          actual->getIzdo() = nuevo;
          this->numNodos++;
          return true;
        } else {
          cola.push(actual->getIzdo());
        }
      } else {
        if (actual->getDcho() == nullptr) {
          actual->getDcho() = nuevo;
          this->numNodos++;
          return true;
        } else {
          cola.push(actual->getDcho());
        }
      }
    }
    return false;
  }

  // Método search
  bool search(const Key& k) const override {
    return searchRecursivo(this->getRoot(), k);
  }

private:
  bool searchRecursivo(NodoB<Key>* nodo, const Key& k) const {
    
    if (nodo == nullptr) {
      return false;
    }

    if(k < nodo->getData()) {
      return searchRecursivo(nodo->getIzdo(), k);
    } 
    else if (k > nodo->getData()) {
      return searchRecursivo(nodo->getDcho(), k);
    } 
    else {
      return true;
    }
  }

  int numNodos = 0;
};