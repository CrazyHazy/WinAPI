#include<Windows.h>
#include<CommCtrl.h>
#include<gdiplus.h>
#include"MainDlg.h"

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "Comctl32.lib")
#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;


int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	
	INITCOMMONCONTROLSEX init = { sizeof(INITCOMMONCONTROLSEX), ICC_WIN95_CLASSES };

	if (!InitCommonControlsEx(&init))
	{
		MessageBox(nullptr, "init err", "fatal", MB_OK | MB_ICONERROR);
	}

	GdiplusStartupInput gdiplusStartUpToken;
	ULONG_PTR gdiplusToken;
	Status st = GdiplusStartup(&gdiplusToken, &gdiplusStartUpToken, nullptr);

	if (st != Status::Ok)
	{
		MessageBoxA(nullptr, "init gdiplus err", "fatal", MB_OK | MB_ICONERROR);
	}

	MSG msg;
	MainDlg* dlg = new MainDlg(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), nullptr);//IDHELP
	
	dlg->Show(SW_SHOW);

	while (FALSE != GetMessage(&msg, nullptr, 0, 0)) 
	{
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}

	GdiplusShutdown(gdiplusToken);

	return 0;
}