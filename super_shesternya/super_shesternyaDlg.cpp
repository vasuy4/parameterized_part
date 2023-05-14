
// super_shesternyaDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "super_shesternya.h"
#include "super_shesternyaDlg.h"
#include "afxdialogex.h"
#include "resource.h"

//#include "stdafx.h"
#include "math.h"
#include "G:\Aprograms\Kompas\SDK\Include\ksConstants.h"
#include "G:\Aprograms\Kompas\SDK\Include\ksConstants3D.h"

#include <atlsafe.h>
#include <comutil.h>

#define PI 4*atan(1)

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma once

#import "G:\Aprograms\Kompas\SDK\lib\kAPI5.tlb"

using namespace Kompas6API5;
KompasObjectPtr pKompasApp5;
ksPartPtr pPart;
ksDocument3DPtr pDoc;

// Диалоговое окно CAboutDlg используется для описания сведений о приложении

CsupershesternyaDlg::CsupershesternyaDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SUPER_SHESTERNYA_DIALOG, pParent)
	, m_extrusion(50)
	, m_diameter(32)
	, m_diameter_S((50 + 16) * 2)
	, m_diameter_L((100 + 16) * 2)
	, m_cutout(18)
	, m_thickness(10)
	, m_rib_thickness(10)
	, m_edge_height(12)
	, m_count_edge(5)
	, m_depth_hole(m_cutout)
	, m_width_hole(6)
	, m_length_hole(10)
	, m_count_of_holes(m_count_edge)
	, m_internal_teeth(30)
	, m_external_teeth(40)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CsupershesternyaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT1, m_extrusion); //толщина детали
	DDV_MinMaxDouble(pDX, m_extrusion, 0, 100);
	DDX_Text(pDX, IDC_EDIT2, m_diameter); //D центрального отверстия
	DDV_MinMaxDouble(pDX, m_diameter, 0, 300);
	DDX_Text(pDX, IDC_EDIT3, m_diameter_S); //диаметр внутренней окружности
	DDV_MinMaxDouble(pDX, m_diameter_S, m_diameter, m_diameter + 200);
	DDX_Text(pDX, IDC_EDIT4, m_diameter_L); //диаметр внешней окружности
	DDV_MinMaxDouble(pDX, m_diameter_L, m_diameter_S, m_diameter_S + 200);
	DDX_Text(pDX, IDC_EDIT5, m_cutout); //глубина выреза
	DDV_MinMaxDouble(pDX, m_cutout, 0, m_extrusion / 2);
	DDX_Text(pDX, IDC_EDIT6, m_thickness); //толщина окружностей
	DDV_MinMaxDouble(pDX, m_thickness, 0, 50);
	DDX_Text(pDX, IDC_EDIT7, m_rib_thickness); //толщина рёбра
	DDV_MinMaxDouble(pDX, m_rib_thickness, 0, 50);
	DDX_Text(pDX, IDC_EDIT9, m_edge_height); //высота ребра
	DDV_MinMaxDouble(pDX, m_edge_height, 0, m_cutout);
	DDX_Text(pDX, IDC_EDIT8, m_count_edge); //количество рёбер
	DDV_MinMaxDouble(pDX, m_count_edge, 0, 20);
	DDX_Text(pDX, IDC_EDIT12, m_depth_hole); //глубина впадины
	DDV_MinMaxDouble(pDX, m_depth_hole, 0, m_cutout);
	DDX_Text(pDX, IDC_EDIT10, m_width_hole); //ширина впадины
	DDV_MinMaxDouble(pDX, m_width_hole, 0, m_thickness - 1);
	DDX_Text(pDX, IDC_EDIT11, m_length_hole); //длина впадины
	DDV_MinMaxDouble(pDX, m_length_hole, 0, 30);
	DDX_Text(pDX, IDC_EDIT13, m_count_of_holes); //количество впадин
	DDV_MinMaxDouble(pDX, m_count_of_holes, 0, 20);
	DDX_Text(pDX, IDC_EDIT15, m_internal_teeth); //количество внутренних зубьев
	DDV_MinMaxDouble(pDX, m_internal_teeth, 0, 70);
	DDX_Text(pDX, IDC_EDIT16, m_external_teeth); //количество внешних зубьев
	DDV_MinMaxDouble(pDX, m_external_teeth, 0, 120);
}

BEGIN_MESSAGE_MAP(CsupershesternyaDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CsupershesternyaDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


BOOL CsupershesternyaDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}


void CsupershesternyaDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CsupershesternyaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

