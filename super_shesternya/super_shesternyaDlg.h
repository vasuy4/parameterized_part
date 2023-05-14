
// super_shesternyaDlg.h: файл заголовка
//

#pragma once


// Диалоговое окно CsupershesternyaDlg
class CsupershesternyaDlg : public CDialogEx
{
// Создание
public:
	CsupershesternyaDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SUPER_SHESTERNYA_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// extrusion height
	double m_extrusion;
	double m_diameter;

	afx_msg void OnBnClickedButton1();
	bool CheckData();

	double m_diameter_S;
	double m_diameter_L;
	double m_cutout;
	double m_thickness;
	double m_rib_thickness;
	double m_edge_height;
	int m_count_edge;
	double m_depth_hole;
	double m_width_hole;
	double m_length_hole;
	int m_count_of_holes;
	int m_internal_teeth;
	int m_external_teeth;
};
