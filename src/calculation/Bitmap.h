//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
//WW                  WWW           WWW WWW           WWW                    WW
//WW                   WWW   WWW   WWW   WWW   WWW   WWW                     WW
//WW                    WWW WW WW WWW     WWW WW WW WWW                      WW
//WW                     WWWW   WWWW       WWWW   WWWW                       WW
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW


#pragma once

#include <iostream>

#include "Pixel.h"

class Bitmap {

public:

  static void writeBMP(std::string fileName, int width, int height, const Pixel *image)
  {
    unsigned int pad = (width*3)%4 ? 4-((width*3)%4) : 0;
    unsigned int size = 54 + width * height * 3 + height * pad;
    
    std::ofstream file(fileName.c_str(), std::ios::binary | std::ios::out);
    file << "BM";                             //bfType
    file.write((char*)&size, 4);              //bfSize
    file << '\0' << '\0' << '\0' << '\0';     //bfReserved16
    file << (char)54 << '\0' << '\0' << '\0'; //bfOffBits .. size of header

    file << (char)40 << '\0' << '\0' << '\0'; //bisize .. size of infoheader
    file.write((char*)&width, 4);             //biWidth
    file.write((char*)&height, 4);            //biHeight
    file <<  '\1' << '\0';                    //biPlanes
    file <<  (char)24 << '\0';                //biBitCount
    file <<  '\0' << '\0' << '\0' << '\0';    //biCompression
    file <<  '\0' << '\0' << '\0' << '\0';    //biSizeImage
    file <<  '\0' << '\0' << '\0' << '\0';    //biXPelsPerMeter
    file <<  '\0' << '\0' << '\0' << '\0';    //biYPelsPerMeter
    file <<  '\0' << '\0' << '\0' << '\0';    //biClrUsed
    file <<  '\0' << '\0' << '\0' << '\0';    //biClrImportant

    for(unsigned int y=height-1; y<height; y--)
    {
      for(unsigned int x=0; x<width; x++)
        file << image[x + y*width];
      for(int i=0; i<pad; i++)
        file << '\0';
    }

    file.close();
  }
};