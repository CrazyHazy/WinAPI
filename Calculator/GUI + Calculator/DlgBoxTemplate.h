#pragma once
#include<Windows.h>

class DlgBoxTemplate
{
public:
	DlgBoxTemplate(HINSTANCE hInstance, LPCSTR dlgResName, HWND parent);
	virtual ~DlgBoxTemplate();
	void Show(int nCmdShow);

private:
	static LRESULT CALLBACK StDlgProc( HWND   hwnd , UINT   uMsg, WPARAM wParam, LPARAM lParam);
	virtual void OnCreate() = 0;
	void CreateDlg(HINSTANCE hInstance, LPCSTR dlgResName, HWND parent);

protected:
	HWND m_hWnd;
	HBRUSH m_background = 0;
	virtual LRESULT	 RealDlgProc(HWND   hwnd, UINT   uMsg, WPARAM wParam, LPARAM lParam);
	
	 
};

