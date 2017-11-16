
// CalculatorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Calculator.h"
#include "CalculatorDlg.h"
#include "afxdialogex.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCalculatorDlg 对话框



CCalculatorDlg::CCalculatorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CALCULATOR_DIALOG, pParent)
	, Answer(_T("0"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT, Answer);
	DDV_MaxChars(pDX, Answer, 255);
}

BEGIN_MESSAGE_MAP(CCalculatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_Percent, &CCalculatorDlg::OnBnClickedButtonPercent)
	ON_BN_CLICKED(IDC_BUTTON_ClearError, &CCalculatorDlg::OnBnClickedButtonClearerror)
	ON_BN_CLICKED(IDC_BUTTON_Clear, &CCalculatorDlg::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_Back, &CCalculatorDlg::OnBnClickedButtonBack)
	ON_BN_CLICKED(IDC_BUTTON_Divide, &CCalculatorDlg::OnBnClickedButtonDivide)
	ON_BN_CLICKED(IDC_BUTTON_Sqrt, &CCalculatorDlg::OnBnClickedButtonSqrt)
	ON_BN_CLICKED(IDC_BUTTON_7, &CCalculatorDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON_8, &CCalculatorDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON_9, &CCalculatorDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON_Multiply, &CCalculatorDlg::OnBnClickedButtonMultiply)
	ON_BN_CLICKED(IDC_BUTTON_Power, &CCalculatorDlg::OnBnClickedButtonPower)
	ON_BN_CLICKED(IDC_BUTTON_4, &CCalculatorDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON_5, &CCalculatorDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON_6, &CCalculatorDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON_Minus, &CCalculatorDlg::OnBnClickedButtonMinus)
	ON_BN_CLICKED(IDC_BUTTON_Cube, &CCalculatorDlg::OnBnClickedButtonCube)
	ON_BN_CLICKED(IDC_BUTTON_1, &CCalculatorDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_2, &CCalculatorDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON_3, &CCalculatorDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON_Plus, &CCalculatorDlg::OnBnClickedButtonPlus)
	ON_BN_CLICKED(IDC_BUTTON_Reciprocal, &CCalculatorDlg::OnBnClickedButtonReciprocal)
	ON_BN_CLICKED(IDC_BUTTON_PlusMinus, &CCalculatorDlg::OnBnClickedButtonPlusminus)
	ON_BN_CLICKED(IDC_BUTTON_0, &CCalculatorDlg::OnBnClickedButton0)
	ON_BN_CLICKED(IDC_BUTTON_Dot, &CCalculatorDlg::OnBnClickedButtonDot)
	ON_BN_CLICKED(IDC_BUTTON_Equal, &CCalculatorDlg::OnBnClickedButtonEqual)
	ON_COMMAND(ID_32772, &CCalculatorDlg::On32772)
	ON_COMMAND(ID_32773, &CCalculatorDlg::On32773)
	ON_COMMAND(ID_32774, &CCalculatorDlg::On32774)
END_MESSAGE_MAP()


// CCalculatorDlg 消息处理程序

BOOL CCalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCalculatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CCalculatorDlg::OnBnClickedButtonPercent()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (Display)
		;
	else {
		double num = _wtof(Answer);
		num = num1 * 0.01 * num;
		Answer.Format(_T("%g"), num);
	}
	UpdateData(FALSE);
}


void CCalculatorDlg::OnBnClickedButtonClearerror()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	Answer = _T("0");
	UpdateData(FALSE);
}


void CCalculatorDlg::OnBnClickedButtonClear()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	Answer = _T("0");
	Display = 1;
	op = 0;
	num1 = num2 = 0;
	UpdateData(FALSE);
}


void CCalculatorDlg::OnBnClickedButtonBack()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (Answer.GetAt(Answer.GetLength()-1) == '.')
		Dot = 0;
	if (Answer.GetLength() > 1)
		Answer.Delete(Answer.GetLength()-1);
	else
		Answer = _T("0");
		
	UpdateData(FALSE);
}


void CCalculatorDlg::OnBnClickedButtonDivide()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	num1 = _wtof(Answer.GetBuffer(0));
	Display = 1;
	op = 4;
	UpdateData(FALSE);
}


void CCalculatorDlg::OnBnClickedButtonSqrt()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	double num = _wtof(Answer);
	num = sqrt(num);
	Display = 1;
	num2 = num;
	Answer.Format(_T("%g"), num);

	UpdateData(FALSE);
}


void CCalculatorDlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (Display) {
		Answer = _T("0");
		Display = 0;
	}
	if (Answer == _T("0"))
		Answer = _T("7");
	else
		Answer.Append(_T("7"));
	UpdateData(FALSE);
}


void CCalculatorDlg::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (Display) {
		Answer = _T("0");
		Display = 0;
	}
	if (Answer == _T("0"))
		Answer = _T("8");
	else
		Answer.Append(_T("8"));
	UpdateData(FALSE);
}


void CCalculatorDlg::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (Display) {
		Answer = _T("0");
		Display = 0;
	}
	if (Answer == _T("0"))
		Answer = _T("9");
	else
		Answer.Append(_T("9"));
	UpdateData(FALSE);
}


