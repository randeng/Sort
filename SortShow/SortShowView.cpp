
// SortShowView.cpp : CSortShowView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "SortShow.h"
#endif

#include "SortShowDoc.h"
#include "SortShowView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSortShowView

IMPLEMENT_DYNCREATE(CSortShowView, CFormView)

BEGIN_MESSAGE_MAP(CSortShowView, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_BeginSort, &CSortShowView::OnBnClickedButtonBeginsort)
	ON_BN_CLICKED(IDC_BUTTON_Pause, &CSortShowView::OnBnClickedButtonPause)
	ON_BN_CLICKED(IDC_BUTTON_Restart, &CSortShowView::OnBnClickedButtonRestart)
	ON_CBN_SELCHANGE(IDC_COMBO_SortType, &CSortShowView::OnCbnSelchangeComboSorttype)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_Speed, &CSortShowView::OnNMCustomdrawSliderSpeed)
END_MESSAGE_MAP()

// CSortShowView 构造/析构

CSortShowView::CSortShowView()
	: CFormView(CSortShowView::IDD)
	, m_Speed(1)
	, m_strSpeed(_T(""))
	, m_Size(100)
	, m_strCostTime(_T(""))
	, m_strComplete(_T(""))
{
	// TODO:  在此处添加构造代码
	isPause = false;
}

CSortShowView::~CSortShowView()
{
	delete[]data;
}

int indexA = 0, indexB = 0;
CBrush cb_ChangeRect = CBrush(RGB(255, 0, 0));
CBrush cb_FlishRect = CBrush(RGB(0, 255, 0));
CBrush cb_VisitRect = CBrush(RGB(0, 0, 255));
CPen   cp_Round = CPen(PS_SOLID, 1, RGB(0, 0, 255));
CPen   cp_ChangeRect = CPen(PS_SOLID, 1, RGB(255, 0, 0));
CPen   cp_FlishRoud = CPen(PS_SOLID, 1, RGB(0, 255, 0));

void CSortShowView::OnDraw(CDC * pDC)
{
	CDC MemDC;
	CBitmap MemBitmap;
	MemDC.CreateCompatibleDC(NULL);
	MemBitmap.CreateCompatibleBitmap(pDC,maxWidth,maxHeight);
	CBitmap * pOldBitmap = MemDC.SelectObject(&MemBitmap);
	
	MemDC.FillSolidRect(0,0,maxWidth,maxHeight, RGB(255, 255, 255));
	
	for (int i = 0; i < m_Size; i++)
	{
		CBrush *pOldBrush = MemDC.SelectObject(&cb_VisitRect);
		CPen   *pOldPen = MemDC.SelectObject(&cp_Round);
		CPoint p1, p2;
		p1.x = startPoint.x + perWidth*i;
		p1.y = startPoint.y - data[i];
		p2.x = p1.x + perWidth;
		p2.y = startPoint.y;

		MemDC.Rectangle(CRect(p1, p2));
		if (perWidth < 1)
		{
			MemDC.MoveTo(p1);
			MemDC.LineTo(p2);
		}

		MemDC.SelectObject(pOldBrush);
		MemDC.SelectObject(pOldPen);

	}
	for (int i = 0; i<m_Speed; i++)
	{
		if (cashData.GetCount() > 0 && !isPause)
		{
			isFlished = false;
			flishIndex = 0;
			int valueB=-1,indexA=-1;
			indexA = cashData.GetHead();
			cashData.RemoveHead();
			int valueA = cashData.GetHead();
			cashData.RemoveHead();

			if (cashData.GetCount()> 0)
			{
				indexB = cashData.GetHead();
				cashData.RemoveHead();
				valueB = cashData.GetHead();
				cashData.RemoveHead();
			}

			CPoint p1, p2, p3, p4;
			p1.x = startPoint.x + perWidth* (indexA);
			p1.y = startPoint.y - data[indexA];
			p2.x = p1.x + perWidth;
			p2.y = startPoint.y;

			if (indexB >= 0)
			{
				p3.x = startPoint.x + perWidth* (indexB);
				p3.y = startPoint.y - data[indexB];
				p4.x = p3.x + perWidth;
				p4.y = startPoint.y;
			}
			CBrush *pOldBrush = MemDC.SelectObject(&cb_ChangeRect);
			CPen   *pOldPen = MemDC.SelectObject(&cp_ChangeRect);

			MemDC.Rectangle(CRect(p1, p2));
			if (perWidth < 1)
			{
				MemDC.MoveTo(p1);
				MemDC.LineTo(p2);
			}
			

			if (indexB >= 0)
			{
				MemDC.Rectangle(CRect(p3, p4));
				if (perWidth < 1)
				{
					MemDC.MoveTo(p3);
					MemDC.LineTo(p4);
				}
			}
			MemDC.SelectObject(pOldBrush);
			MemDC.SelectObject(pOldPen);

			data[indexA] = valueA;

			if (indexB >= 0)
			{
				data[indexB] = valueB;
			}

			if (cashData.GetCount() == 0)
			{
				isFlished = true;
			}
		}
	}
	if (isFlished )
	{
		CPoint p1, p2;
		CBrush *pOldBrush = MemDC.SelectObject(&cb_FlishRect);
		CPen *pOldPen = MemDC.SelectObject(&cp_FlishRoud);

		for (int j = 0; j < flishIndex; j++)
		{
			p1.x = startPoint.x + perWidth*j;
			p1.y = startPoint.y - data[j];
			p2.x = p1.x + perWidth;
			p2.y = startPoint.y;
			MemDC.Rectangle(CRect(p1, p2));
			if (perWidth < 1)
			{
				MemDC.MoveTo(p1);
				MemDC.LineTo(p2);
			}
		}

		MemDC.SelectObject(pOldPen);
		MemDC.SelectObject(pOldBrush);

		flishIndex+=m_Speed;

		if (flishIndex >= m_Size)
		{
			flishIndex = m_Size - 1;
		}
	}

	pDC->SetStretchBltMode(COLORONCOLOR);
	pDC->BitBlt(0,0,maxWidth,maxHeight,&MemDC,0,0,SRCCOPY);
	MemBitmap.DeleteObject();
	MemDC.DeleteDC();

	

}

