//file for all classes in mandelbrot
#ifndef MANDEL_CLASSES
#define MANDEL_CLASSES
#include "utils.h"
#include <iostream>
#include <cstdint>
#include <utility>
#include <map>
#include <cmath>

class ComplexNumber;
class Color;
class Field;
class Mandelbrot;
class ColorReg;

bool compare(ComplexNumber&);

typedef std::pair<ComplexNumber*, Color*> fieldname;
typedef std::pair<long double, long double> scale;


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

  friend ComplexNumber& operator +(ComplexNumber&, ComplexNumber&);
  friend bool operator<(ComplexNumber&, ComplexNumber&);


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

  fieldname **field;
  scale xscale;
  scale yscale;

  Field();
  Field(int, int, int);
  ~Field();

  void draw(SDL_Renderer*);

  fieldname* get(int, int);
  void setComplex(int, int, ComplexNumber*);
  void setColor(int, int, Color*);

  void calculateColors(ColorReg*);
  void setxscale(long double, long double);
  void setyscale(long double, long double);



};

class ColorReg{

public:

  Color colors[2] = {{0, 0, 255}, {0, 0, 0}};

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

  std::cout << c.real << " " << c.imag << "\n";
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

  field = new fieldname*[height];

  xscale.first = -2;
  xscale.second = 2;

  yscale.first = -2;
  yscale.second = 2;

  for(int i=0;i<height;i++){

    field[i] = new fieldname[width];


  }

  long double adif = xscale.second-xscale.first, bdif = yscale.second-yscale.first;

  for(int i=0;i<height;i++){

    for(int g=0;g<width;g++){

      field[i][g].first = new ComplexNumber(yscale.first+bdif/height*i, xscale.first+adif/width*g);
      field[i][g].second = new Color(0, 0, 0);



    }
  }


}



Field::~Field(){


  for(int i=0;i<height;i++){

    delete [] field[i];

  }

  delete [] field;


}

void Field::draw(SDL_Renderer* r){


for(int a=0;a<height;a++){

  for(int b=0;b<width;b++){

    ComplexNumber* cn = field[a][b].first;
    Color* cl = field[a][b].second;

    SDL_SetRenderDrawColor(r, cl->r, cl->g, cl->b, 0);
    SDL_RenderDrawPoint(r, a, b);


  }
}

}

fieldname* Field::get(int a, int b){

  return &(field[a][b]);

}

void Field::setComplex(int height, int width, ComplexNumber* number){

  delete field[height][width].first;
  field[height][width].first = number;

}

void Field::setColor(int height, int width, Color* c){

  delete field[height][width].second;
  field[height][width].second = c;



}

void Field::calculateColors(ColorReg* reg){

  for(int i=0;i<height;i++){

    for(int g=0;g<width;g++){

      ComplexNumber complex = (*field[i][g].first);
      ComplexNumber begin(complex.real, complex.imag);

    for(int t=0;t<magnitude;t++){
      complex.square();
      complex = complex+begin;
    }
    ComplexNumber end(complex.real, complex.imag);
    ComplexNumber diff(end.real-begin.real, end.imag-begin.imag);

    if (diff.real < 1 || diff.imag < 1 || diff.real < -1 || diff.imag < -1){
      setColor(i, g, new Color(reg->colors[1]));
    }
    else{
      setColor(i, g, new Color(reg->colors[0]));
    }





    }
  }

}

void Field::setxscale(long double a, long double b){

xscale.first = a;
xscale.second = b;

long double adif = xscale.second-xscale.first, bdif = yscale.second-yscale.first;

for(int i=0;i<height;i++){

  for(int g=0;g<width;g++){

    setComplex(i, g, new ComplexNumber(yscale.first+bdif/height*i, xscale.first+adif/width*g));




  }
}

}

void Field::setyscale(long double a, long double b){
  yscale.first = a;
  yscale.second = b;

  long double adif = xscale.second-xscale.first, bdif = yscale.second-yscale.first;

  for(int i=0;i<height;i++){

    for(int g=0;g<width;g++){

      setComplex(i, g, new ComplexNumber(yscale.first+bdif/height*i, xscale.first+adif/width*g));




    }
  }
}


ComplexNumber& operator+(ComplexNumber&a, ComplexNumber& b){

  ComplexNumber neu(a.real+b.real, a.imag+b.imag);
  return neu;

}

bool operator<(ComplexNumber& a, ComplexNumber&b){

  return false;
}

bool compare(ComplexNumber& a){
return (a.real > 1 || a.imag > 1 || a.real < -1 || a.imag < 1);
}




#endif
