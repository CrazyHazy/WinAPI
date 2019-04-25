#pragma once
#include<Windows.h>
#include<TlHelp32.h>
class MemoryManager
{
private:

	void ReloadPID();
	bool DataCompare(byte* data,  byte* sign, char* mask);

	char*	m_pName;
	HANDLE	m_hProc;
	DWORD	m_pID = 0;
	byte*	m_buffer;
	size_t	m_buffer_size;


public:
	MemoryManager(const char* proc_name, size_t buffer_size = 32);
	~MemoryManager();

	DWORD GetPID();

	void Open(DWORD access = PROCESS_ALL_ACCESS);
	void Close();

	DWORD Alloc(DWORD mem_protect = PAGE_EXECUTE_READWRITE);
	void Free(void* ptr);

	void GetModuleInfo(char* module_name, MODULEENTRY32* m_info, bool about_process = false);
	
	DWORD FindSignature(DWORD base, DWORD size, byte* sign, char* mask);
	
	void Write(void* ptr, DWORD to, size_t size, DWORD mem_protect = PAGE_EXECUTE_READWRITE);

	MemoryManager& Read(DWORD from, size_t size, DWORD mem_protect = PAGE_READWRITE);
	DWORD ReadPointer(DWORD base, DWORD* offset, size_t count);

	//it's bad iknow
	double	  ToDouble();
	float	  ToFloat();	
	UINT64	  ToUINT64();
	INT64	  ToINT64();
	UINT32	  ToUINT32();
	INT32	  ToINT32();
	UINT16	  ToUINT16();
	INT16	  ToINT16();
	UINT8	  ToUINT8();
	INT8	  ToINT8();
	char*	  ToStringA();
	wchar_t*  ToStringW();


};

