/*! =========================================================================
      
      @file    nsl_exception.cpp
      @brief   nsl::exception implementation.
      
    ========================================================================= */
    
/*                                                                   includes
----------------------------------------------------------------------------- */
                    
#include "nsl_common.h"                                                
#include "nsl_exception.h"  
#include "nsl_tools_string.h"                                                 


/*                                                           function members
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
nsl::exception::exception(const std::string &m,const char *f,unsigned int l,const char *fn)
/*! @brief Default constructor.

    Typically this function should not be invoked directly; the nlTHROW() macro
    will invoke it, filling in the parameters as needed.

    @param msg  A description of the exception.
    @param f    The file from which the exception was thrown.
    @param l    The line from which the exception was thrown.
    @param fn   The function from which the exception was thrown.
*/
: mWhat(m),mFile(f),mLine(l),mFunc(f)
{
  mStdWhat = nsl::stformat("%s\n\nLocation:\n\t%s %d (%s)",m.c_str(),nsl::stptail(f,"\\").c_str(),l,fn);
}


/*  _________________________________________________________________________ */
nsl::exception::exception(const nsl::exception &s)
/*! @brief Copy constructor.

    @param s  The exception to copy.
*/
: mWhat(s.mWhat),mFile(s.mFile),mLine(s.mLine) 
{
}


/*  _________________________________________________________________________ */
nsl::exception::~exception(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
nsl::exception& nsl::exception::operator=(const nsl::exception &rhs)
/*! @brief Assignment operator.

    @param rhs  The exception to assign to the invoking object.

    @return
    A reference to the new exception.
*/
{
  mWhat = rhs.mWhat;
  mFile = rhs.mFile;
  mLine = rhs.mLine;
  return (*this);
}

