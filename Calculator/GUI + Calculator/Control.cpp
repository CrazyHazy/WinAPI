#include "Control.h"

Control::Control(HWND hParent, int id)
{
	m_hWnd = GetDlgItem(hParent, id);
	m_hParent = hParent;
}

Control::~Control()
{
}

void Control::SetFont(HFONT hFont)
{
	SendMessageA(m_hWnd, WM_SETFONT, (WPARAM)hFont, false);
}

HFONT Control::GetFont()
{
	return (HFONT)SendMessageA(m_hWnd, WM_GETFONT, 0, 0);
}

RECT Control::GetPositionRect()
{
	RECT ctrRect = { 0 };
	GetWindowRect(m_hWnd, &ctrRect);
	
	POINT p1 = { ctrRect.left, ctrRect.top };
	POINT p2 = { ctrRect.right, ctrRect.bottom };

	ScreenToClient(m_hParent, &p1);
	ScreenToClient(m_hParent, &p2);

	ctrRect.left = p1.x;
	ctrRect.top = p1.y;
	ctrRect.right = p2.x;
	ctrRect.bottom = p2.y;
	
	return ctrRect;
}

HWND Control::GetHandle()
{
	return this->m_hWnd;
}

HWND Control::GetPatern()
{
	return this->m_hParent;
}

int Control::GetID()
{
	return this->m_id;
}
