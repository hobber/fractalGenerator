//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
//WW                  WWW           WWW WWW           WWW                    WW
//WW                   WWW   WWW   WWW   WWW   WWW   WWW                     WW
//WW                    WWW WW WW WWW     WWW WW WW WWW                      WW
//WW                     WWWW   WWWW       WWWW   WWWW                       WW
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW


#pragma once

#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <string>
#include <vector>

#include "Pixel.h"

class FractalHistogram {

  unsigned int histogramm[USHRT_MAX];
  float accumulation[USHRT_MAX];
  unsigned int maximumEntry;
  unsigned int maximumValue;

  Pixel colorBackground;
  Pixel colorLines;
  Pixel colorForeground;
  Pixel colorAccumulation;

public:

  FractalHistogram() : maximumEntry(0), maximumValue(0), colorBackground(255), 
    colorLines(0), colorForeground(100), colorAccumulation(255, 0, 0) 
  {

  }

  void update(unsigned short *data, unsigned int dataSize)
  {
    for(int i=0; i<USHRT_MAX; i++)
      histogramm[i] = 0;

    maximumValue = 0;
    maximumEntry = 0;

    for(int i=0; i<dataSize; i++)
    {
      histogramm[data[i]]++;
      if(data[i] > maximumEntry) {
        maximumEntry = data[i];
      }
      if(histogramm[data[i]] > maximumValue)
        maximumValue = histogramm[data[i]];
    }

    float sum = 0.0;
    float total = dataSize - histogramm[0];
    accumulation[0] = 0.0;
    for(int i=1; i<USHRT_MAX; i++)
    {            
      accumulation[i] = sum / total;      
      sum += histogramm[i];
    }
  }

  const float* getHistogramAccumulation() const
  {
    return accumulation;
  }

  void writeBMP(std::string fileName, unsigned int width, unsigned int height, unsigned int boarder=5)
  {
    long double scaleX = (long double)(width-2*boarder) / maximumEntry;
    long double scaleY = (long double)(height-2*boarder) / maximumValue;
    unsigned int barWidth = scaleX > 1.0 ? floor(scaleX) : 1;    
    unsigned int groupSize = scaleX < 1.0 ? ceil(1.0 / scaleX) : 1;
    unsigned int widthPlot = maximumEntry * barWidth / groupSize;    
    
    Pixel image[width * height];
    for(unsigned int i=0; i<width*height; i++)
      image[i] = colorBackground;

    for(unsigned int x=boarder-1; x<=widthPlot+boarder; x++)
      image[x + (height-boarder+1)*width] = colorLines;
    for(unsigned int y=boarder; y<=height-boarder+1; y++)
      image[boarder-1 + y*width] = colorLines;

    for(unsigned int x=0, i=0; i<maximumEntry; x++) 
    {       
      unsigned int value = histogramm[i] * scaleY;
      long double accu = accumulation[i];
      if(groupSize > 1) 
      {
        for(int g=1; g<groupSize; g++)
        {
          value += histogramm[i+g] * scaleY;
          accu += accumulation[i+g];
        }
        value /= groupSize;
        accu /= groupSize;
      }
      i += groupSize;

      for(unsigned int w=0; w<barWidth; w++) 
      {        
        for(unsigned int y=0; y<value; y++) 
          image[x*barWidth+w+boarder + width*(height-boarder-y)] = colorForeground;        

        unsigned int index = x*barWidth+w+boarder + width*(int)(height-boarder-accu*(height-2*boarder));
        image[index] = colorAccumulation;
      }
    }
    
    Bitmap::writeBMP(fileName, width, height, image);    
  }
};