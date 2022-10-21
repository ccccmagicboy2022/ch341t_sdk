// ch341_i2c_toolDlg.h : header file
//

#if !defined(AFX_ch341_i2c_toolDLG_H__74968387_2A6C_443E_AB2B_D653686611F3__INCLUDED_)
#define AFX_ch341_i2c_toolDLG_H__74968387_2A6C_443E_AB2B_D653686611F3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// Cch341_i2c_toolDlg dialog

class Cch341_i2c_toolDlg : public CDialog
{
// Construction
public:
	Cch341_i2c_toolDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(Cch341_i2c_toolDlg)
	enum { IDD = IDD_ch341_i2c_tool_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cch341_i2c_toolDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(Cch341_i2c_toolDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
    afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ch341_i2c_toolDLG_H__74968387_2A6C_443E_AB2B_D653686611F3__INCLUDED_)
