//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
//WW                  WWW           WWW WWW           WWW                    WW
//WW                   WWW   WWW   WWW   WWW   WWW   WWW                     WW
//WW                    WWW WW WW WWW     WWW WW WW WWW                      WW
//WW                     WWWW   WWWW       WWWW   WWWW                       WW
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW


#pragma once

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

};