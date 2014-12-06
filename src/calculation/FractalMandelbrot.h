//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
//WW                  WWW           WWW WWW           WWW                    WW
//WW                   WWW   WWW   WWW   WWW   WWW   WWW                     WW
//WW                    WWW WW WW WWW     WWW WW WW WWW                      WW
//WW                     WWWW   WWWW       WWWW   WWWW                       WW
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW


#pragma once

#include <stdio.h>

#include "Complex.h"
#include "FractalBase.h"
#include "Parameters.h"
#include "Result.h"

class FractalMandelbrot : public FractalBase {

public:	

  Result calculate(const Parameters &parameters)
  {
    Result result(parameters.width, parameters.height);
    for(unsigned int y=0; y<parameters.height; y++)
    {
      for(unsigned int x=0; x<parameters.width; x++)
      {
        Complex position = Complex(2.6, 2.4)
          .mul(x, y)
          .div(parameters.width, parameters.height)
          .add(-1.3, -1.2)
          .div(parameters.zoom, parameters.zoom)
          .rotateDegree(parameters.rotation)
          .add(parameters.offsetX, parameters.offsetY);
                    
        Complex value(position);

        for(unsigned short n=1; n<parameters.iterations; n++)
        {
          Complex square = value.square();
          if(square.real() + square.imag() > 4.0)
          {
            result.setValue(x, y, n);
            break;
          }
          value.imag(2 * value.real() * value.imag() + position.imag());         
          value.real(square.real() - square.imag() + position.real());
        }
      }
    }
    return result;
  }

  Parameters getDefaultParameters(unsigned int width, unsigned int height) const
  {
    return Parameters(width, height, 256, -0.75, 0.0);
  }
};