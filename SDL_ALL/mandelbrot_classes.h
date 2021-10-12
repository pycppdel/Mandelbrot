//file for all classes in mandelbrot
#ifndef MANDEL_CLASSES
#define MANDEL_CLASSES
#include "utils.h"
#include <iostream>
#include <cstdint>


class ComplexNumber{


public:

  long double real, imag;

  ComplexNumber();
  ComplexNumber(ComplexNumber&);
  ComplexNumber(long double, long double);
  ~ComplexNumber();

  friend ComplexNumber& operator*(ComplexNumber&, ComplexNumber&);

  friend std::ostream& operator<<(std::ostream&, ComplexNumber&);
  ComplexNumber& operator=(ComplexNumber&);
  void square();


};

class Color{

public:

uint8_t r, g, b;

Color();
Color(uint8_t, uint8_t, uint8_t);
~Color();


};

class Field{


};

class Mandelbrot{


};


ComplexNumber::ComplexNumber(){

}

ComplexNumber::ComplexNumber(long double a, long double b){

  real = a;
  imag = b;
}

ComplexNumber::ComplexNumber(ComplexNumber& c){
  real = c.real;
  imag = c.imag;
}

ComplexNumber::~ComplexNumber(){


}

ComplexNumber& ComplexNumber::operator=(ComplexNumber& c){
  real = c.real;
  imag = c.imag;

  return (*this);
}

ComplexNumber& operator*(ComplexNumber& a1, ComplexNumber& a2){

long double new_real=0.0, new_imag=0.0;

new_real += a1.real*a2.real;
new_real -= a1.imag*a2.imag;
new_imag += a1.real*a2.imag;
new_imag += a1.imag*a2.real;

ComplexNumber* back = new ComplexNumber(new_real, new_imag);

return (*back);

}

std::ostream& operator<<(std::ostream& os, ComplexNumber& c){

  std::cout << c.real << " " << c.imag;
  return os;

}


void ComplexNumber::square(){
  (*this) = ((*this)*(*this));

}

Color::Color(){

}

Color::Color(uint8_t a, uint8_t b, uint8_t c){

  r = a;
  g = b;
  g = c;

}

Color::~Color(){
  
}

#endif
