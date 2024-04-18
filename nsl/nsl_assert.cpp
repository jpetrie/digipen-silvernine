/*! =========================================================================

     @file    nsl_assert.cpp
     @brief   Implements a robust assertion macro.

    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "nsl_common.h"

#include "nsl_assert.h"

#include "nsl_tools_string.h"


/*                                                                  functions
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
bool nsl::assert_worker(bool c,const char *cs,const char *fn,const char *f,unsigned int l)
/*! @brief Handle assertion macro.

    assert_worker() checks the assert condition c and, if it is false, displays
    an error message.

    @param c   Assert condition.
    @param cs  Assert condition as a string.
    @param fn  The function tripping the assert.
    @param f   The file tripping the assert.
    @param l   The line tripping the assert.

    @return
    The value of the assert condition.
    
    @internal
*/
{
  // Early-out if true.
  if(c)
    return (c);
    
std::string  tMsg = nsl::stformat("%s\n\nLocation:\n\t%s %d (%s)",cs,nsl::stptail(f,"\\").c_str(),l,fn);

  MessageBox(0,tMsg.c_str(),"Assertion Failed",MB_OK);
  return (c);
}