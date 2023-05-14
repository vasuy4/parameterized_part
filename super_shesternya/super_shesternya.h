
// super_shesternya.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CsupershesternyaApp:
// Сведения о реализации этого класса: super_shesternya.cpp
//

class CsupershesternyaApp : public CWinApp
{
public:
	CsupershesternyaApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CsupershesternyaApp theApp;
