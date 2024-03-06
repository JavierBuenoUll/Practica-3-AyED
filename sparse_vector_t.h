// AUTOR: 
// FECHA: 
// EMAIL: 
// VERSION: 4.0
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

typedef pair_t<double> pair_double_t;
typedef vector_t<pair_double_t> pair_vector_t;

class sparse_vector_t {
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
  pair_double_t& operator[](const int);
  
  // getters constantes
  const pair_double_t& at(const int) const;
  const pair_double_t& operator[](const int) const;

  // E/S
  void write(std::ostream& = std::cout) const;

 private:
  pair_vector_t pv_;  // valores + índices
  int nz_;            // nº de valores distintos de cero = tamaño del vector
  int n_;             // tamaño del vector original

  // bool IsNotZero(const double, const double = EPS) const;
};


bool IsNotZero(const double val, const double eps = EPS) {
  return fabs(val) > eps;
}

sparse_vector_t::sparse_vector_t(const int n) : pv_(n), nz_(0), n_(n) {}

// FASE II
sparse_vector_t::sparse_vector_t(const vector_t<double>& v, const double eps)
    : pv_(), nz_(0), n_(0) {
  // poner el código aquí
}

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

sparse_vector_t::~sparse_vector_t() {}

inline int sparse_vector_t::get_nz() const {
  return nz_;
}

inline int sparse_vector_t::get_n() const {
  return n_;
}

pair_double_t& sparse_vector_t::at(const int i) {
  assert(i >= 0 && i < get_nz());
  return pv_[i];
}

pair_double_t& sparse_vector_t::operator[](const int i) {
  return at(i);
}

const pair_double_t& sparse_vector_t::at(const int i) const {
  assert(i >= 0 && i < get_nz());
  return pv_[i];
}

const pair_double_t& sparse_vector_t::operator[](const int i) const {
  return at(i);
}

// E/S
void sparse_vector_t::write(std::ostream& os) const { 
  os << get_n() << "(" << get_nz() << "): [ ";
  for (int i = 0; i < get_nz(); i++)
    os << pv_[i] << " ";
	os << "]" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const sparse_vector_t& sv) {
  sv.write(os);
  return os;
}

#endif  // SPARSE_VECTORT_H_
