// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__5312035C_F5F2_407A_BE0A_ABEC652EE398__INCLUDED_)
#define AFX_STDAFX_H__5312035C_F5F2_407A_BE0A_ABEC652EE398__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN        // Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>        // MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>            // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT


#pragma comment (lib, "3rd_part/CH341DLL/CH341DLL.LIB")
#include "3rd_part/CH341DLL/CH341DLL.H"

typedef enum {
CH341_I2C_SPEED_20K = 0,
CH341_I2C_SPEED_100K,
CH341_I2C_SPEED_400K,
CH341_I2C_SPEED_750K,
};

/////////////////////////////////////


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__5312035C_F5F2_407A_BE0A_ABEC652EE398__INCLUDED_)
