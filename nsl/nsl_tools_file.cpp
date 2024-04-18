/*! =========================================================================

      @file    nsl_tools_file.cpp
      @brief   File tools implementation.

    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "nsl_common.h"
#include "nsl_tools_file.h"


/*                                                                  functions
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
nsl::bool_t nsl::fdexists(const std::string &pn)
/*! @brief Determine if a file or directory exists.

    This function does not report any information about the type of the entity
    referred to by pn (e.g., it could be a file or a directory). To retrieve
    such information, use fdis_file() or fdis_directory().
 
    @param pn  The pathname of the file.
    
    @return
    True if the file or directory exists, false otherwise.
*/
{
WIN32_FIND_DATA  tFD;
HANDLE           tFH;
bool             tExists;

  tFH = FindFirstFile(pn.c_str(),&tFD);
  tExists = (tFH != INVALID_HANDLE_VALUE);
  FindClose(tFH);
  return (tExists);
}


/*  _________________________________________________________________________ */
nsl::bool_t nsl::fdis_file(const std::string &pn)
/*! @brief Determine if a pathname refers to a file.

    @param pn  The pathname.
    
    @return
    True if the pathname refers to a file, false if the pathname is invalid or
    refers to a directory.
*/
{
WIN32_FIND_DATA  tFD;
HANDLE           tFH;
nsl::bool_t      tValid;

  tFH = FindFirstFile(pn.c_str(),&tFD);
  tValid = (tFH != INVALID_HANDLE_VALUE && !(tFD.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY));
  FindClose(tFH);
  return (tValid);
}


/*  _________________________________________________________________________ */
nsl::bool_t nsl::fdis_directory(const std::string &pn)
/*! @brief Determine if a pathname refers to a directory.

    @param pn  The pathname.
    
    @return
    True if the pathname refers to a directory, false if the pathname is invalid
    or refers to a file.
*/
{
WIN32_FIND_DATA  tFD;
HANDLE           tFH;
nsl::bool_t      tValid;

  tFH = FindFirstFile(pn.c_str(),&tFD);
  tValid = (tFH != INVALID_HANDLE_VALUE && !!(tFD.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY));
  FindClose(tFH);
  return (tValid);
}


/*  _________________________________________________________________________ */
nsl::size_t nsl::fdsize(const std::string &fn)
/*! @brief Determine the size of a file.

    @param fn  The filename.
    
    @return
    The size of the file, in bytes, or 0 if fn is invalid or specifies a file.
*/
{
WIN32_FIND_DATA  tFD;
HANDLE           tFH;
nsl::size_t      tSz = 0;

  tFH = FindFirstFile(fn.c_str(),&tFD);
  if(tFH != INVALID_HANDLE_VALUE)
    tSz = tFD.nFileSizeLow;
  
  FindClose(tFH);
  return (tSz);
}


/*  _________________________________________________________________________ */
nsl::size_t nsl::fdenum_files(const std::string &pn,nsl::stringlist &contents)
/*! @brief Retrieves the files within the specified directory.

    EnumFiles() returns a list of the names of all files within the
    specified directory.

    @param pn        The pathname of the directory to list.
    @param contents  A list of strings to be filled out with the contents of the
                     specified directory. The existing contents of the list will
                     be destroyed.
*/
{
WIN32_FIND_DATA  tFD;  // Find data.
HANDLE           tFH;  // Find handle.
std::string      tSearchPath = pn;
nsl::size_t      tCount = 0;

  // Clear the list.
  contents.clear();
 
  // Construct the search path.
  nsl::stpslash(tSearchPath);
  tSearchPath += "*";
  tFH = FindFirstFile(tSearchPath.c_str(),&tFD);
  if(tFH != INVALID_HANDLE_VALUE)
  {
    do
    {
      // Do not find directories.
      if(!(tFD.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
       tCount++,contents.push_back(tFD.cFileName);
    }
    while(FindNextFile(tFH,&tFD));
  }
  
  // Clean up.
  FindClose(tFH);
  return (tCount);
}


/*  _________________________________________________________________________ */
nsl::size_t nsl::fdenum_directories(const std::string &pn,nsl::stringlist &contents)
/*! @brief Retrieves the subdirectories within the specified directory.

    EnumFiles() returns a list of the names of all subdirectories within the
    specified directory.

    @param pn        The pathname of the directory to list.
    @param contents  A list of strings to be filled out with the contents of the
                     specified directory. The existing contents of the list will
                     be destroyed.
*/
{
WIN32_FIND_DATA  tFD;  // Find data.
HANDLE           tFH;  // Find handle.
std::string      tSearchPath = pn;
nsl::size_t      tCount = 0;

  // Clear the list.
  contents.clear();
 
  // Construct the search path.
  nsl::stpslash(tSearchPath);
  tSearchPath += "*";
  tFH = FindFirstFile(tSearchPath.c_str(),&tFD);
  if(tFH != INVALID_HANDLE_VALUE)
  {
    do
    {
      // Only find directories.
      if(tFD.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
       tCount++,contents.push_back(tFD.cFileName);
    }
    while(FindNextFile(tFH,&tFD));
  }
  
  // Clean up.
  FindClose(tFH);
  return (tCount);
}


/*  _________________________________________________________________________ */
nsl::bool_t nsl::fdremove(const std::string &fn)
/*! @brief Deletes a file, if it exists.

    @param fn  The pathname of the file.
    
    @return
    True if the file was deleted, false otherwise.
*/
{
  return (!!DeleteFile(fn.c_str()));
}