void CSortShowView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SortType, m_cbSortType);
	DDX_Control(pDX, IDC_SLIDER_Speed, m_sliderSpeed);
	DDX_Slider(pDX, IDC_SLIDER_Speed, m_Speed);
	DDX_Text(pDX, IDC_STATIC_Speed, m_strSpeed);
	DDX_Text(pDX, IDC_EDIT1, m_Size);
	DDX_Text(pDX, IDC_STATIC_Time, m_strCostTime);
	DDX_Text(pDX, IDC_STATIC_Time2, m_strComplete);
}

BOOL CSortShowView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	return CFormView::PreCreateWindow(cs);
}

void CSortShowView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit(FALSE);

	sortType[0] = "冒泡排序法";
	sortType[1] = "快速排序法";
	sortType[2] = "插入排序法";
	sortType[3] = "选择排序法";
	sortType[4] = "希尔排序法";
	sortType[5] = "堆排序法";
	sortType[6] = "归并排序法";
	sortType[7] = "基数排序法";
	sortType[8] = "STL_sort";
	sortType[9] = "Stable_sort";
	sortType[10] = "鸡尾酒";
	for (int i = 0; i < 11; i++)
	{
		m_cbSortType.AddString(sortType[i]);
	}
	m_sliderSpeed.SetRangeMax(30);
	m_sliderSpeed.SetRangeMin(1);


	CRect rect;
	GetDlgItem(IDC_STATIC_Group)->GetWindowRect(&rect);//获取控件相对于屏幕的位置
	ScreenToClient(rect);
	startPoint.x = rect.left;
	startPoint.y = rect.bottom;
	maxHeight = rect.bottom - rect.top;
	maxWidth = rect.right - rect.left;
	startRect = rect;
	spwanData();
}

void CSortShowView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
}

void CSortShowView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

// CSortShowView 诊断

#ifdef _DEBUG
void CSortShowView::AssertValid() const
{
	CFormView::AssertValid();
}

void CSortShowView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CSortShowDoc* CSortShowView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSortShowDoc)));
	return (CSortShowDoc*)m_pDocument;
}
#endif //_DEBUG


// CSortShowView 消息处理程序

