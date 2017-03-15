/**
*
*/
#include "F_ChromaKey.h"
#include "PixelBuffer.h"
#include "ColorData.h"
#include <stdlib.h>
#include <math.h> 

F_ChromaKey::F_ChromaKey(float parameter, float secondary_parameter, float red, float green, float blue)
{
  m_filterParameter.amountF = parameter;
  m_filterParameter.amountF2 = secondary_parameter;
  m_filterParameter.red = red;
  m_filterParameter.green = green;
  m_filterParameter.blue = blue;
}

F_ChromaKey::~F_ChromaKey()
{
}
void F_ChromaKey::applyFilter(PixelBuffer *canvas)
{
  ColorData cur_pixel, chosen_color;
  float chosen_blue_diff, chosen_red_diff, max_distance, outer_threshold, euclidean_chroma_distance, interpolation_factor;
  chosen_color = ColorData(m_filterParameter.red, m_filterParameter.green, m_filterParameter.blue);

  max_distance = m_filterParameter.amountF * 1.41421356237; //sqrt of 2.0 used to precalculate value for comparisions
  outer_threshold = m_filterParameter.amountF2 * 1.41421356237;
  chosen_blue_diff = chosen_color.getChromaBlueDifference();
  chosen_red_diff = chosen_color.getChromaRedDifference();
  if (m_filterParameter.wallpaper) {
    for(int curX = 0; curX < canvas->getWidth(); curX++)
      {
        for(int curY = 0; curY < canvas->getHeight(); curY++)
        { 
          cur_pixel = canvas->getPixel(curX,curY);
          euclidean_chroma_distance = pow((cur_pixel.getChromaBlueDifference() - chosen_blue_diff),2.0) \
             + pow((cur_pixel.getChromaRedDifference() - chosen_red_diff),2.0);
          if ((euclidean_chroma_distance) <= pow(max_distance,2.0))  //Trying to avoid sqrt calculations if possible
          {
            canvas->setPixel(curX,curY,m_filterParameter.wallpaper->getPixel(curX % m_filterParameter.wallpaper->getWidth(), curY % m_filterParameter.wallpaper->getHeight()));
          }  else if (outer_threshold > 0.0)
           {
            interpolation_factor = 1.0 - ( (sqrt(euclidean_chroma_distance) - max_distance) / outer_threshold ); //by default numerator is non-negative
              if (interpolation_factor <= 1.0 || interpolation_factor > 0.0)  // Want to avoid negative intensity values
                {
                  canvas->setPixel(curX,curY, \
                    m_filterParameter.wallpaper->getPixel(curX % m_filterParameter.wallpaper->getWidth(), curY % m_filterParameter.wallpaper->getHeight()) * interpolation_factor \
                    + cur_pixel * (1.0 - interpolation_factor));
                }
          }
        }
      }
    }  
}