// AUTOR: JAVIER BUENO CALZADILLA 
// FECHA: 6/3/2024
// EMAIL: alu0101627922@ull.edu.es
// VERSION: 3.1
// ASIGNATURA: Algoritmos y Estructuras de Datos
// PRÁCTICA Nº: 3
// ESTILO: Google C++ Style Guide
// COMENTARIOS: 
// 

#ifndef VECTORT_H_
#define VECTORT_H_

#include <iostream>
#include <cassert>

template<class T> class vector_t {  //Se define la clase vector como plantilla 
 public:
  // constructores
  vector_t(const int = 0);
  vector_t(const vector_t&); // constructor de copia

  // operador de asignación
  vector_t<T>& operator=(const vector_t<T>&);

  // destructor
  ~vector_t();
  
  // getters
  T get_val(const int) const;
  int get_size(void) const;
  
  // setters
  void set_val(const int, const T);
  
  // getters-setters
  T& at(const int);
  T& operator[](const int);
  
  // getters constantes
  const T& at(const int) const;
  const T& operator[](const int) const;

  // Redimensionado
  void resize(const int);
  
  // E/S
  void read(std::istream& = std::cin);
  void write(std::ostream& = std::cout) const;

 private:
  T *v_;
  int sz_;
  
  void build(void);
  void destroy(void);
};


template<class T> vector_t<T>::vector_t(const int n) : v_(NULL), sz_(n) {
  build();
}

// constructor de copia
template<class T> vector_t<T>::vector_t(const vector_t<T>& w)
    : v_(NULL), sz_(0) {
  *this = w; // se invoca directamente al operator=
}

// sobrecarga del operador de asignación
template<class T> vector_t<T>& vector_t<T>::operator=(const vector_t<T>& w) {
  resize(w.get_size());
  for (int i = 0; i < get_size(); i++)
    at(i) = w.at(i);
  
  return *this;
}

template<class T> vector_t<T>::~vector_t() { // Destructor 
  destroy();
}

template<class T> void vector_t<T>::build() { // Si el tamaño es distinto de 0, reserva el tamaño de un vector de tamaño sz_
  v_ = NULL;
  if (sz_ != 0) {
    v_ = new T[sz_];
    assert(v_ != NULL);
  }
}

template<class T> void vector_t<T>::destroy() { // Destruye el vector existente y lo inicializa a null para limpiar la memoria
  if (v_ != NULL) {
    delete[] v_;
    v_ = NULL;
  }
  sz_ = 0;
}

template<class T> void vector_t<T>::resize(const int n) { // Establece el tamaño del vector a n
  destroy();
  sz_ = n;
  build();
}

template<class T> inline T vector_t<T>::get_val(const int i) const { // Recoge el índice de la posición del elemento
  assert(i >= 0 && i < get_size());
  return v_[i]; // Devuelve el elemento en dicha posición constante.
}

template<class T> inline int vector_t<T>::get_size() const { // Devuelve el tamaño del vector
  return sz_;
}

template<class T> void vector_t<T>::set_val(const int i, const T d) { // Establece el valor de esa posición a otra
  assert(i >= 0 && i < get_size());
  v_[i] = d;
}

template<class T> T& vector_t<T>::at(const int i) { // getter - setter
  assert(i >= 0 && i < get_size());
  return v_[i];
}

template<class T> T& vector_t<T>::operator[](const int i) { // Sobrecarga del operador [] para las posiciones
  return at(i);
}

template<class T> const T& vector_t<T>::at(const int i) const { // Getter constante
  assert(i >= 0 && i < get_size());
  return v_[i];
}

template<class T> const T& vector_t<T>::operator[](const int i) const { // Sobrecarga constante del operador []
  return at(i);
}

template<class T> void vector_t<T>::read(std::istream& is) { // Método de lectura por fichero
  is >> sz_;
  resize(sz_);
  for (int i = 0; i < sz_; i++)
    is >> at(i);
}

template<class T> void vector_t<T>::write(std::ostream& os) const { // Método de escritura
  os << get_size() << ": [ ";
  for (int i = 0; i < get_size(); i++)
    os << at(i) << (i != get_size() - 1 ? "\t" : "");
  os << " ]" << std::endl;
}

template<class T> std::istream& operator>>(std::istream& is, vector_t<T>& v) { // sobrecarga del operador de extracción
  v.read(is);
  return is;
}

template<class T> std::ostream& operator<<(std::ostream& os, // Sobrecarga del operador de inserción
					   const vector_t<T>& v) {
  v.write(os);
  return os;
}

#endif  // VECTORT_H_
