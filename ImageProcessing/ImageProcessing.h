
// ImageProcessing.h : PROJECT_NAME ���ε{�����D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�


// CImageProcessingApp: 
// �аѾ\��@�����O�� ImageProcessing.cpp
//

class CImageProcessingApp : public CWinApp
{
public:
	CImageProcessingApp();

// �мg
public:
	virtual BOOL InitInstance();

// �{���X��@

	DECLARE_MESSAGE_MAP()
};

extern CImageProcessingApp theApp;