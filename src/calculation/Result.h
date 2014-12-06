//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
//WW                  WWW           WWW WWW           WWW                    WW
//WW                   WWW   WWW   WWW   WWW   WWW   WWW                     WW
//WW                    WWW WW WW WWW     WWW WW WW WWW                      WW
//WW                     WWWW   WWWW       WWWW   WWWW                       WW
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW


#pragma once

#include <fstream>
#include <string>
#include <stdexcept> 
#include <stdio.h>

#include "Bitmap.h"
#include "ColorMap.h"
#include "Histogram.h"
#include "Pixel.h"

class Result { //ColorMap, setValue(x, y, v)

  unsigned short *data;
  unsigned int width;
  unsigned int height;
  Histogram histogram;

public:

  Result(unsigned int width, unsigned int height)
  {
    this->width = width;
    this->height = height;
    data = new unsigned short[width*height];
  }

  ~Result()
  {
    delete[] data;
  }

  void setValue(unsigned int x, unsigned int y, unsigned short value)
  {
    if(x >= width || y >= height)
      throw new std::out_of_range("Position out of range!");
    data[x + y*width] = value;
  }

  void writeFractalBMP(std::string fileName, const ColorMap &colorMap) const
  {
    Pixel image[width*height];

    for(unsigned int i=0; i<width*height; i++)
      	image[i] = colorMap.convert(data[i]);
    
    Bitmap::writeBMP(fileName, width, height, image);
  }

  void writeHistogramBMP(std::string fileName, int width, int height, int boarder=5) 
  {
    histogram.update(data, this->width * this->height);
    histogram.writeBMP(fileName, width, height, boarder);
  }

};