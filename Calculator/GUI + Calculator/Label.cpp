#include "Label.h"



Label::Label(HWND hParent, int id) : Control(hParent, id)
{

}


Label::~Label()
{
	if (m_buffer) delete[] m_buffer;
}

void Label::SetText(const char * txt)
{
	SendMessageA(m_hWnd, WM_SETTEXT, 0, (LPARAM)txt);
}

char * Label::GetText()
{
	if (m_buffer)
	{
		delete[] m_buffer;
		m_buffer = nullptr;
	}

	int len = SendMessageA(m_hWnd, WM_GETTEXTLENGTH, 0, 0);
	m_buffer = new char[len + 1];
	m_buffer[len] = 0;

	SendMessageA(m_hWnd, WM_GETTEXT, len + 1, (LPARAM)m_buffer);
	return m_buffer;
}
