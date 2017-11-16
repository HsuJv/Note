
// CalculatorDlg.h : 头文件
//

#pragma once


// CCalculatorDlg 对话框
class CCalculatorDlg : public CDialogEx
{
// 构造
public:
	CCalculatorDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CALCULATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	double num1, num2;
	bool Display = 0;
	int op = 0;
	bool Dot = 0;
	bool Minus = 0;

public:
	CString Answer;
	afx_msg void OnBnClickedButtonPercent();
	afx_msg void OnBnClickedButtonClearerror();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButtonBack();
	afx_msg void OnBnClickedButtonDivide();
	afx_msg void OnBnClickedButtonSqrt();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButtonMultiply();
	afx_msg void OnBnClickedButtonPower();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButtonMinus();
	afx_msg void OnBnClickedButtonCube();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButtonPlus();
	afx_msg void OnBnClickedButtonReciprocal();
	afx_msg void OnBnClickedButtonPlusminus();
	afx_msg void OnBnClickedButton0();
	afx_msg void OnBnClickedButtonDot();
	afx_msg void OnBnClickedButtonEqual();
	afx_msg void On32772();
	afx_msg void On32773();
	afx_msg void On32774();
};
