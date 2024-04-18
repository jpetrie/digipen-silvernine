/*! =========================================================================

     @file    nsl_assert.h
     @brief   Provides a robust assertion macro.

    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#ifndef _NSL_ASSERT_H_
#define _NSL_ASSERT_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "nsl_common.h"

namespace nsl
{


/*                                                                 prototypes
----------------------------------------------------------------------------- */

// assertion worker
bool assert_worker(bool c,const char *cs,const char *fn,const char *f,unsigned int l);


/*                                                                     macros
----------------------------------------------------------------------------- */

// assertion
#if defined(NSL_VC)
  #define nlASSERT(c)  if(!nsl::assert_worker((c),(#c),__FUNCTION__,__FILE__,__LINE__)) __asm int 3;
#else
  #define nlASSERT(c)  nsl::assert_worker((c),(#c),"unknown",__FILE__,__LINE__)
#endif


}       /* namespace nsl */
#endif  /* _NSL_ASSERT_H_ */