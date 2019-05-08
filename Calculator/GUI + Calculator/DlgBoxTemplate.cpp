#include "DlgBoxTemplate.h"



DlgBoxTemplate::DlgBoxTemplate(HINSTANCE hInstance, LPCSTR dlgResName, HWND parent)
{
	CreateDlg(hInstance, dlgResName, parent);
}


DlgBoxTemplate::~DlgBoxTemplate()
{
}

void DlgBoxTemplate::Show(int nCmdShow)
{
	ShowWindow(m_hWnd, nCmdShow);
}

LRESULT DlgBoxTemplate::RealDlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG : 
		break;
	
	case WM_CTLCOLORDLG:
		if (!m_background) break;
		return (LPARAM)m_background;
		break;
	case WM_CLOSE :
		EndDialog(hwnd, wParam);
		PostQuitMessage(0);
	}
	return 0;
}

void DlgBoxTemplate::CreateDlg(HINSTANCE hInstance, LPCSTR dlgResName, HWND parent)
{
	m_hWnd = CreateDialogParamA(hInstance, dlgResName, parent, (DLGPROC)StDlgProc, WM_INITDIALOG);
	SetWindowLongA(m_hWnd, GWLP_USERDATA, (LONG_PTR)this);
}

LRESULT DlgBoxTemplate::StDlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	DlgBoxTemplate* pDlg = nullptr;
	pDlg = (DlgBoxTemplate*)GetWindowLongA(hwnd, GWLP_USERDATA);
	return pDlg ? pDlg->RealDlgProc(hwnd, uMsg, wParam, lParam) : 0;
}
