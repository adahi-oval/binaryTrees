#include <string>
#include <stdexcept>
#include <ctime>
#include <random>
#include <sstream>

class NIF {
private:
  long nums;
  char letra;
  int letraAscii;
  std::string originalString;

public:
  NIF(std::string nifString) {
    if (!isValidNif(nifString))
    {
      throw std::invalid_argument("NIF inválido. Debe ser 8 números seguidos de una letra.");
    } else
    {
      nums = std::stol(nifString.substr(0,8));
      letra = nifString[nifString.length() - 1];
      letraAscii = letra;
      originalString = nifString;
      if (letraAscii < 65 || letraAscii > 90)
      {
        throw std::invalid_argument("NIF inválido. Debe ser 8 números seguidos de una letra mayúscula.");
      }
      
    }
  }

  // Constructor por defecto
  NIF() {
    // Generar 8 números aleatorios
    nums = 0;
    for (int i = 0; i < 8; ++i) {
      nums = nums * 10 + (std::rand() % 10);
    }

    // Generar una letra mayúscula aleatoria (código ASCII entre 65 y 90)
    letraAscii = 65 + std::rand() % 26;
    letra = static_cast<char>(letraAscii);

    // Crear la cadena original
    std::ostringstream oss;
    oss << nums << letra;
    originalString = oss.str();
  }

  long getNums() {
    return nums;
  }

  char getLetra() {
    return letra;
  }

  std::string getOriginal() {
    return originalString;
  }

  // Método para comprobar si un string es válido, comprueba la longitud, los 8 primeros caracteres y el ultimo por separado
  bool isValidNif(std::string nifString) {
    bool result = true;

    if (nifString.length() != 9)
    {
      result = false;
    } else
    {
      for (int i = 0; i < nifString.length() - 1; i++)
      {
        if (!isdigit(nifString[i])) { result = false; }
      }
      if (!std::isalpha(nifString[nifString.length() - 1])) { result = false; }
    }

    return result;
  }

  // Sobrecarga de operadores

  // Comparación
  bool operator==(const NIF& otro) const {
    return originalString == otro.originalString;
  }

  bool operator!=(const NIF& otro) const {
    return originalString != otro.originalString;
  }

  bool operator<(const NIF& otro) const {
    if (nums < otro.nums) { return true; } 
    else if (nums == otro.nums) {
      if (letraAscii < otro.letraAscii){ return true; }
    }
    return false;
  }

  bool operator>(const NIF& otro) const {
    if (nums > otro.nums) { return true; } 
    else if (nums == otro.nums) {
      if (letraAscii > otro.letraAscii){ return true; }
    }
    return false;
  }

  bool operator<=(const NIF& otro) const {
    if (nums < otro.nums) { return true; } 
    else if (nums == otro.nums) {
      if (letraAscii <= otro.letraAscii){ return true; }
    }
    return false;
  }

  bool operator>=(const NIF& otro) const {
    if (nums > otro.nums) { return true; } 
    else if (nums == otro.nums) {
      if (letraAscii >= otro.letraAscii){ return true; }
    }
    return false;
  }

  // Asignación
  NIF& operator=(const NIF& otro) {
    if (this != &otro) {
      nums = otro.nums;
      letra = otro.letra;
      letraAscii = otro.letraAscii;
      originalString = otro.originalString;
    }
    return *this;
  }

  // Operador /
  long operator/(int divisor) const {
    return nums / divisor;
  }

  // Operador <<
  friend std::ostream& operator<<(std::ostream& os, const NIF& nif) {
    os << nif.originalString;
    return os;
  }

};