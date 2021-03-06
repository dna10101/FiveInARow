
// CalculatorDlg.h: 头文件
//

#pragma once
#include"Player.h"
#include"ComputerPlayer.h"
#include"PersonPlayer.h"

// CCalculatorDlg 对话框
class CCalculatorDlg : public CDialogEx
{
// 构造
public:
	CCalculatorDlg(CWnd* pParent = nullptr);	// 标准构造函数
	CCalculatorDlg(class Player *p1, class Player *p2, class ChessBoard *board, CWnd* pParent = nullptr);
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
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	void setFirst(boolean isP1);

private:
	CMenu m_Menu;
	boolean isWin;
	boolean isP1;
	Player *p1;
	Player *p2;
	ChessBoard *board;
public:
	afx_msg void On32772();
	afx_msg void OnTimerIdVisibilityTimer();
};
