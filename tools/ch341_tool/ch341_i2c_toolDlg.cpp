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
    //}}AFX_DATA_INIT
    // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cch341_i2c_toolDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(Cch341_i2c_toolDlg)
    DDX_Control(pDX, IDC_EDIT_WRITE, m_write_data);
    DDX_Control(pDX, IDC_EDIT_READ, m_read_data);
    DDX_Control(pDX, IDC_EDIT_READ_LENGTH, m_read_length);
    DDX_Control(pDX, IDC_EDIT_I2C_REG_ADDR, m_i2c_reg_addr);
    DDX_Control(pDX, IDC_EDIT_I2C_ADDR, m_i2c_addr);
    DDX_Control(pDX, IDC_COMBO_SPEED, m_speed);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(Cch341_i2c_toolDlg, CDialog)
    //{{AFX_MSG_MAP(Cch341_i2c_toolDlg)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_WM_DESTROY()
    ON_WM_KEYUP()
    ON_BN_CLICKED(IDC_BUTTON_CLR_READ, OnButtonClrRead)
    ON_BN_CLICKED(IDC_BUTTON_CLR_WRITE, OnButtonClrWrite)
    ON_BN_CLICKED(IDC_BUTTON_READ, OnButtonRead)
    ON_BN_CLICKED(IDC_BUTTON_WRITE, OnButtonWrite)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CALLBACK CH341_NOTIFY_ROUTINE (ULONG    iEventStatus)
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
        this->SetWindowText("CH341**plug out");
    }
    else
    {
        this->SetWindowText("CH341**plug in");
    }
}

/////////////////////////////////////////////////////////////////////////////
// Cch341_i2c_toolDlg message handlers

BOOL Cch341_i2c_toolDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    ULONG ver;
    DWORD io_val = 0;
    CString temp_str;

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
    SetIcon(m_hIcon, TRUE);            // Set big icon
    SetIcon(m_hIcon, FALSE);        // Set small icon

    // TODO: Add extra initialization here
    if(CH341OpenDevice(0) == INVALID_HANDLE_VALUE)
    {
        this->SetWindowText("CH341**plug out");
    }
    else
    {
        this->SetWindowText("CH341**plug in");
    }
    ver = CH341GetVersion();
    CH341SetDeviceNotify(0, NULL, CH341_NOTIFY_ROUTINE);

    CH341GetStatus(0, &io_val);
    temp_str.Format("ch341 io: 0x%08X\r\n", io_val);
    TRACE(temp_str);

    m_speed.SetCurSel(CH341_I2C_SPEED_400K);
    m_i2c_addr.SetWindowText("E2");
    m_i2c_reg_addr.SetWindowText("00");
    m_read_length.SetWindowText("1");
    m_read_data.SetWindowText("");
    m_write_data.SetWindowText("");

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

void Cch341_i2c_toolDlg::OnButtonClrRead()
{
    // TODO: Add your control notification handler code here
    m_read_data.SetWindowText("");
}

void Cch341_i2c_toolDlg::OnButtonClrWrite()
{
    // TODO: Add your control notification handler code here
    m_write_data.SetWindowText("");
}

void Cch341_i2c_toolDlg::OnButtonRead()
{
    // TODO: Add your control notification handler code here
    // read i2c bus
    UINT addr = 0x00;
    UINT reg_addr = 0x00;
    UINT read_len = 0;
    CString temp_str;
    CString temp_str2;
    UCHAR wbuffer[mMAX_BUFFER_LENGTH]="";
    UCHAR rbuffer[mMAX_BUFFER_LENGTH]="";
    DWORD i = 0;

    m_i2c_addr.GetWindowText(temp_str);
    addr = mHexStrToBcd(temp_str);

    if (addr != -1 && addr < 256)
    {
        temp_str.Format("i2c addr: 0x%02X\r\n", addr);
        TRACE(temp_str);
    }
    else
    {
        AfxMessageBox("I2C address error!", MB_OK|MB_ICONSTOP);
        return;
    }

    m_i2c_reg_addr.GetWindowText(temp_str);
    reg_addr = mHexStrToBcd(temp_str);

    if (reg_addr != -1 && reg_addr < 256)
    {
        temp_str.Format("i2c reg addr: 0x%02X\r\n", reg_addr);
        TRACE(temp_str);
    }
    else
    {
        AfxMessageBox("I2C reg address error!", MB_OK|MB_ICONSTOP);
        return;
    }

    m_read_length.GetWindowText(temp_str);
    read_len = _tcstoul(temp_str, NULL, 10);

    if (read_len != 0)
    {
        temp_str.Format("i2c read length: %d\r\n", read_len);
        TRACE(temp_str);
    }
    else
    {
        AfxMessageBox("I2C read length error!", MB_OK|MB_ICONSTOP);
        return;
    }

    if (!CH341SetStream(0, m_speed.GetCurSel()))
    {
        AfxMessageBox("I2C speed set error!", MB_OK|MB_ICONSTOP);
        return;
    }

    wbuffer[0] = 0x80 | addr;
    wbuffer[1] = reg_addr;

    try
    {
        if(!CH341StreamI2C (0, 2, &wbuffer[0], read_len, &rbuffer[0] ))
        {
            AfxMessageBox("I2C stream read error!", MB_OK|MB_ICONSTOP);
            return;
        }
        else
        {
            temp_str2.Format("");
            for(i=0;i<read_len;i++)
            {
                temp_str.Format("%02X ", rbuffer[i]);
                temp_str2 += temp_str;
            }
            temp_str2 += "\r\n";
            TRACE(temp_str2);
            m_read_data.SetWindowText(temp_str2);
        }
    }
    catch( CException * )
    {
        TRACE("Error: %d",GetLastError());
    }
}

