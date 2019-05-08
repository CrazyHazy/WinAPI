#pragma once
#include<Windows.h>
#include"Control.h"
class Button : public Control
{
public:
	Button(HWND hParent, int id);
	~Button();
};

