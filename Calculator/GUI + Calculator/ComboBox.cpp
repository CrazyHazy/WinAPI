#include "ComboBox.h"



ComboBox::ComboBox(HWND hParent, int id) : Control(hParent, id)
{

}


ComboBox::~ComboBox()
{
}

void ComboBox::AddString(const char * str)
{
	SendMessageA(m_hWnd, CB_ADDSTRING, 0, LPARAM(str));
}

char * ComboBox::GetItemText(int index)
{
	if (index == -1) 
	{
		return nullptr;
	}

	if (m_buffer)
	{
		delete[] m_buffer;
		m_buffer = nullptr;
	}

	int len = SendMessageA(m_hWnd, CB_GETLBTEXTLEN, index, 0);
	m_buffer = new char[len + 1];
	m_buffer[len] = 0;

	SendMessageA(m_hWnd, CB_GETLBTEXT, index, (LPARAM)m_buffer);

	return m_buffer;

}

int ComboBox::GetSelectedItemID()
{
	return SendMessageA(m_hWnd, CB_GETCURSEL, 0, 0);
}