void Cch341_i2c_toolDlg::OnButtonWrite()
{
    // TODO: Add your control notification handler code here
    // write i2c bus
    UINT addr = 0x00;
    UINT reg_addr = 0x00;
    UINT read_len = 0;
    CString temp_str;
    CString temp_str2;
    UCHAR wbuffer[mMAX_BUFFER_LENGTH]="";
    DWORD i = 0;
    UINT write_dat = 0x00;

    m_i2c_addr.GetWindowText(temp_str);
    addr = mHexStrToBcd(temp_str);

    if (addr != -1 && addr < 256)
    {
        temp_str.Format("i2c addr: 0x%02X\r\n", addr);
        TRACE(temp_str);
    }
    else
    {
        AfxMessageBox("I2C address error!", MB_OK|MB_ICONSTOP);
        return;
    }

    m_i2c_reg_addr.GetWindowText(temp_str);
    reg_addr = mHexStrToBcd(temp_str);

    if (reg_addr != -1 && reg_addr < 256)
    {
        temp_str.Format("i2c reg addr: 0x%02X\r\n", reg_addr);
        TRACE(temp_str);
    }
    else
    {
        AfxMessageBox("I2C reg address error!", MB_OK|MB_ICONSTOP);
        return;
    }

    m_read_length.GetWindowText(temp_str);
    read_len = _tcstoul(temp_str, NULL, 10);

    if (read_len != 0)
    {
        temp_str.Format("i2c read length: %d\r\n", read_len);
        TRACE(temp_str);
    }
    else
    {
        AfxMessageBox("I2C read length error!", MB_OK|MB_ICONSTOP);
        return;
    }

    if (!CH341SetStream(0, m_speed.GetCurSel()))
    {
        AfxMessageBox("I2C speed set error!", MB_OK|MB_ICONSTOP);
        return;
    }

    m_write_data.GetWindowText(temp_str);
    write_dat = mHexStrToBcd(temp_str);

    if (write_dat != -1 && write_dat < 256)
    {
        temp_str.Format("i2c write data: 0x%02X\r\n", write_dat);
        TRACE(temp_str);
    }
    else
    {
        AfxMessageBox("I2C write data error!", MB_OK|MB_ICONSTOP);
        return;
    }

    wbuffer[0] = addr;
    wbuffer[1] = reg_addr;
    wbuffer[2] = (unsigned char)write_dat;

    try
    {
        if(!CH341StreamI2C (0, 3, &wbuffer[0], 0, NULL ))
        {
            AfxMessageBox("I2C stream write error!", MB_OK|MB_ICONSTOP);
            return;
        }
        else
        {
            //pass
        }
    }
    catch( CException * )
    {
        TRACE("Error: %d",GetLastError());
    }
}

LONG Cch341_i2c_toolDlg::mHexStrToBcd( CString str )
{
    char mlen,i=0;
    UCHAR iChar=0,Char[9]="";
    UINT mBCD=0,de=1;
    mlen=strlen(str);
    memcpy(Char,str,mlen);
    for(i=mlen-1;i>=0;i--)
    {    iChar=Char[i];
        if ( iChar >= '0' && iChar <= '9' )
            mBCD = mBCD+(iChar -'0')*de;
        else if ( iChar >= 'A' && iChar <= 'F' )
            mBCD =mBCD+ (iChar - 'A' + 0x0a)*de;
        else if ( iChar >= 'a' && iChar <= 'f' )
            mBCD =mBCD+ (iChar - 'a' + 0x0a)*de;
        else return(-1);
        de*=16;
    }
    return(mBCD);
}

