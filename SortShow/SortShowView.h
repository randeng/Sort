
// SortShowView.h : CSortShowView ��Ľӿ�
//

#pragma once

#include "resource.h"
#include "afxwin.h"
#include "afxcmn.h"
#include <stdlib.h>
#include "Sort.h"

class CSortShowView : public CFormView
{
protected: // �������л�����
	CSortShowView();
	DECLARE_DYNCREATE(CSortShowView)

public:
	enum{ IDD = IDD_SORTSHOW_FORM };

// ����
public:
	CSortShowDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CSortShowView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CComboBox m_cbSortType;
	CSliderCtrl m_sliderSpeed;
	afx_msg void OnBnClickedButtonBeginsort();
	afx_msg void OnBnClickedButtonPause();
	afx_msg void OnBnClickedButtonRestart();
	afx_msg void OnCbnSelchangeComboSorttype();
	afx_msg void OnNMCustomdrawSliderSpeed(NMHDR *pNMHDR, LRESULT *pResult);
	int checInputData();
	void spwanData();
	void ChoseSortType();

private:
	BOOL isPause;
	BOOL isFlished = false;
	int * data=NULL;
	int maxSize = 100000;
	int maxHeight;
	int maxWidth;
	int flishIndex = 0;
	int maxCashLength;
	long costTime;
	double perWidth;
	CList<int>cashData;
	CString sortType[11];
	CString curSel;
	CRect startRect;
	CPoint startPoint;
	Sort<int> sort;
public:
	int m_Speed;
	int m_Size;
	CString m_strSpeed;
	CString m_strCostTime;
	CString m_strComplete;
};

#ifndef _DEBUG  // SortShowView.cpp �еĵ��԰汾
inline CSortShowDoc* CSortShowView::GetDocument() const
   { return reinterpret_cast<CSortShowDoc*>(m_pDocument); }
#endif

