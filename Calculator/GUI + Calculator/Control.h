#pragma once
#include<Windows.h>
class Control
{
public:
	Control(HWND hParent, int id);
	virtual ~Control();

	void SetFont(HFONT hFont);
	HFONT GetFont();
	RECT GetPositionRect();

	HWND GetHandle();
	HWND GetPatern();
	int GetID();

protected:
	HWND m_hWnd;
	HWND m_hParent;
	int m_id;
};

