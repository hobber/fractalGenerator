

#include "calculation/FractalMandelbrot.h"
#include "calculation/Parameters.h"
#include "calculation/Result.h"

int main( int argc, const char* argv[] )
{
  FractalMandelbrot fractal;
  Parameters parameters = fractal.getDefaultParameters(200, 200);
  ColorMap colorMap;
  Result result = fractal.calculate(parameters);
  result.writeFractalBMP("fractal.bmp", colorMap);
  result.writeHistogramBMP("histogram.bmp", 266, 200);
  colorMap.writeBMP("colormap.bmp", 200, 30);
  return 0;
}