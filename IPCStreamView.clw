; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CFocusAssit
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "IPCStreamView.h"

ClassCount=5
Class1=CIPCStreamViewApp
Class2=CIPCStreamViewDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_IPCSTREAMVIEW_DIALOG
Resource4=IDD_DIALOG_FOCUS_ASSIST
Class4=CFocusAssit
Class5=CPreview
Resource5=IDD_DIALOG_PREVIEW

[CLS:CIPCStreamViewApp]
Type=0
HeaderFile=IPCStreamView.h
ImplementationFile=IPCStreamView.cpp
Filter=N
LastObject=CIPCStreamViewApp

[CLS:CIPCStreamViewDlg]
Type=0
HeaderFile=IPCStreamViewDlg.h
ImplementationFile=IPCStreamViewDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CIPCStreamViewDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=IPCStreamViewDlg.h
ImplementationFile=IPCStreamViewDlg.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_IPCSTREAMVIEW_DIALOG]
Type=1
Class=CIPCStreamViewDlg
ControlCount=1
Control1=IDC_TAB_MAIN,SysTabControl32,1342177280

[DLG:IDD_DIALOG_FOCUS_ASSIST]
Type=1
Class=CFocusAssit
ControlCount=15
Control1=IDC_STATIC_VIEW_AREA,button,1342210055
Control2=IDC_STATIC_TIPS,button,1342210055
Control3=IDC_STATIC_FOCUS_ASSIST,button,1342210055
Control4=IDC_LIST_TIPS,listbox,1345388803
Control5=IDC_BUTTON_SAMPLE,button,1342242816
Control6=IDC_BUTTON_START_FOCUS,button,1342242816
Control7=IDC_BUTTON_STOP_FOCUS2,button,1342242816
Control8=IDC_IPADDRESS1,SysIPAddress32,1342242816
Control9=IDC_STATIC_IP_ADDRESS,static,1342308352
Control10=IDC_STATIC_PORT,static,1342308352
Control11=IDC_EDIT_PORT,edit,1350631552
Control12=IDC_BUTTON_CONNECT,button,1342242816
Control13=IDC_STATIC_INFO,button,1342210055
Control14=IDC_COMBO_ALARM,combobox,1344340226
Control15=IDC_STATIC_ALARM,static,1342308352

[DLG:IDD_DIALOG_PREVIEW]
Type=1
Class=CPreview
ControlCount=0

[CLS:CFocusAssit]
Type=0
HeaderFile=FocusAssit.h
ImplementationFile=FocusAssit.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_IPADDRESS1
VirtualFilter=dWC

[CLS:CPreview]
Type=0
HeaderFile=Preview.h
ImplementationFile=Preview.cpp
BaseClass=CDialog
Filter=D
LastObject=CPreview
VirtualFilter=dWC

