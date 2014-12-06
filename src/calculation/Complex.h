//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
//WW                  WWW           WWW WWW           WWW                    WW
//WW                   WWW   WWW   WWW   WWW   WWW   WWW                     WW
//WW                    WWW WW WW WWW     WWW WW WW WWW                      WW
//WW                     WWWW   WWWW       WWWW   WWWW                       WW
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW


#pragma once

#include <complex>
#include <iostream>

class Complex {

  std::complex<long double> value;

public:
  Complex(long double x, long double y) : value(x, y) {}
  
  Complex(const Complex &value) : value(value.value) {}

  Complex square() const 
  {
    long double x = value.real() * value.real();
    long double y = value.imag() * value.imag();
    return Complex(x, y);
  }

  long double real() const 
  {
    return value.real();
  }

  void real(long double x) 
  {
    value = std::complex<long double>(x, value.imag());
  }

  long double imag() const 
  {
    return value.imag();
  }

  void imag(long double y) 
  {
    value = std::complex<long double>(value.real(), y);
  }

  long double radius() const
  {
    return abs(value);
  }

  long double angle() const
  {
    return radius() == 0.0 ? 0.0 : arg(value);
  }

  Complex mul(long double x, long double y)
  {
    return Complex(value.real()*x, value.imag()*y);
  }

  Complex div(long double x, long double y)
  {
    return Complex(value.real()/x, value.imag()/y);
  }

  Complex add(long double x, long double y)
  {
    return Complex(value.real()+x, value.imag()+y);
  }

  Complex rotateDegree(long double delta)
  {
    if(delta == 0.0 || radius() == 0.0)
      return Complex(value.real(), value.imag());
    long double newAngle = delta * M_PI / 180.0 + angle();
    long double x = radius() * cos(newAngle);
    long double y = radius() * sin(newAngle);
    return Complex(x, y);
  }

  friend std::ostream& operator << (std::ostream& os, const Complex& value) 
  {
    os << "(" << value.value.real() << ", " << value.value.imag() << ")";
    return os;
  }
};