void CSortShowView::OnTimer(UINT_PTR nIDEvent)
{
	InvalidateRect(startRect, false);
	CClientDC dc(this);
	CString strTime, strPer;
	strTime.Format(_T("耗时：%ld ms"), costTime);
	strPer.Format(_T("完成：%.2lf"), (double)(100*(maxCashLength-cashData.GetCount()))
		/(double)maxCashLength);
	strPer += " %";

	dc.DrawTextW(strTime, CRect(0, 0, 400, 400), 1);
	dc.DrawTextW(strPer, CRect(0, 0, 700, 700), 1);

}
int  CSortShowView::checInputData()
{
	int oldSize = m_Size;
	UpdateData(TRUE);

	if (m_Size < 0)
	{
		MessageBox(L"请输入一个正数", L"错误");
		m_Size = oldSize;
		UpdateData(FALSE);
		return -1;
	}
	else if (m_Size>maxSize)
	{
		CString error;
		error.Format(_T("数据过大!不要超过%d"), maxSize);
		MessageBox(error, L"错误");
		m_Size = oldSize;
		UpdateData(FALSE);
		return -1;
	}
	return 1;
}
void CSortShowView::OnBnClickedButtonBeginsort()
{
	// 检查数据
	if (checInputData() < 0){ return; }

	if (data == NULL)
	{
		spwanData();
	}

	if (isPause)
	{
		isPause = false;
	}
	else
	{
		ChoseSortType();
	}
	SetTimer(1, 33, NULL);
}
void CSortShowView::OnBnClickedButtonPause()
{
	// TODO:  在此添加控件通知处理程序代码
	isPause = true;
}
void CSortShowView::OnBnClickedButtonRestart()
{
	// TODO:  在此添加控件通知处理程序代码
	Invalidate();
	spwanData();
	isPause = false;
	cashData.RemoveAll();
	SetTimer(1,0,NULL);
}
void CSortShowView::OnCbnSelchangeComboSorttype()
{
	// TODO:  在此添加控件通知处理程序代码
	int curIndex = m_cbSortType.GetCurSel();
	m_cbSortType.GetLBText(curIndex,curSel);
}

void CSortShowView::OnNMCustomdrawSliderSpeed(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CString str;
	str.Format(_T("%d"),m_Speed);
	m_strSpeed = str;
	UpdateData(FALSE);

	*pResult = 0;
}

void CSortShowView::spwanData()
{
	UpdateData(TRUE);
	data = new int[m_Size];
	isFlished = false;
	flishIndex = 0;
	costTime = 0;
	maxCashLength = 1;

	perWidth = (double)maxWidth / (double) m_Size;
	//perWidth = perWidth >1? perWidth : 1;

	double perHeight = (double)maxHeight / (double)m_Size;

	for (int i = 0; i < m_Size; i++)
	{
		data[i]= perHeight * (i+1);
	}
	for (int i = 0; i < m_Size; i++)
	{
		for (int j = i; j < m_Size; j++)
		{
			int temp;
			int index;
			index = rand() % m_Size;
			temp = data[index];
			data[index]= data[i];
			data[i] = temp;
		}
	}
	CClientDC dc(this);
	// 清屏
	CBrush backGroud(RGB(255, 255, 255));
	dc.FillRect(startRect, &backGroud);
}
void CSortShowView::ChoseSortType()
{
	UpdateData(TRUE);
	if (curSel == sortType[0])
	{
		costTime=sort.Bubble(data,m_Size,&cashData);
	}
	else if (curSel == sortType[1])
	{
		costTime = sort.Quick(data, m_Size, &cashData);
	}
	else if (curSel == sortType[2])
	{
		costTime = sort.Insert(data, m_Size, &cashData);
	}
	else if (curSel == sortType[3])
	{
		costTime = sort.Select(data, m_Size, &cashData);

	}
	else if (curSel == sortType[4])
	{
		costTime = sort.Shell(data, m_Size, &cashData);
	}
	else if (curSel == sortType[5])
	{
		costTime = sort.Heap(data, m_Size, &cashData);
	}
	else if (curSel == sortType[6])
	{
		costTime = sort.Merge(data, m_Size, &cashData);
	}
	else if (curSel == sortType[7])
	{
		costTime = sort.Radix(data, m_Size, &cashData);
	}
	else if (curSel == sortType[8])
	{
		costTime = sort.STL_Sort(data, m_Size, &cashData);
	}
	else if (curSel == sortType[9])
	{
		costTime = sort.STL_StableSort(data, m_Size, &cashData);
	}
	else  if (curSel == sortType[10])
	{
		costTime = sort.Cocktail(data, m_Size, &cashData);
	}
	maxCashLength = cashData.GetCount();
}
