#pragma once

#include "Nodo.h"
#include <queue>
#include <iostream>

template <class Key>
class AB { 
public:
    // Constructor:
    AB() : raiz(nullptr) {}

    // Métodos
    NodoB<Key>*& getRaiz() {
        return raiz;
    }

    NodoB<Key>* getRoot() const {
        return raiz;
    }

    virtual bool insert(const Key& k) = 0;
    virtual bool search(const Key& k) const = 0;

    void inorden() const {
      inordenRecursivo(this->getRoot());
    }

    void inordenRecursivo(NodoB<Key>* nodo) const {
      if (nodo != nullptr) {
        inordenRecursivo(nodo->getIzdo());
        std::cout << nodo->getData() << " " << std::endl;
        inordenRecursivo(nodo->getDcho());
      }
    }

    // Sobrecarga del operador de inserción en flujo
    friend std::ostream& operator<<(std::ostream& os, const AB<Key>& arbol) {
        if (arbol.raiz == nullptr) {
            os << "[.]";
            return os;
        }

        std::queue<std::pair<NodoB<Key>*, int>> Q;
        Q.push({arbol.raiz, 0});
        int nivel_actual = 0;

        while (!Q.empty()) {
            auto [nodo, nivel] = Q.front();
            Q.pop();
            
            if (nivel > nivel_actual) {
                nivel_actual = nivel;
                os << std::endl;
            }

            if (nodo != nullptr) {

                os << " [" << nodo->getData() << "]";
                Q.push({nodo->getIzdo(), nivel + 1});
                Q.push({nodo->getDcho(), nivel + 1});

                os << " ";
            } else {
                os << "[.] ";
            }
        }
        return os;
    }

protected:
    // Atributos
    NodoB<Key> *raiz;
};