void CCalculatorDlg::OnBnClickedButtonMultiply()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	num1 = _wtof(Answer.GetBuffer(0));
	Display = 1;
	op = 3;
	UpdateData(FALSE);
}


void CCalculatorDlg::OnBnClickedButtonPower()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	double num = _wtof(Answer);
	num = pow(num, 2);
	Display = 1;
	num2 = num;
	Answer.Format(_T("%g"), num);

	UpdateData(FALSE);
}


void CCalculatorDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (Display) {
		Answer = _T("0");
		Display = 0;
	}
	if (Answer == _T("0"))
		Answer = _T("4");
	else
		Answer.Append(_T("4"));
	UpdateData(FALSE);
}


void CCalculatorDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (Display) {
		Answer = _T("0");
		Display = 0;
	}
	if (Answer == _T("0"))
		Answer = _T("5");
	else
		Answer.Append(_T("5"));
	UpdateData(FALSE);
}


void CCalculatorDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (Display) {
		Answer = _T("0");
		Display = 0;
	}
	if (Answer == _T("0"))
		Answer = _T("6");
	else
		Answer.Append(_T("6"));
	UpdateData(FALSE);
}


void CCalculatorDlg::OnBnClickedButtonMinus()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	num1 = _wtof(Answer.GetBuffer(0));
	Display = 1;
	op = 2;
	UpdateData(FALSE);
}


void CCalculatorDlg::OnBnClickedButtonCube()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	double num = _wtof(Answer);
	num = pow(num, 3);
	Display = 1;
	num2 = num;
	Answer.Format(_T("%g"), num);

	UpdateData(FALSE);
}


void CCalculatorDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (Display) {
		Answer = _T("0");
		Display = 0;
	}
	if (Answer == _T("0"))
		Answer = _T("1");
	else
		Answer.Append(_T("1"));
	UpdateData(FALSE);
}


void CCalculatorDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (Display) {
		Answer = _T("0");
		Display = 0;
	}
	if (Answer == _T("0"))
		Answer = _T("2");
	else
		Answer.Append(_T("2"));
	UpdateData(FALSE);
}


void CCalculatorDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (Display) {
		Answer = _T("0");
		Display = 0;
	}
	if (Answer == _T("0"))
		Answer = _T("3");
	else
		Answer.Append(_T("3"));
	UpdateData(FALSE);
}


void CCalculatorDlg::OnBnClickedButtonPlus()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	num1 = _wtof(Answer.GetBuffer(0));
	Display = 1;
	op = 1;
	UpdateData(FALSE);
}


void CCalculatorDlg::OnBnClickedButtonReciprocal()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	double num = _wtof(Answer);
	if (num == 0)
		;
	else
		num = 1 / num;
	Display = 1;
	num2 = num;
	Answer.Format(_T("%g"), num);
		
	UpdateData(FALSE);
}


void CCalculatorDlg::OnBnClickedButtonPlusminus()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (Answer == _T("0"))
		;
	else if (Minus) {
		Answer.Remove('-');
		Minus = 0;
	}
	else {
		Answer = CString(_T("-")) + Answer;
		Minus = 1;
	}
	UpdateData(FALSE);
}


void CCalculatorDlg::OnBnClickedButton0()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (Display) {
		Answer = _T("0");
		Display = 0;
	}
	if (Answer == _T("0"))
		;
	else
		Answer.Append(_T("0"));
	UpdateData(FALSE);
}


void CCalculatorDlg::OnBnClickedButtonDot()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (Display) {
		Answer = _T("0");
		Display = 0;
	}
	if (Dot)
		;
	else {
		Answer.Append(_T("."));
		Dot = 1;
	}
	UpdateData(FALSE);
}


void CCalculatorDlg::OnBnClickedButtonEqual()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (Display) {
		switch (op)
		{
		case 1: num1 = num1 + num2;// +
			Answer.Format(_T("%g"), num1);
			break;
		case 2: num1 = num1 - num2;// -
			Answer.Format(_T("%g"), num1);
			break;
		case 3: num1 = num1 * num2;// *
			Answer.Format(_T("%g"), num1);
			break;
		case 4: num1 = num1 / num2;// /
			Answer.Format(_T("%g"), num1);
			break;
		default:
			break;
		}
		Dot = 0;
	}
	else {
		num2 = _wtof(Answer.GetBuffer(0));
		switch (op)
		{
		case 1: num1 = num1 + num2;// +
			Answer.Format(_T("%g"), num1);
			break;
		case 2: num1 = num1 - num2;// -
			Answer.Format(_T("%g"), num1);
			break;
		case 3: num1 = num1 * num2;// *
			Answer.Format(_T("%g"), num1);
			break;
		case 4: num1 = num1 / num2;// /
			Answer.Format(_T("%g"), num1);
			break;
		default:
			break;
		}
		Dot = 0;
		Display = 1;
	}
	UpdateData(FALSE);
}


void CCalculatorDlg::On32772()
{
	// TODO: 在此添加命令处理程序代码
	OnBnClickedButtonClear();
}


void CCalculatorDlg::On32773()
{
	// TODO: 在此添加命令处理程序代码
	CAboutDlg ab;
	ab.DoModal();
}


void CCalculatorDlg::On32774()
{
	// TODO: 在此添加命令处理程序代码
	SendMessage(WM_CLOSE);
}
