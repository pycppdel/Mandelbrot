//file for all classes in mandelbrot
#ifndef MANDEL_CLASSES
#define MANDEL_CLASSES
#include "utils.h"
#include <iostream>
#include <cstdint>
#include <utility>
#include <map>

class ComplexNumber;
class Color;
class Field;
class Mandelbrot;

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

private:

  int width, height, magnitude;

public:
  fieldmap field;
  fieldmap squarefield;

  Field();
  Field(int, int, int);
  ~Field();

  std::pair<ComplexNumber*, Color*>* get(std::pair<int, int>*);

  void draw(SDL_Renderer*);



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

Field::Field(){


}

Field::Field(int w, int h, int m){

  width = w;
  height = h;
  magnitude = m;


  std::cout << &field;


  for(int i=0;i<height;i++){

    for(int g = 0;g< width;g++){

      std::pair<int, int>* pos = new std::pair<int, int>(g, i);
      ComplexNumber a(g, i);
      Color color(0, 0, 0);
      int* b = new int(8);

      field[pos] = b;




    }
  }

  std::pair<int, int>* pos = new std::pair<int, int>(4, 5);

  std::cout << *(field[pos]);







}

std::pair<ComplexNumber*, Color*>*  Field::get(std::pair<int, int>* p){

  return  NULL;

}

Field::~Field(){




}

void Field::draw(SDL_Renderer* r){



}

#endif
