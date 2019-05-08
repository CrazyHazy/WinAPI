#pragma once
#include<Windows.h>
#include"Control.h"
class EditBox : public Control
{
private:
	char* m_buffer = nullptr;

public:
	EditBox(HWND hParent, int id);
	~EditBox();

	char* GetText();
	void SetText(const char* text);
	void AppendText(const char* text);

};

