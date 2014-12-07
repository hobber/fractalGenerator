//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
//WW                  WWW           WWW WWW           WWW                    WW
//WW                   WWW   WWW   WWW   WWW   WWW   WWW                     WW
//WW                    WWW WW WW WWW     WWW WW WW WWW                      WW
//WW                     WWWW   WWWW       WWWW   WWWW                       WW
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW


#pragma once

#include <stdexcept> 
#include <utility>
#include <vector>

#include "Bitmap.h"
#include "Pixel.h"

class ColorMap {
  
  std::vector<std::pair<Pixel, float> > colors;

public:

  ColorMap() {
    colors.push_back(std::make_pair(Pixel(255, 0, 0), 0.0));
    colors.push_back(std::make_pair(Pixel(255, 255, 0),  0.75));
    colors.push_back(std::make_pair(Pixel(0, 0, 255), 1.0));
  }

  Pixel convert(unsigned short value, float accumulation) const
  {    
    if(value == 0)
      return Pixel(0);
    return mapPercentage(accumulation);
  }
    
  Pixel mapPercentage(float accumulation) const    
  {
    int endColorIndex = -1;
    for(int i=0; i<colors.size(); i++)
    {
      if( colors[i].second > accumulation || 
         (colors[i].second == 1.0 && accumulation == 1.0))
      {
        endColorIndex = i;
        break;
      }
    }

    if(endColorIndex <= 0)
    {
      std::cout << "Invalid ColorMap (" << endColorIndex << ")!";
      throw new  std::runtime_error("Invalid ColorMap!");
    }

    Pixel startColor = colors[endColorIndex].first;
    Pixel endColor = colors[endColorIndex-1].first;
    float startPercentage = colors[endColorIndex-1].second;
    float endPercentage = colors[endColorIndex].second;
    float colorBandWidth = endPercentage - startPercentage;
    float actualPercentage = (accumulation - startPercentage) / colorBandWidth;
    float missingPercentage = 1.0 - actualPercentage;
    
    float r = startColor.r * actualPercentage + endColor.r * missingPercentage;
    float g = startColor.g * actualPercentage + endColor.g * missingPercentage;
    float b = startColor.b * actualPercentage + endColor.b * missingPercentage;

    return Pixel(r, g, b);   
  }

  void writeBMP(std::string fileName, unsigned int width, unsigned int height)
  {
    Pixel image[width*height];

    for(unsigned int x=0; x<width; x++)
    {
      float percentage = (float)x / (float)(width-1.0);
      Pixel color = mapPercentage(percentage);
      for(unsigned int y=0; y<height; y++)
        image[x + width*y] = color;      
    }
    
    Bitmap::writeBMP(fileName, width, height, image);
  }

};