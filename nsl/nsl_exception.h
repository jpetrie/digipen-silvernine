/*! =========================================================================
      
      @file    nsl_exception.h
      @brief   nsl::exception interface.
      
    ========================================================================= */
    
/*                                                                      guard
----------------------------------------------------------------------------- */
                                                                  
#ifndef _NSL_EXCEPTION_H_
#define _NSL_EXCEPTION_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "nsl_common.h"

namespace nsl
{


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class exception : public std::exception
/*! @brief Provides an exception base class.
*/
{
  public:
    // ct and dt
             exception(const std::string &m = "",const char *f = 0,unsigned int l = 0,const char *fn = 0);
             exception(const exception &s);
    virtual ~exception(void);
    
    // = operator
    exception& operator=(const exception &rhs);
    
    // accessors
    virtual const std::string& info(void) const { return (mWhat); }
    std::string                func(void) const { return (mFunc); }
    std::string                file(void) const { return (mFile); }
    unsigned int               line(void) const { return (mLine); }
    
    // std::exception compatibility
    const char* what(void) const { return (mStdWhat.c_str()); }
    
    
  protected:
    std::string   mWhat;  // Exception message.
    
    
  private:
    std::string   mFunc;  // Function exception thrown from.
    std::string   mFile;  // File exception thrown from.
    unsigned int  mLine;  // Line exception thrown from.
    
    std::string   mStdWhat;  // Returned from std::exception::what().
};


/*  _________________________________________________________________________ */
template< typename E_ >
class var_exception : public exception
/*! @brief Variant exception.

    @param E_  Exception variant tag.
*/
{
  public:
             var_exception(const std::string &m = "",const char *f = 0,unsigned int l = 0,const char *fn = 0);
    virtual ~var_exception(void);
};


/*                                                           member functions
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
template< typename E_ >
var_exception< E_ >::var_exception(const std::string &m,const char *f,unsigned int l,const char *fn)
/*! @brief Default constructor.

    Typically this function should not be invoked directly; the nlTHROWV() macro
    will invoke it, filling in the parameters as needed.

    @param msg  A description of the exception.
    @param f    The file from which the exception was thrown.
    @param l    The line from which the exception was thrown.
    @param fn   The function from which the exception was thrown.
*/
: exception(m,f,l,fn)
{
}


/*  _________________________________________________________________________ */
template< typename E_ >
var_exception< E_ >::~var_exception(void)
/*! @brief Destructor.
*/
{
}

/*                                                                     macros
----------------------------------------------------------------------------- */

// declaration    
#define nlVE_TAG(t)  typedef struct { } t   

// throw
#if defined(NSL_VC)
  #define nlTHROW(m)     throw (nsl::exception((m),__FILE__,__LINE__,__FUNCTION__))
  #define nlTHROWV(t,m)  throw (nsl::var_exception< t >((m),__FILE__,__LINE__,__FUNCTION__))
#else
  #define nlTHROW(m)     throw (nsl::exception((m),__FILE__,__LINE__,"unknown"))
  #define nlTHROWV(t,m)  throw (nsl::var_exception< t >((m),__FILE__,__LINE__,"unknown"))
#endif


}       /* namespace nsl */
#endif  /* _NSL_EXCEPTION_H_ */