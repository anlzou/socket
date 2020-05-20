// MfcTcpServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MfcTcpServer.h"
#include "MfcTcpServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//anlzou add
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



//anlzou end.

/////////////////////////////////////////////////////////////////////////////
// CMfcTcpServerDlg dialog

CMfcTcpServerDlg::CMfcTcpServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMfcTcpServerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMfcTcpServerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMfcTcpServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMfcTcpServerDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMfcTcpServerDlg, CDialog)
	//{{AFX_MSG_MAP(CMfcTcpServerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_SEND, OnSend)
	ON_MESSAGE(WM_SOCKET,OnSocket)
END_MESSAGE_MAP()


//anlzou add
CTCPDlg::CTCPDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTCPDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTCPDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	n=0;
}

void CTCPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCPDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCPDlg, CDialog)
	//{{AFX_MSG_MAP(CTCPDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SEND, OnSend)
	ON_MESSAGE(WM_SOCKET,OnSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



//anlzou add end.

/////////////////////////////////////////////////////////////////////////////
// CMfcTcpServerDlg message handlers

BOOL CMfcTcpServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//anlzou add
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



	//anlzou add end.

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	//anlzou add
	addr.sin_family=AF_INET;
	addr.sin_port=htons(80);
	addr.sin_addr.S_un.S_addr=INADDR_ANY;
	s=::socket(AF_INET,SOCK_STREAM,0);
	::bind(s,(sockaddr*)&addr,sizeof(addr));
	::listen(s,5);
	::WSAAsyncSelect(s,this->m_hWnd,WM_SOCKET,FD_ACCEPT|FD_READ);
	GetDlgItem(IDC_TEXT)->EnableWindow(false);
	GetDlgItem(IDC_ADDR)->SetWindowText("�����������Ѿ�������");
	
	//anlzou add end.
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

//anlzou add
void CTCPDlg::OnSysCommand(UINT nID, LPARAM lParam)
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


//anlzou add end.

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMfcTcpServerDlg::OnPaint() 
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
HCURSOR CMfcTcpServerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


//anlzou add
void CTCPDlg::OnSocket(WPARAM wParam,LPARAM lParam)
{
	CString str13;
	char cs[100] = {0};
	switch (lParam)
	{
	case FD_ACCEPT:
		{
			int lenth=sizeof(add1);     
			s1=::accept(s,(sockaddr*)&add1,&lenth);
			n=n+1;
			str13.Format("��%d�ͻ��Ѿ���������",n);
			str13+=::inet_ntoa(add1.sin_addr);
			str13+="\r\n��½\r\n";
			GetDlgItem(IDC_TEXT)->SetWindowText(str13);
		}
		break;
		
	case FD_READ:
		{ 
			CString num="";
			::recv(s1,cs,100,0);
			GetDlgItem(IDC_TEXT)->GetWindowText(num);
			num+="\r\n";
			num+=(LPTSTR)::inet_ntoa(add1.sin_addr);
			num+="����˵��";
			num+=(LPTSTR)cs;
			GetDlgItem(IDC_TEXT)->SetWindowText(num);}
		break;
		}
}


void CTCPDlg::OnSend() 
{
	// TODO: Add your control notification handler code here
	CString str="";
	GetDlgItem(IDC_SENDTEXT)->GetWindowText(str);
	if(str=="")
	{
		MessageBox("��Ϣ����Ϊ�գ�");
	}
	else
	{
		if(::send(s1,str.GetBuffer(1),str.GetLength(),0)!=SOCKET_ERROR)
		{
			GetDlgItem(IDC_TEXT)->GetWindowText(str);
			str+="��Ϣ�Ѿ����͵��ͻ��ˣ�\r\n";
			GetDlgItem(IDC_TEXT)->SetWindowText(str);
		}
		else
		{
			GetDlgItem(IDC_TEXT)->SetWindowText("��Ϣ����ʧ�ܣ�\r\n");
		}
	}
}

//anlzou add end.