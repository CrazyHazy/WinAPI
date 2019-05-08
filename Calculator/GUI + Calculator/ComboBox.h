#pragma once
#include"Control.h"
class ComboBox : public Control
{
private:
	char* m_buffer = nullptr;

public:
	ComboBox(HWND hParent, int id);
	~ComboBox();

	void AddString(const char* str);
	char* GetItemText(int index);
	int GetSelectedItemID();

};

