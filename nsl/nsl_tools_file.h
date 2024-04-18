/*! =========================================================================
      
      @file    nsl_tools_file.h
      @brief   File tools interface.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _NSL_TOOLS_FILE_H_
#define _NSL_TOOLS_FILE_H_


/*                                                                   includes
----------------------------------------------------------------------------- */
                
#include "nsl_common.h"

#include "nsl_tools_string.h"

namespace nsl
{


/*                                                                 prototypes
----------------------------------------------------------------------------- */

// query
bool_t fdexists(const std::string &pn);
bool_t fdis_file(const std::string &pn);
bool_t fdis_directory(const std::string &pn);

// size and properties
size_t fdsize(const std::string &fn);

// enumeration
size_t fdenum_files(const std::string &pn,nsl::stringlist &contents);
size_t fdenum_directories(const std::string &pn,nsl::stringlist &contents);

// removal
bool_t fdremove(const std::string &fn);
//FIXME replace enum functions with sth that can enum based on user mask function callback and also do a "for each" thing
}       /* namespace nsl */
#endif  /* _NSL_TOOLS_FILE_H_ */