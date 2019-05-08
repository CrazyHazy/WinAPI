#include "MainDlg.h"
#include"../resource.h"
#include"RPN.h"



MainDlg::MainDlg(HINSTANCE hInstance, LPCSTR dlgResName, HWND parent) : DlgBoxTemplate(hInstance, dlgResName, parent)
{
	OnCreate();
}


MainDlg::~MainDlg()
{

}

LRESULT MainDlg::RealDlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{

		case WM_ERASEBKGND:
			return 1; break;

		case WM_COMMAND: 
		{
			switch (wParam)
			{
			case B_0: m_in->AppendText("0"); break;
			case B_1: m_in->AppendText("1"); break;
			case B_2: m_in->AppendText("2"); break;
			case B_3: m_in->AppendText("3"); break;
			case B_4: m_in->AppendText("4"); break;
			case B_5: m_in->AppendText("5"); break;
			case B_6: m_in->AppendText("6"); break;
			case B_7: m_in->AppendText("7"); break;
			case B_8: m_in->AppendText("8"); break;
			case B_9: m_in->AppendText("9"); break;
			case B_PLUS: m_in->AppendText(" + "); break;
			case B_MULT: m_in->AppendText(" x "); break;
			case B_MINUS: m_in->AppendText(" - "); break;
			case B_OP: m_in->AppendText(" ) "); break;
			case B_CL: m_in->AppendText(" ( "); break;
			case B_ANS:
				std::string a = std::to_string(CountRPN(GetRPN(m_in->GetText())));
				m_out->SetText(&a[0u]); break;
			}
		}	
	}
	return DlgBoxTemplate::RealDlgProc(hwnd, uMsg, wParam, lParam);
}

void MainDlg::OnCreate()
{
	m_in = new EditBox(m_hWnd, IN);
	m_out = new EditBox(m_hWnd, OUT);
		
}
