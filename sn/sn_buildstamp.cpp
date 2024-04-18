/*! =========================================================================
   
      @file    sn_buildstamp.cpp
      @brief   Silver Nine buildstamp source file.
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "sn_buildstamp.h"
#include "sn_buildstampdefines.h"

/*                                                                  functions
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
std::string build_stamp(void)
/*! @brief Return build stamp.
    @return    The build stamp.
*/
{
  return (SN_BUILDSTAMP);
}


/*  _________________________________________________________________________ */
int build_id(void)
/*! @brief Return build ID.
    @return    The build ID.
*/
{
  return (SN_BUILDID);
}
