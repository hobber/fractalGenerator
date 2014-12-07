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
#include "FractalHistogram.h"
#include "Pixel.h"

class Result {

  unsigned short *data;
  unsigned int width;
  unsigned int height;
  FractalHistogram histogram;
  bool histogramIsUpdated;

public:

  Result(unsigned int width, unsigned int height)
  {
    this->width = width;
    this->height = height;
    data = new unsigned short[width*height];
    for(int i=0; i<width*height; i++)
      data[i] = 0;
    histogramIsUpdated = false;
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
    histogramIsUpdated = false;
  }

  void writeFractalBMP(std::string fileName, const ColorMap &colorMap)
  {
    if(histogramIsUpdated == false)
    {
      histogram.update(data, width * height);
      histogramIsUpdated = true;
    }

    Pixel image[width*height];
    const float *accumulation = histogram.getHistogramAccumulation();

    for(unsigned int i=0; i<width*height; i++)
      	image[i] = colorMap.convert(data[i], accumulation[data[i]]);
    
    Bitmap::writeBMP(fileName, width, height, image);
  }

  void writeHistogramBMP(std::string fileName, int width, int height, int boarder=5) 
  {
    if(histogramIsUpdated == false)
    {
      histogram.update(data, this->width * this->height);
      histogramIsUpdated = true;
    }

    histogram.writeBMP(fileName, width, height, boarder);
  }

};