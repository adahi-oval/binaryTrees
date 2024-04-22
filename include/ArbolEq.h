#pragma once

#include "Nodo.h"
#include "ArbolBin.h"
#include <queue>
#include <iostream>

template <class Key>
class ABEquilibrado : public AB<Key> {
public:
  // Constructor
  ABEquilibrado() {
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

      if (actual->getIzdo() == nullptr) {
        actual->getIzdo() = nuevo;
        this->numNodos++;
        return true;
      } else {
        cola.push(actual->getIzdo());
      }

      if (actual->getDcho() == nullptr) {
        actual->getDcho() = nuevo;
        this->numNodos++;
        return true;
      } else {
        cola.push(actual->getDcho());
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
    
    if (nodo->getData() == k) {
      return true;
    }

    if (searchRecursivo(nodo->getIzdo(), k)) {
      return true;
    }

    return searchRecursivo(nodo->getDcho(), k);
  }

  int numNodos;
};