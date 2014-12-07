//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
//WW                  WWW           WWW WWW           WWW                    WW
//WW                   WWW   WWW   WWW   WWW   WWW   WWW                     WW
//WW                    WWW WW WW WWW     WWW WW WW WWW                      WW
//WW                     WWWW   WWWW       WWWW   WWWW                       WW
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW


#pragma once

#include <unistd.h>
#include <termios.h>

#include "../calculation/FractalBase.h"
#include "../calculation/FractalMandelbrot.h"
#include "../calculation/Parameters.h"
#include "../calculation/Result.h"

class Controller {

  static const char INPUT_ENTER = 10;

  //src: http://stackoverflow.com/questions/421860
  static char getch() {
    char buf = 0;
    struct termios old = {0};
    if(tcgetattr(0, &old) < 0)
      perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if(tcsetattr(0, TCSANOW, &old) < 0)
      perror("tcsetattr ICANON");
    if(read(0, &buf, 1) < 0)
      perror ("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if(tcsetattr(0, TCSADRAIN, &old) < 0)
      perror ("tcsetattr ~ICANON");
    return buf;
  }

  FractalBase *fractal;
  Parameters parameters;
  ColorMap colorMap;

  long double deltaX;
  long double deltaY;
  long double deltaR;
  long double deltaZ;

public:

  Controller() : fractal(new FractalMandelbrot()), parameters(fractal->getDefaultParameters(300, 300))
  {
    deltaX = 0.1;
    deltaY = 0.1;
    deltaR = 5;
    deltaZ = 2.0;
  }

  ~Controller()
  {
    delete fractal;
  }

  void start()
  {  
    std::string command = "";
    bool commandInputActive = false;
    while(true)
    {      
      char input = getch();      

      if(commandInputActive) 
      {
        if(input == INPUT_ENTER)
        {
          std::cout << "command: " << command << std::endl;
          command = "";
          commandInputActive = false;
        }
        else 
        {
          command += input;
        }
      }
      else if(input == ':')
        commandInputActive = true;
      else if(input == 'x')
        break;
      else 
        handleInput(input);
    }
  }

private:

  void writeFractalBMP()
  {
    Result result = fractal->calculate(parameters);
    result.writeFractalBMP("fractal.bmp", colorMap);
    result.writeHistogramBMP("histogram.bmp", 266, 200);
    colorMap.writeBMP("colormap.bmp", 200, 30);
  }

  void handleInput(char input)
  {
    if     (input == 'a') parameters.offsetX += deltaX;   //TODO: consider rotation and zoom!!
    else if(input == 'd') parameters.offsetX -= deltaX;
    else if(input == 'w') parameters.offsetY += deltaY;
    else if(input == 's') parameters.offsetY -= deltaY;
    else if(input == 'e') parameters.rotation += deltaR;
    else if(input == 'q') parameters.rotation -= deltaR;
    else if(input == '+') parameters.zoom *= deltaZ;
    else if(input == '-') parameters.zoom /= deltaZ;

    //TODO: print / store parameters
    //TODO: change size, deltas with commands
    //TODO: use history to undo (also commands)

    else 
    {
      printUsage(); 
      return;
    }

    writeFractalBMP();
  }

  void printUsage()
  {
    std::cout << "usage: " << std::endl;
    std::cout << "  navigation: 'a', 'd', 'w', 's'" << std::endl;
    std::cout << "  rotation:   'q', 'e'" << std::endl;
    std::cout << "  zoom:       '+', '-'" << std::endl;
    std::cout << "  exit:       'x'" << std::endl;
  }
};