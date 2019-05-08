#pragma once
#include "Control.h"
class Label : public Control
{
private:
	char* m_buffer = nullptr;
public:
	DWORD textColor = 0;
	DWORD background = 0;
	bool isTransparent = false;

	Label(HWND hParent, int id);
	~Label();

	void SetText(const char* txt);
	char* GetText();

	
};

