#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "ArbolEq.h"
#include "ArbolBus.h"
#include "Nif.h"

typedef NIF Key;
int main(int argc, char* argv[]) {

  int size;
  std::string filename = "";
  std::string abType;
  std::string insertMethod;

  if (argc > 7 || argc < 5) {
    std::cerr << "Uso: " << argv[0] << " -ab <abe|abb> -init <manual|random|file> [s] [f]" << std::endl;
    return 1;
  }

  for (int i = 1; i < argc; ++i) {
    std::string option(argv[i]);
    if (option == "-ab") {
      abType = argv[++i];
    } else if (option == "-init") {
      insertMethod = argv[++i];
      if (insertMethod == "file")
      {
        size = std::stoi(argv[++i]);
        filename = argv[++i];
      } else if (insertMethod == "random") {
        size = std::stoi(argv[++i]);
      }
    } else {
      std::cerr << "Opción no válida: " << option << std::endl;
      std::cerr << "Uso: " << argv[0] << " -size <s> -ord <m> -init <i> [f] -trace <y|n>" << std::endl;
      return 1;
    }
  }

  ABBusqueda<Key> arbolBus;
  ABBusqueda<Key> arbolEq;
  int menuOpt = 1;

  if (abType == "abe") {
    if(insertMethod == "random") {
      std::srand(std::time(0));
      for (int i = 0; i < size; i++) {
        Key placeholder;
        arbolEq.insert(placeholder);
      }
    } 
    else if (insertMethod == "file") {
      std::ifstream file(filename);
      if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
        return 1;
      }

      std::vector<std::string> lines;
      std::string line;
      while (std::getline(file, line)) {
        lines.push_back(line);
      }

      file.close();

      for (int i = 0; i < size; i++) {
        Key input(lines[i]);
        arbolEq.insert(input);
      }
    }

    std::cout << arbolEq << std::endl;

    while(menuOpt != 0) {
      std::cout << "\n[0] Salir\n[1] Insertar clave\n[2] Buscar clave\n[3] Mostrar árbol inorden\n" << std::endl;
      std::cin >> menuOpt;
      if (menuOpt == 1) {
        std::string inputString;
        std::cout << "Introduzca la clave a insertar: ";
        std::cin >> inputString;

        Key input(inputString);
        arbolEq.insert(input);
        std::cout << arbolEq << std::endl;
      } else if (menuOpt == 2) {
        std::string inputString;
        std::cout << "Introduzca la clave a buscar:\n";
        std::cin >> inputString;
      
        Key input(inputString);
        std::cout << (arbolEq.search(input) ? "\nEncontrado" : "\nNo Encontrado") << std::endl;
      } else if (menuOpt == 3) {
        std::cout << std::endl;
        arbolEq.inorden();
      } else if (menuOpt == 0) {
        break;
      } else {
        std::cout << "\n Seleccione una opción válida.\n";
      }
    }
  } 
  else if (abType == "abb") {

  } else {
    std::cerr << "Opción no válida: " << abType << std::endl;
  }

}