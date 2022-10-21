// ch341_i2c_toolDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ch341_i2c_tool.h"
#include "ch341_i2c_toolDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Cch341_i2c_toolDlg dialog

Cch341_i2c_toolDlg::Cch341_i2c_toolDlg(CWnd* pParent /*=NULL*/)
	: CDialog(Cch341_i2c_toolDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(Cch341_i2c_toolDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cch341_i2c_toolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cch341_i2c_toolDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(Cch341_i2c_toolDlg, CDialog)
	//{{AFX_MSG_MAP(Cch341_i2c_toolDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
    ON_WM_KEYUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CALLBACK CH341_NOTIFY_ROUTINE (ULONG	iEventStatus)
{
    ::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), WM_KEYUP, iEventStatus, 0);
}

void Cch341_i2c_toolDlg::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{	
	ULONG iEventStatus;
	iEventStatus=nChar;

    switch(iEventStatus)
    {
    case CH341_DEVICE_ARRIVAL:
        AfxMessageBox("plugin usb");
        break;
    case CH341_DEVICE_REMOVE:
        AfxMessageBox("remove usb");
        CH341CloseDevice(0);
        break;
    case CH341_DEVICE_REMOVE_PEND:
        break;
    default:
        break;    
    }

	if(CH341OpenDevice(0) == INVALID_HANDLE_VALUE)
	{
	    this->SetWindowText("CH341**设备0已拔出");
	}
	else
	{
	    this->SetWindowText("CH341**设备0已插入");
	}
}

/////////////////////////////////////////////////////////////////////////////
// Cch341_i2c_toolDlg message handlers

BOOL Cch341_i2c_toolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

    ULONG ver;

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	if(CH341OpenDevice(0) == INVALID_HANDLE_VALUE)
	{
		this->SetWindowText("CH341**设备0已拔出");
	}
	else
	{
		this->SetWindowText("CH341**设备0已插入");
	}
    ver = CH341GetVersion();
    CH341SetDeviceNotify(0, NULL, CH341_NOTIFY_ROUTINE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void Cch341_i2c_toolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void Cch341_i2c_toolDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR Cch341_i2c_toolDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void Cch341_i2c_toolDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
    CH341CloseDevice(0);
	CH341SetDeviceNotify(0, NULL, NULL);  //注销监视通知
}