bool CsupershesternyaDlg::CheckData()
{
	if (!UpdateData())
		return false;

	return true;
}





void CsupershesternyaDlg::OnBnClickedButton1()
{
	// TODO: добавьте свой код обработчика уведомлений
	BeginWaitCursor();

	if (!CheckData())
		return;

	CComPtr<IUnknown> pKompasAppUnk = nullptr;
	if (!pKompasApp5)
	{
		// Получаем CLSID для Компас
		CLSID InvAppClsid;
		HRESULT hRes = CLSIDFromProgID(L"Kompas.Application.5", &InvAppClsid);
		if (FAILED(hRes)) {
			pKompasApp5 = nullptr;
			return;
		}

		// Проверяем есть ли запущенный экземпляр Компас
		//если есть получаем IUnknown
		hRes = ::GetActiveObject(InvAppClsid, NULL, &pKompasAppUnk);
		if (FAILED(hRes)) {
			// Приходится запускать Компас самим так как работающего нет
			// Также получаем IUnknown для только что запущенного приложения Компас
			TRACE(L"Could not get hold of an active Inventor, will start a new session\n");
			hRes = CoCreateInstance(InvAppClsid, NULL, CLSCTX_LOCAL_SERVER, __uuidof(IUnknown), (void**)&pKompasAppUnk);
			if (FAILED(hRes)) {
				pKompasApp5 = nullptr;
				return;
			}
		}

		// Получаем интерфейс приложения Компас
		hRes = pKompasAppUnk->QueryInterface(__uuidof(KompasObject), (void**)&pKompasApp5);
		if (FAILED(hRes)) {
			return;
		}
	}

	pKompasApp5->Visible = true;

	pDoc = pKompasApp5->Document3D();

	pDoc->Create(false, true);

	pPart = pDoc->GetPart(pTop_Part);

	//create main sketch

	ksEntityPtr pSketch = pPart->NewEntity(o3d_sketch);

	ksSketchDefinitionPtr pSketchDef = pSketch->GetDefinition();

	pSketchDef->SetPlane(pPart->GetDefaultEntity(o3d_planeXOY));

	pSketch->Create();

	ksDocument2DPtr p2DDoc = pSketchDef->BeginEdit();

	double point[17][2];
	point[0][0] = 0;
	point[0][1] = m_diameter / 2.f; //16;
	point[1][0] = m_extrusion / 2.f - m_cutout; //7
	point[1][1] = m_diameter / 2.f; //16

	point[2][0] = m_extrusion / 2.f - m_cutout; //7
	point[2][1] = m_diameter_S / 2.f - m_thickness; //56

	point[3][0] = m_extrusion / 2.f; //25
	point[3][1] = m_diameter_S / 2.f - m_thickness; //56

	point[4][0] = m_extrusion / 2.f; //25
	point[4][1] = m_diameter_S / 2.f; //66

	point[5][0] = m_extrusion / 2.f - m_cutout; //7
	point[5][1] = m_diameter_S / 2.f; //66

	point[6][0] = m_extrusion / 2.f - m_cutout; //7
	point[6][1] = m_diameter_L / 2.f - m_thickness; //106

	point[7][0] = m_extrusion / 2.f; //25
	point[7][1] = m_diameter_L / 2.f - m_thickness; //106

	point[8][0] = m_extrusion / 2.f; //25
	point[8][1] = m_diameter_L / 2.f; //116

	//********

	point[9][0] = -(m_extrusion / 2.f); //-25
	point[9][1] = m_diameter_L / 2.f; //116

	point[10][0] = -(m_extrusion / 2.f); //-25
	point[10][1] = m_diameter_L / 2.f - m_thickness; //106

	point[11][0] = -(m_extrusion / 2.f - m_cutout); //-7
	point[11][1] = point[6][1] = m_diameter_L / 2.f - m_thickness; //106

	point[12][0] = -(m_extrusion / 2.f - m_cutout); //-7
	point[12][1] = m_diameter_S / 2.f; //66

	point[13][0] = -(m_extrusion / 2.f); //-25
	point[13][1] = m_diameter_S / 2.f; //66

	point[14][0] = -(m_extrusion / 2.f); //-25
	point[14][1] = m_diameter_S / 2.f - m_thickness; //56

	point[15][0] = -(m_extrusion / 2.f - m_cutout); //-7
	point[15][1] = m_diameter_S / 2.f - m_thickness; //56

	point[16][0] = -(m_extrusion / 2.f - m_cutout); //-7
	point[16][1] = m_diameter / 2.f; //16

	
	p2DDoc->ksLineSeg(point[0][0], point[0][1], point[1][0], point[1][1], 1);
	p2DDoc->ksLineSeg(point[1][0], point[1][1], point[2][0], point[2][1], 1);
	p2DDoc->ksLineSeg(point[2][0], point[2][1], point[3][0], point[3][1], 1);
	p2DDoc->ksLineSeg(point[3][0], point[3][1], point[4][0], point[4][1], 1);
	p2DDoc->ksLineSeg(point[4][0], point[4][1], point[5][0], point[5][1], 1);
	p2DDoc->ksLineSeg(point[5][0], point[5][1], point[6][0], point[6][1], 1);
	p2DDoc->ksLineSeg(point[6][0], point[6][1], point[7][0], point[7][1], 1);
	p2DDoc->ksLineSeg(point[7][0], point[7][1], point[8][0], point[8][1], 1);
	p2DDoc->ksLineSeg(point[8][0], point[8][1], point[9][0], point[9][1], 1);
	p2DDoc->ksLineSeg(point[9][0], point[9][1], point[10][0], point[10][1], 1);

	p2DDoc->ksLineSeg(point[10][0], point[10][1], point[11][0], point[11][1], 1);
	p2DDoc->ksLineSeg(point[11][0], point[11][1], point[12][0], point[12][1], 1);
	p2DDoc->ksLineSeg(point[12][0], point[12][1], point[13][0], point[13][1], 1);
	p2DDoc->ksLineSeg(point[13][0], point[13][1], point[14][0], point[14][1], 1);
	p2DDoc->ksLineSeg(point[14][0], point[14][1], point[15][0], point[15][1], 1);
	p2DDoc->ksLineSeg(point[15][0], point[15][1], point[16][0], point[16][1], 1);
	p2DDoc->ksLineSeg(point[16][0], point[16][1], point[0][0], point[0][1], 1);

	p2DDoc->ksLineSeg(-10, 0, 10, 0, 3);

	pSketchDef->EndEdit();

	//create main extrusion

	ksEntityPtr pRotate = pPart->NewEntity(o3d_bossRotated);

	ksBossRotatedDefinitionPtr pRotDef = pRotate->GetDefinition();
	pRotDef->SetSketch(pSketch);
	pRotDef->SetSideParam(TRUE, 360);

	pRotate->Create();


	/*
	ksEntityPtr pPlane = pPart->NewEntity(o3d_planeOffset);
	ksPlaneOffsetDefinitionPtr pPlaneDef = pPlane->GetDefinition();

	pPlaneDef->direction = true;
	pPlaneDef->offset = m_extrusion / 2.f - m_cutout ;
	pPlaneDef->SetPlane(pPart->GetDefaultEntity(o3d_planeYOZ));

	pPlane->Create();
	*/

	//создание ребра

	ksEntityPtr pSketch1 = pPart->NewEntity(o3d_sketch);

	pSketchDef = pSketch1->GetDefinition();

	pSketchDef->SetPlane(pPart->GetDefaultEntity(o3d_planeYOZ));

	pSketch1->Create();

	p2DDoc = pSketchDef->BeginEdit();


	double point1[4][2];
	
	point1[0][0] = -(m_rib_thickness / 2.f); //-5
	point1[0][1] = m_diameter_S / 2.f - m_thickness / 2.f; //61

	point1[1][0] = m_rib_thickness / 2.f; //5
	point1[1][1] = m_diameter_S / 2.f - m_thickness / 2.f; //61

	point1[2][0] = m_rib_thickness / 2.f; //5
	point1[2][1] = m_diameter_L / 2.f - m_thickness / 2.f; //111

	point1[3][0] = -(m_rib_thickness / 2.f); //-5
	point1[3][1] = m_diameter_L / 2.f - m_thickness / 2.f; //-111
	
	
	p2DDoc->ksLineSeg(point1[0][0], point1[0][1], point1[1][0], point1[1][1], 1);
	p2DDoc->ksLineSeg(point1[1][0], point1[1][1], point1[2][0], point1[2][1], 1);
	p2DDoc->ksLineSeg(point1[2][0], point1[2][1], point1[3][0], point1[3][1], 1);
	p2DDoc->ksLineSeg(point1[3][0], point1[3][1], point1[0][0], point1[0][1], 1);
	p2DDoc->ksLineSeg(-10, 0, 10, 0, 3);

	pSketchDef->EndEdit();

	//выдавливание ребра в обе стороны

	ksEntityPtr pExtrude1 = pPart->NewEntity(o3d_baseExtrusion);

	ksBaseExtrusionDefinitionPtr pEx1 = pExtrude1->GetDefinition();
	pEx1->directionType = dtMiddlePlane;

	pEx1->SetSketch(pSketch1);
	pEx1->SetSideParam(true, etBlind, (m_edge_height + m_extrusion / 2.f - m_cutout) * 2, 0, false);

	pExtrude1->Create();

	//массив ребра

	ksEntityPtr pCircCopy1 = pPart->NewEntity(o3d_circularCopy);

	ksCircularCopyDefinitionPtr pCircEx = pCircCopy1->GetDefinition();
	pCircEx->Putcount2(m_count_edge); //5

	pCircEx->SetAxis(pPart->GetDefaultEntity(o3d_axisOX));

	ksEntityCollectionPtr fl = pCircEx->GetOperationArray();
	fl->Clear();

	fl->Add(pExtrude1);

	pCircCopy1->Create();


	//создание смещённой плоскости

	ksEntityPtr pPlane = pPart->NewEntity(o3d_planeOffset);
	ksPlaneOffsetDefinitionPtr pPlaneDef = pPlane->GetDefinition();

	pPlaneDef->direction = true;
	pPlaneDef->offset = m_extrusion / 2.f;
	pPlaneDef->SetPlane(pPart->GetDefaultEntity(o3d_planeYOZ));

	pPlane->Create();

	//создание эскиза впадины
	ksEntityPtr pSketchHole = pPart->NewEntity(o3d_sketch);
	pSketchDef = pSketchHole->GetDefinition();
	pSketchDef->SetPlane(pPlane);
	pSketchHole->Create();
	p2DDoc = pSketchDef->BeginEdit();

	double point2[10][2];
	point2[0][0] = m_length_hole / 2.f; //5
	point2[0][1] = -m_diameter_S / 2.f; //-66

	point2[1][0] = m_length_hole / 2.f; //5
	point2[1][1] = -m_diameter_S / 2.f + m_width_hole; //-60

	point2[2][0] = -m_length_hole / 2.f; //-5
	point2[2][1] = -m_diameter_S / 2.f + m_width_hole; //-60

	point2[3][0] = -m_length_hole / 2.f; //-5
	point2[3][1] = -m_diameter_S / 2.f; //-66
	
	p2DDoc->ksLineSeg(point2[0][0], point2[0][1], point2[1][0], point2[1][1], 1);
	p2DDoc->ksLineSeg(point2[1][0], point2[1][1], point2[2][0], point2[2][1], 1);
	p2DDoc->ksLineSeg(point2[2][0], point2[2][1], point2[3][0], point2[3][1], 1);
	p2DDoc->ksLineSeg(point2[3][0], point2[3][1], point2[0][0], point2[0][1], 1);

	

	pSketchDef->EndEdit();


	//вырезать выдавливанием

	ksEntityPtr pExtrude2 = pPart->NewEntity(o3d_cutExtrusion);

	ksCutExtrusionDefinitionPtr pExDef = pExtrude2->GetDefinition();
	pExDef->directionType = dtNormal;

	pExDef->SetSketch(pSketchHole);
	pExDef->SetSideParam(true, etBlind, m_depth_hole, 0, false);


	pExtrude2->Create();

	//массив впадин
	ksEntityPtr pHoleCopy1 = pPart->NewEntity(o3d_circularCopy);

	ksCircularCopyDefinitionPtr pHoleEx = pHoleCopy1->GetDefinition();
	pHoleEx->Putcount2(m_count_of_holes); //5

	pHoleEx->SetAxis(pPart->GetDefaultEntity(o3d_axisOX));

	fl = pHoleEx->GetOperationArray();
	fl->Clear();

	fl->Add(pExtrude2);

	pHoleCopy1->Create();


	//создание эскиза зуба внешней окружности

	ksEntityPtr pSketchTooth = pPart->NewEntity(o3d_sketch);
	pSketchDef = pSketchTooth->GetDefinition();
	pSketchDef->SetPlane(pPart->GetDefaultEntity(o3d_planeYOZ));

	pSketchTooth->Create();
	p2DDoc = pSketchDef->BeginEdit();

	double point3[4][2];
	point3[0][0] = m_diameter_L / 2.f - m_thickness / 8.f;
	point3[0][1] = 3.f;

	point3[1][0] = m_diameter_L / 2.f - m_thickness / 8.f;
	point3[1][1] = -3.f;

	point3[2][0] = m_diameter_L / 2.f - m_thickness / 8.f + 9.f;
	point3[2][1] = -1.5f;

	point3[3][0] = m_diameter_L / 2.f - m_thickness / 8.f + 9.f;
	point3[3][1] = 1.5f;

	p2DDoc->ksLineSeg(point3[0][0], point3[0][1], point3[1][0], point3[1][1], 1);
	p2DDoc->ksLineSeg(point3[1][0], point3[1][1], point3[2][0], point3[2][1], 1);
	p2DDoc->ksLineSeg(point3[2][0], point3[2][1], point3[3][0], point3[3][1], 1);
	p2DDoc->ksLineSeg(point3[3][0], point3[3][1], point3[0][0], point3[0][1], 1);

	pSketchDef->EndEdit();

	//выдавливание зуба в обе стороны

	ksEntityPtr pExtrudeTooth = pPart->NewEntity(o3d_baseExtrusion);

	ksBaseExtrusionDefinitionPtr pExTooth = pExtrudeTooth->GetDefinition();
	pExTooth->directionType = dtMiddlePlane;

	pExTooth->SetSketch(pSketchTooth);
	pExTooth->SetSideParam(true, etBlind, m_extrusion, 0, false);

	pExtrudeTooth->Create();

	//создание эскиза зуба внутренней окружности

	ksEntityPtr pSketchTooth2 = pPart->NewEntity(o3d_sketch);
	pSketchDef = pSketchTooth2->GetDefinition();
	pSketchDef->SetPlane(pPlane);
	pSketchTooth2->Create();
	p2DDoc = pSketchDef->BeginEdit();

	double point4[4][2];
	point4[0][0] = m_diameter_S / 2.f - m_thickness / 1.02f;
	point4[0][1] = 3.f;

	point4[1][0] = m_diameter_S / 2.f - m_thickness / 1.02f;
	point4[1][1] = -3.f;

	point4[2][0] = m_diameter_S / 2.f - m_thickness / 1.02f - 9.f;
	point4[2][1] = -1.5f;

	point4[3][0] = m_diameter_S / 2.f - m_thickness / 1.02f - 9.f;
	point4[3][1] = 1.5f;

	p2DDoc->ksLineSeg(point4[0][0], point4[0][1], point4[1][0], point4[1][1], 1);
	p2DDoc->ksLineSeg(point4[1][0], point4[1][1], point4[2][0], point4[2][1], 1);
	p2DDoc->ksLineSeg(point4[2][0], point4[2][1], point4[3][0], point4[3][1], 1);
	p2DDoc->ksLineSeg(point4[3][0], point4[3][1], point4[0][0], point4[0][1], 1);

	pSketchDef->EndEdit();

	//выдавливание зуба

	ksEntityPtr pExtrudeTooth2 = pPart->NewEntity(o3d_baseExtrusion);

	ksBaseExtrusionDefinitionPtr pExTooth2 = pExtrudeTooth2->GetDefinition();
	pExTooth2->directionType = dtReverse;

	pExTooth2->SetSketch(pSketchTooth2);
	pExTooth2->SetSideParam(false, etUpToNearSurface, 0, 0, false);

	pExtrudeTooth2->Create();

	//массив зубьев внешних

	ksEntityPtr pTeethCopy1 = pPart->NewEntity(o3d_circularCopy);

	ksCircularCopyDefinitionPtr pTeethEx = pTeethCopy1->GetDefinition();
	pTeethEx->Putcount2(m_external_teeth); //40

	pTeethEx->SetAxis(pPart->GetDefaultEntity(o3d_axisOX));

	fl = pTeethEx->GetOperationArray();
	fl->Clear();

	fl->Add(pExtrudeTooth);

	pTeethCopy1->Create();


	//массив зубьев внутренних
	ksEntityPtr pTeethCopy2 = pPart->NewEntity(o3d_circularCopy);

	ksCircularCopyDefinitionPtr pTeeth2Ex = pTeethCopy2->GetDefinition();
	pTeeth2Ex->Putcount2(m_internal_teeth); //40

	pTeeth2Ex->SetAxis(pPart->GetDefaultEntity(o3d_axisOX));

	fl = pTeeth2Ex->GetOperationArray();
	fl->Clear();

	fl->Add(pExtrudeTooth2);

	pTeethCopy2->Create();

	pDoc->SaveAs("C:\\KompasAssembly\\Boss.m3d");
}







class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
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


void CsupershesternyaDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

