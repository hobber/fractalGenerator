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
  static const char INPUT_BACKSP = 127;

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
      //std::cout << (int) input << std::endl;  

      if(commandInputActive) 
      {
        std::cout << input << std::flush;
        if(input == INPUT_ENTER)
        {
          handleCommand(command);
          command = "";
          commandInputActive = false;
        }
        else if(input == INPUT_BACKSP)
        {
          if(command.length() == 0) 
          {
            std::cout << "\b\b\033[K:" << std::flush;
            continue;
          }
          std::cout << "\b\b\033[K" << std::flush;
          command.resize(command.length()-1);
        }
        else 
        {
          command += input;
        }
      }
      else if(input == ':')
      {
        commandInputActive = true;
        std::cout << ":" << std::flush;
      }
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

  void handleCommand(const std::string &command)
  {
    if(command.find('=') != std::string::npos)
    {
      int p = command.find('=');
      std::string name = command.substr(0, p);
      std::string value = command.substr(p+1);    
      if(parameters.setParameter(name, value) == false)
        std::cout << "unknown parameter" << std::endl;
    }
    else if(command.compare("redraw") == 0)
      writeFractalBMP();
    else
      std::cout << "unknowm command" << std::endl;
  }

  void handleInput(char input)
  {
    if     (input == 'a') parameters.move( deltaX, 0.0);//offsetX += deltaX;   //TODO: consider rotation and zoom!!
    else if(input == 'd') parameters.move(-deltaX, 0.0);//offsetX -= deltaX;
    else if(input == 'w') parameters.move(0.0,  deltaY);//offsetY += deltaY;
    else if(input == 's') parameters.move(0.0, -deltaY);//offsetY -= deltaY;
    else if(input == 'e') parameters.rotation += deltaR;
    else if(input == 'q') parameters.rotation -= deltaR;
    else if(input == '+') parameters.zoom *= deltaZ;
    else if(input == '-') parameters.zoom /= deltaZ;
    else if(input == 'p') parameters.print();
    else if(input == 'P') parameters.write("parameters.txt");
    
    //TODO: change size, deltas, iterations with commands
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
    std::cout << std::endl;
    std::cout << "simple commands: " << std::endl;
    std::cout << "  navigation:       'a', 'd', 'w', 's'" << std::endl;
    std::cout << "  rotation:         'q', 'e'" << std::endl;
    std::cout << "  zoom:             '+', '-'" << std::endl;
    std::cout << "  print parameters: 'p'" << std::endl;
    std::cout << "  write parameters: 'P'" << std::endl;
    std::cout << "  exit:             'x'" << std::endl;
    std::cout << "extended commands:" << std::endl;
    std::cout << "  :redraw ... redraws fractal" << std::endl;
    std::cout << "to set following parameters type :<name>=<value>" << std::endl;
    parameters.printParameterList(2);    
    std::cout << std::endl;
  }
};