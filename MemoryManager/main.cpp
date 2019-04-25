#include<iostream>
#include "MemoryManager.h"


int main() {

	MemoryManager* mem = new MemoryManager("notepad.exe", 3200);
	MODULEENTRY32 mod = { 0 };


	mem->Open();
 	mem->GetModuleInfo(nullptr, &mod, true);

	std::cout << "process base : " << mod.modBaseAddr << std::endl;
	std::cout << "process size : " << mod.modBaseSize << std::endl;
	std::cout << "PID :" << mem->GetPID() << std::endl;
	
	mem->Close();


	system("PAUSE");
}