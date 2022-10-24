// ch341_i2c_tool.h : main header file for the ch341_i2c_tool application
//

#if !defined(AFX_ch341_i2c_tool_H__93FC6065_1610_44E1_87DF_0DED44175C58__INCLUDED_)
#define AFX_ch341_i2c_tool_H__93FC6065_1610_44E1_87DF_0DED44175C58__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
    #error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"        // main symbols

/////////////////////////////////////////////////////////////////////////////
// Cch341_i2c_toolApp:
// See ch341_i2c_tool.cpp for the implementation of this class
//

class Cch341_i2c_toolApp : public CWinApp
{
public:
    Cch341_i2c_toolApp();

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(Cch341_i2c_toolApp)
    public:
    virtual BOOL InitInstance();
    //}}AFX_VIRTUAL

// Implementation

    //{{AFX_MSG(Cch341_i2c_toolApp)
        // NOTE - the ClassWizard will add and remove member functions here.
        //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ch341_i2c_tool_H__93FC6065_1610_44E1_87DF_0DED44175C58__INCLUDED_)
