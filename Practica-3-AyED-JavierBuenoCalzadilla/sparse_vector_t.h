// AUTOR: JAVIER BUENO CALZADILLA 
// FECHA: 6/3/2024
// EMAIL: alu0101627922@ull.edu.es
// VERSION: 3.1
// ASIGNATURA: Algoritmos y Estructuras de Datos
// PRÁCTICA Nº: 3
// ESTILO: Google C++ Style Guide
// COMENTARIOS: 
// 

#ifndef SPARSE_VECTORT_H_
#define SPARSE_VECTORT_H_

#include <iostream>
#include <math.h>  // fabs

#include "vector_t.h"
#include "pair_t.h"

#define EPS 1.0e-6

typedef pair_t<double> pair_double_t; // define el tipo de par de dobles
typedef vector_t<pair_double_t> pair_vector_t; // define el tipo de vector de pares de dobles

class sparse_vector_t { // Clase de vector disperso
 public:
  // constructores
  sparse_vector_t(const int = 0);
  sparse_vector_t(const vector_t<double>&,
		  const double = EPS); // constructor normal
  sparse_vector_t(const sparse_vector_t&);  // constructor de copia

  // operador de asignación
  sparse_vector_t& operator=(const sparse_vector_t&);

  // destructor
  ~sparse_vector_t();
  
  // getters
  int get_nz(void) const;
  int get_n(void) const;

  // getters-setters
  pair_double_t& at(const int);
  pair_double_t& operator[](const int); // Sobrecarga del operador []
  
  // getters constantes
  const pair_double_t& at(const int) const;
  const pair_double_t& operator[](const int) const;

  // E/S
  void write(std::ostream& = std::cout) const; // Método de escritura

  // Modificación de clase:
  void mostrar_monomios_coeficiente_0(const double) const;

 private:
  pair_vector_t pv_;  // valores + índices
  int nz_;            // nº de valores distintos de cero = tamaño del vector
  int n_;             // tamaño del vector original

  // bool IsNotZero(const double, const double = EPS) const;
};


bool IsNotZero(const double val, const double eps = EPS) {
  return fabs(val) > eps;
}

sparse_vector_t::sparse_vector_t(const int n) : pv_(n), nz_(0), n_(n) {} // constructor por defecto

// FASE II
sparse_vector_t::sparse_vector_t(const vector_t<double>& v, const double eps)
    : pv_(), nz_(0), n_(v.get_size()) {
  for (int i = 0; i < n_; i++) 
    if(IsNotZero(v[i],eps)) 
      nz_++;
      pv_.resize(nz_);
    
    nz_ = 0;
    for(int i = 0; i < n_; i++) 
      if(IsNotZero(v[i],eps)) {
        pv_.set_val(nz_,pair_double_t(v[i],i));
        nz_++;
      }
}
// Modificación de clase: 
 /*void sparse_vector_t::mostrar_monomios_coeficiente_0(const double) const {
    for (int i = 0; i < n_; i++) {
      if(!IsNotZero(v[i],eps)) {

      }
    }
  }
  */

// constructor de copia
sparse_vector_t::sparse_vector_t(const sparse_vector_t& w) {
  *this = w;  // se invoca directamente al operator=
}

// operador de asignación
sparse_vector_t& sparse_vector_t::operator=(const sparse_vector_t& w) {
  nz_ = w.get_nz();
  n_ = w.get_n();
  pv_ = w.pv_;

  return *this;
}

sparse_vector_t::~sparse_vector_t() {} // Destructor de la clase sparse vector

inline int sparse_vector_t::get_nz() const { // getter del número de valores distintos de 0
  return nz_;
}

inline int sparse_vector_t::get_n() const { // getter del tamaño del vector
  return n_;
}

pair_double_t& sparse_vector_t::at(const int i) { // Devuelve el valor de una posición constante
  assert(i >= 0 && i < get_nz());
  return pv_[i];
}

pair_double_t& sparse_vector_t::operator[](const int i) { // Sobrecarga del operador []
  return at(i);
}

const pair_double_t& sparse_vector_t::at(const int i) const { // Devuelve el valor constante
  assert(i >= 0 && i < get_nz());
  return pv_[i];
}

const pair_double_t& sparse_vector_t::operator[](const int i) const { // Sobrecarga constante
  return at(i);
}

// E/S
void sparse_vector_t::write(std::ostream& os) const { // Método de escritura  
  os << get_n() << "(" << get_nz() << "): [ ";
  for (int i = 0; i < get_nz(); i++)
    os << pv_[i] << " ";
	os << "]" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const sparse_vector_t& sv) { // Sobrecarga del operador de inserción
  sv.write(os);
  return os;
}

#endif  // SPARSE_VECTORT_H_
