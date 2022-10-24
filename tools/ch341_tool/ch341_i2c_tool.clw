; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=Cch341_i2c_toolDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ch341_i2c_tool.h"
LastPage=0

ClassCount=3
Class1=Cch341_i2c_toolApp
Class2=CAboutDlg
Class3=Cch341_i2c_toolDlg

ResourceCount=2
Resource1=IDD_ABOUTBOX
Resource2=IDD_ch341_i2c_tool_DIALOG

[CLS:Cch341_i2c_toolApp]
Type=0
BaseClass=CWinApp
HeaderFile=ch341_i2c_tool.h
ImplementationFile=ch341_i2c_tool.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=ch341_i2c_toolDlg.cpp
ImplementationFile=ch341_i2c_toolDlg.cpp
LastObject=IDOK

[CLS:Cch341_i2c_toolDlg]
Type=0
BaseClass=CDialog
HeaderFile=ch341_i2c_toolDlg.h
ImplementationFile=ch341_i2c_toolDlg.cpp
LastObject=IDC_COMBO_SPEED
Filter=D
VirtualFilter=dWC

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_ch341_i2c_tool_DIALOG]
Type=1
Class=Cch341_i2c_toolDlg
ControlCount=15
Control1=IDC_STATIC,static,1342308352
Control2=IDOK,button,1342242817
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_I2C_ADDR,edit,1350631560
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_I2C_REG_ADDR,edit,1350631560
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT_READ_LENGTH,edit,1350631552
Control9=IDC_BUTTON_READ,button,1342242816
Control10=IDC_EDIT_READ,edit,1350633484
Control11=IDC_BUTTON_CLR_READ,button,1342242816
Control12=IDC_COMBO_SPEED,combobox,1344348163
Control13=IDC_EDIT_WRITE,edit,1350631564
Control14=IDC_BUTTON_WRITE,button,1342242816
Control15=IDC_BUTTON_CLR_WRITE,button,1342242816

