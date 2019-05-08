#include "EditBox.h"



EditBox::EditBox(HWND hParent, int id) : Control(hParent, id)
{

}


EditBox::~EditBox()
{
	if (m_buffer) delete[] m_buffer;
}



char * EditBox::GetText()
{
	if (m_buffer)
	{
		delete[] m_buffer;
		m_buffer = nullptr;
	}

	int count = SendMessageA(m_hWnd, EM_GETLINECOUNT, 0, 0);

	if (count == 1)
	{
		int len = SendMessageA(m_hWnd, EM_LINELENGTH, 0, 0);

		if (len)
		{
			m_buffer = new char[len + 1];
			m_buffer[len] = 0;

			SendMessageA(m_hWnd, EM_GETLINE, 0, (LPARAM)m_buffer);
		}
	}
	else if (count)
	{
		int len = count;
		for (int i = 0; i < count; i++) {
			len += SendMessage(m_hWnd, EM_LINELENGTH, SendMessage(m_hWnd, EM_LINEINDEX, i, 0), 0);
		}

		m_buffer = new char[len + 1];
		m_buffer[len] = 0;

		for (int i = 0; i < count; i++) {
			int currentLen = SendMessage(m_hWnd, EM_LINELENGTH, SendMessage(m_hWnd, EM_LINEINDEX, i, 0), 0);

			SendMessage(m_hWnd, EM_GETLINE, i, (LPARAM)m_buffer);

			m_buffer[currentLen] = '\n';
			m_buffer += currentLen + 1;
		}
		m_buffer -= len;
	}

	return m_buffer;
}

void EditBox::SetText(const char* text)
{
	SendMessage(m_hWnd, WM_SETTEXT, 0, (LPARAM)text);
}

void EditBox::AppendText(const char* text)
{
	DWORD startPos;
	DWORD endPos = 0;

	SendMessageA(m_hWnd, EM_GETSEL, (WPARAM)&startPos, (LPARAM)&endPos);

	int outLenght = GetWindowTextLengthA(m_hWnd);
	
	SendMessageA(m_hWnd, EM_SETSEL, outLenght, outLenght);
	SendMessageA(m_hWnd, EM_REPLACESEL, TRUE, (LPARAM)text);
	SendMessageA(m_hWnd, EM_SETSEL, startPos, endPos);

}
