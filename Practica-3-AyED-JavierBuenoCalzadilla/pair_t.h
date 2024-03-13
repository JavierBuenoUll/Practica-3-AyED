// AUTOR: JAVIER BUENO CALZADILLA 
// FECHA: 6/3/2024
// EMAIL: alu0101627922@ull.edu.es
// VERSION: 3.1
// ASIGNATURA: Algoritmos y Estructuras de Datos
// PRÁCTICA Nº: 3
// ESTILO: Google C++ Style Guide
// COMENTARIOS: 
// 

#ifndef PAIRT_H_
#define PAIRT_H_

#include <iostream>


template<class T> class pair_t { // Establecemos la clase par como plantilla
 public:
  // constructores
  pair_t(void); 
  pair_t(T, int); // constructor con parámetros

  // destructor
  ~pair_t(void);

  // getters & setters
  T get_val(void) const;
  int get_inx(void) const;
  void set(T, int);

  // E/S
  std::istream& read(std::istream& is = std::cin); // método de lectura
  std::ostream& write(std::ostream& os = std::cout) const; // método de escritura

 private:
  T val_; // valor
  int inx_; // índice
};


template<class T> pair_t<T>::pair_t() : val_(), inx_(-1) {} // Constructor por defecto

template<class T> pair_t<T>::pair_t(T val, int inx) : val_(val), inx_(inx) {} // Constructor con parámetros

template<class T> pair_t<T>::~pair_t() {} // destructor

template<class T> void pair_t<T>::set(T val, int inx) { // setters
  val_ = val;
  inx_ = inx;
}

template<class T> int pair_t<T>::get_inx() const { // getter del índice
  return inx_;
}

template<class T> T pair_t<T>::get_val() const { // getter del valor
  return val_;
}

template<class T> std::istream& pair_t<T>::read(std::istream& is) { // Método de lectura
  return is >> inx_ >> val_;
}

template<class T> std::ostream& pair_t<T>::write(std::ostream& os) const { // método de escritura
  return os << "(" << inx_ << ":" << val_ << ")";
}

template<class T> std::ostream& operator<<(std::ostream& os, // Sobrecarga del operador de inserción
					   const pair_t<T>& p) {
  p.write(os);
  return os;
}

#endif  // PAIRT_H_
