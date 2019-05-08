#pragma once
#include<Windows.h>
#include<vector>
#include"DlgBoxTemplate.h"
#include"../resource.h"
#include"EditBox.h"
#include"ComboBox.h"
#include"Label.h"

class MainDlg : public DlgBoxTemplate
{
private:
	EditBox* m_in;
	EditBox* m_out;




public:
	MainDlg(HINSTANCE hInstance, LPCSTR dlgResName, HWND parent);
	~MainDlg();

	LRESULT	 RealDlgProc(HWND   hwnd, UINT   uMsg, WPARAM wParam, LPARAM lParam);
	void OnCreate();
};

