//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
//WW                  WWW           WWW WWW           WWW                    WW
//WW                   WWW   WWW   WWW   WWW   WWW   WWW                     WW
//WW                    WWW WW WW WWW     WWW WW WW WWW                      WW
//WW                     WWWW   WWWW       WWWW   WWWW                       WW
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW


#pragma once

#include <cstdlib>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>

#include "Complex.h"

class Parameters 
{
  
public:

  unsigned int width;
  unsigned int height;
  unsigned short iterations;
  long double offsetX;
  long double offsetY;
  long double zoom;
  long double rotation;

  Parameters(unsigned int width, unsigned int height, unsigned short iterations,
    long double offsetX, long double offsetY, long double zoom=1.0, long double rotation=0.0) :
    width(width), height(height), iterations(iterations), offsetX(offsetX),
    offsetY(offsetY), zoom(zoom), rotation(rotation)
  {

  }

  void move(long double deltaX, long double deltaY)
  {
    Complex delta = Complex(deltaX, deltaY)
      .div(zoom, zoom)
      .rotateDegree(rotation);
    offsetX += delta.real();
    offsetY += delta.imag();     
  }

  void write(std::string fileName)
  {
    std::ofstream file(fileName.c_str());
    file << "fractalGenerator parameters v1.0" << std::endl;
    file << "width=" << width << std::endl;
    file << "height=" << height << std::endl;
    file << "iterations=" << iterations << std::endl;
    file << "offsetX=" << offsetX << std::endl;
    file << "offsetY=" << offsetY << std::endl;
    file << "zoom=" << zoom << std::endl;
    file << "rotation=" << rotation << std::endl;
    file.close();
  }

  bool setParameter(std::string name, std::string value)
  {
    if     (name.compare("width")      == 0) width = parseGreaterZero(width, name, value);
    else if(name.compare("height")     == 0) height = parseGreaterZero(height, name, value);
    else if(name.compare("iterations") == 0) iterations = atoi(value.c_str());
    else if(name.compare("offsetX")    == 0) offsetX = strtold(value.c_str(), NULL);
    else if(name.compare("offsetY")    == 0) offsetY = strtold(value.c_str(), NULL);
    else if(name.compare("zoom")       == 0) zoom = parseGreaterZero(zoom, name, value);
    else if(name.compare("rotation")   == 0) rotation = strtold(value.c_str(), NULL);
    else return false;

    return true;
  }

  void printParameterList(unsigned char intend = 0)
  {
    for(unsigned int i=0; i<intend; i++)
      std::cout << ' ';
    std::cout << "width, height, iterations" << std::endl;
    for(unsigned int i=0; i<intend; i++)
      std::cout << ' ';
    std::cout << "offsetX, offsetY, zoom, rotation" << std::endl;
  }

  unsigned int parseGreaterZero(unsigned int currentValue, std::string name, std::string value)
  {
    unsigned int newValue = atoi(value.c_str());
    if(newValue <= 0)
    {
      std::cout << "invalid value for " << name << std::endl;
      return currentValue;
    }
    return newValue;
  }

  long double parseGreaterZero(long double currentValue, std::string name, std::string value)
  {
    long double newValue = strtold(value.c_str(), NULL);
    if(newValue <= 0.0)
    {
      std::cout << "invalid value for " << name << std::endl;
      return currentValue;
    }
    return newValue;
  }

  void print()
  {
    std::cout << width << "x" << height << " (N=" << iterations << ") @ " << offsetX 
              << ", " << offsetY << ", " << rotation << "° (" << zoom << ")" << std::endl;
  }

};