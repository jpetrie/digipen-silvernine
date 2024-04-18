/*! =========================================================================
      
      @file    sn_buildstamp.h
      @brief   Silver Nine buildstamp header file.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _SILVERNINE_BUILDSTAMP_H_
#define _SILVERNINE_BUILDSTAMP_H_


/*                                                                 prototypes
----------------------------------------------------------------------------- */

#include <string>


/*                                                                 prototypes
----------------------------------------------------------------------------- */

// build data accessors
std::string  build_stamp(void);
int          build_id(void);
  

#endif  /* _SILVERNINE_BUILDSTAMP_H_ */
