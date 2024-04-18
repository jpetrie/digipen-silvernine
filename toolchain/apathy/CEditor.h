/*!
        @file   CEditor.h
        @author Scott Smith
        @date   October 10, 2003

        @brief  Base class for plug-in editor windows
______________________________________________________________________________*/

#ifndef __CEDITOR_H__
#define __CEDITOR_H__

/*------------------------------------------------------------------------------
Includes
------------------------------------------------------------------------------*/
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>

#include "CTag.h"

/*!
    @class  CEditor
    @brief  Base class for editor windows, provides 'pluggability'
______________________________________________________________________________*/
class CEditor : public TForm
{
public:
        // ct & dt
        CEditor(Classes::TComponent* AOwner,unsigned long typecode = 0)
        :TForm(AOwner), kTypeCode(typecode)
        { }
        //virtual ~CEditor() { }

private:
        const CTag::ID kTypeCode;
        // tagfile * t1
        // tagfile * t2
};

#endif
 