//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
//WW                  WWW           WWW WWW           WWW                    WW
//WW                   WWW   WWW   WWW   WWW   WWW   WWW                     WW
//WW                    WWW WW WW WWW     WWW WW WW WWW                      WW
//WW                     WWWW   WWWW       WWWW   WWWW                       WW
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW


#pragma once

#include <iostream>

struct Pixel {  

  unsigned char r, g, b;

  Pixel() : r(0), g(0), b(0)
  {

  }

  Pixel(unsigned char gray) : r(gray), g(gray), b(gray)
  {

  }

  Pixel(unsigned char r, unsigned char g, unsigned char b) :
    r(r), g(g), b(b)
  {

  }

  friend std::ostream& operator << (std::ostream& os, const Pixel& value) 
  {
    os << (char)value.b << (char)value.g << (char)value.r;
    return os;
  }
};