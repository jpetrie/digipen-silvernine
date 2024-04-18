/*! =========================================================================

      @file    nsl_bitmap.cpp
      @brief   Implementation of nsl::bitmap.

    ========================================================================= */


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "nsl_bitmap.h"


/*                                                           function members
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
void nsl::bitmap::load_bmp(const std::string &fn)
/*! @brief Load bitmap data from a Windows bitmap (.bmp) file.
*/
{
std::ifstream     tFile(fn.c_str(),std::ios::binary);
BITMAPFILEHEADER  tFileHead;

  // Read file header.

  // Read bitmap header.
  // Read bitmap data.

  // Close.
  tFile.close();
}