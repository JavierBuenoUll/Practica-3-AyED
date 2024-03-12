// AUTOR: JAVIER BUENO CALZADILLA 
// FECHA: 6/3/2024
// EMAIL: alu0101627922@ull.edu.es
// VERSION: 3.1
// ASIGNATURA: Algoritmos y Estructuras de Datos
// PRÁCTICA Nº: 3
// ESTILO: Google C++ Style Guide
// COMENTARIOS: 
// 

#ifndef POLYNOMIAL_H_
#define POLYNOMIAL_H_

#include <iostream>
#include <math.h>  // fabs, pow

#include "vector_t.h"
#include "sparse_vector_t.h"

// Clase para polinomios basados en vectores densos (vector inicial) de doubles
class Polynomial : public vector_t<double> {
 public:
  // constructores
  Polynomial(const int n = 0) : vector_t<double>(n) {};
  Polynomial(const Polynomial& pol)
      : vector_t<double>(pol) {}; // constructor de copia

  // destructor por defecto
  ~Polynomial() {};

  // E/S
  void Write(std::ostream& = std::cout, const double eps = EPS) const;
  
  // operaciones
  double Eval(const double) const;
  bool IsEqual(const Polynomial&, const double = EPS) const;
 };


// Clase para polinomios basados en vectores dispersos
class SparsePolynomial : public sparse_vector_t {
 public:
  // constructores
  SparsePolynomial(const int n = 0) : sparse_vector_t(n) {};
  SparsePolynomial(const Polynomial& pol) : sparse_vector_t(pol) {};
  SparsePolynomial(const SparsePolynomial&);  // constructor de copia

  // destructor
  ~SparsePolynomial() {};

  // E/S
  void Write(std::ostream& = std::cout) const;
  
  // operaciones
  double Eval(const double) const;
  bool IsEqual(const SparsePolynomial&, const double = EPS) const;
  bool IsEqual(const Polynomial&, const double = EPS) const;
};

// E/S
void Polynomial::Write(std::ostream& os, const double eps) const { // Método de escritura
  os << get_size() << ": [ ";
  bool first{true};
  for (int i{0}; i < get_size(); i++)
    if (IsNotZero(at(i), eps)) {
      os << (!first ? " + " : "") << at(i)
	 << (i > 1 ? " x^" : (i == 1) ? " x" : "");
      if (i > 1)
	os << i;
      first = false;
    }
  os << " ]" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Polynomial& p) { // Sobrecarga del operador de inserción
  p.Write(os);
  return os;
}

// Operaciones con polinomios

// Evaluación de un polinomio representado por vector denso FASE 3
double Polynomial::Eval(const double x) const {
  double result{0.0};
  double valor_x_elevado_grado {1.0};
  for(int i = 0; i < get_size(); i++) {
    int grado_polinomio = i;
    valor_x_elevado_grado = 1.0;
    while(grado_polinomio > 0) { // mientras el grado sea mayor que 1, se multiplica x tantas veces como el grado lo pide.
      valor_x_elevado_grado = x * valor_x_elevado_grado; // sería como una potencia
      grado_polinomio--; // se reduce el valor del grado
    }
    result = result + (at(i) * valor_x_elevado_grado);
  }
  return result;
}

// FASE 4
// Comparación si son iguales dos polinomios representados por vectores densos
bool Polynomial::IsEqual(const Polynomial& pol, const double eps) const {
  bool differents = false;
  int menor_tamanio = std::min(get_size(), pol.get_size());
  for(int i = 0; i < menor_tamanio; i++) {
    if (fabs(at(i) - pol.at(i)) > eps) {
      differents = true;
    }
  }
  return !differents;
}
 

// constructor de copia
SparsePolynomial::SparsePolynomial(const SparsePolynomial& spol) {
  *this = spol;   // se invoca directamente al operator=
}

// E/S
void SparsePolynomial::Write(std::ostream& os) const { // Método de escritura del polinomia disperso
  os << get_n() << "(" << get_nz() << "): [ ";
  bool first{true};
  for (int i{0}; i < get_nz(); i++) {
    int inx{at(i).get_inx()};
    os << (!first ? " + " : "") << at(i).get_val()
       << (inx > 1 ? " x^" : (inx == 1) ? " x" : "");
    if (inx > 1)
      os << inx;
    first = false;
  }
  os << " ]" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const SparsePolynomial& p) { // Sobrecarga del operador de inserción
  p.Write(os);
  return os;
}

// Operaciones con polinomios

// Evaluación de un polinomio representado por vector disperso FASE 3
double SparsePolynomial::Eval(const double x) const {
  double result{0.0};
  for(int i = 0; i < get_nz(); i++) {
    result += (at(i).get_val() * pow(x, at(i).get_inx())); 
    // Donde at(i).get_val() consigue el coeficiente, y at(i).get_inx, el exponente.
  }
  return result;
}

// FASE 4
// Comparación si son iguales dos polinomios representados por vectores dispersos
bool SparsePolynomial::IsEqual(const SparsePolynomial& spol
			       , const double eps) const {
  bool differents = false;
  for(int i = 0; i < get_nz(); i++) {
    if((at(i).get_inx() != spol.at(i).get_inx()) ||
       (fabs(at(i).get_val() - spol.at(i).get_val()) > eps)) {
      // Si los índices son distintos o la resta de los valores supera el margen (eps) son distintos.
    differents = true;
    break;
    }
  }
  return !differents;
}



// Comparación si son iguales dos polinomios representados por
// vector disperso y vector denso
bool SparsePolynomial::IsEqual(const Polynomial& pol, const double eps) const {
  bool differents = false;
  for(int i = 0, j = 0; i < get_nz() && j < pol.get_size(); i++, j++) {
    while(j < pol.get_size() && pol.at(j) == 0) {
      j++; // recorrer el polinomio denso hasta un elemento no nulo.
    }
    if(j >= pol.get_size() || (j != at(i).get_inx()) || (fabs(at(i).get_val() - pol.at(j)) > eps)) {
      differents = true;
    }
  }
  return !differents;
}



#endif  // POLYNOMIAL_H_
