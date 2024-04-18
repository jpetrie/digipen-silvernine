/*! =========================================================================

      @file    nsl_bitmap.h
      @brief   Interface to nsl::bitmap.

    ========================================================================= */
    
/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _NSL_BITMAP_H_
#define _NSL_BITMAP_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "nsl.h"

#include <string>

namespace nsl
{


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class bitmap
/*! @brief Bitmap class.
*/
{
  public:
    // ct and dt
     bitmap(void);
     bitmap(const bitmap &s);
    ~bitmap(void);
    
    // load and save
    void load_bmp(const std::string &fn);
    void save_bmp(const std::string &fn);
    
  
  private:
    HBITMAP  mBitmap;      // Backbuffer bitmap.
    HBITMAP  mBitmapSave;  // Backup of default DC bitmap.
    HDC      mBitmapDC;    // Backbuffer device.
        
    unsigned char *mColorBuffer;  // Color data.
};


}       /* namespace nsl */
#endif  /* _NSL_BITMAP_H_ */