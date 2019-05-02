#include "MemoryManager.h"




MemoryManager::MemoryManager(const char* proc_name, size_t buffer_size) : m_buffer_size(buffer_size)
{
	int len = strlen(proc_name) + 1;
	m_pName = new char[len];
	strcpy_s(m_pName, len, proc_name);

	m_buffer = new byte[buffer_size];
}

MemoryManager::~MemoryManager()
{
	delete[] m_pName;
	delete[] m_buffer;
}

DWORD MemoryManager::GetPID()
{
	return m_pID;
}

void MemoryManager::ReloadPID()
{
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 p_info;
	p_info.dwSize = sizeof(PROCESSENTRY32);

	if (Process32First(snapshot, &p_info))
	{
		while (Process32Next(snapshot, &p_info))
		{
			if (_strcmpi(m_pName, p_info.szExeFile) == 0)
			{
				m_pID = p_info.th32ParentProcessID;
				CloseHandle(snapshot);
				return;
			}
		}
	}
	else
	{
		CloseHandle(snapshot);
		m_pID = 0;
		return;
	}
}

bool MemoryManager::DataCompare(byte * data, byte * sign, char * mask)
{
	for (; *mask; mask++, sign++, data++) 
	{
		if (*mask == 'x' && *data != *sign) 
		{
			return false;
		}
	}
	return true;
}
 


void MemoryManager::Open(DWORD access)
{
	ReloadPID();
	m_hProc = OpenProcess(access, false, m_pID);
}

void MemoryManager::Close()
{
	CloseHandle(m_hProc);
}

DWORD MemoryManager::Alloc(DWORD mem_protect)
{
	return (DWORD)VirtualAllocEx(m_hProc, nullptr, 0x1000, MEM_COMMIT | MEM_RESERVE, mem_protect);
}

void MemoryManager::Free(void * ptr)
{
	VirtualFreeEx(m_hProc, ptr, 0, MEM_RELEASE);
}

void MemoryManager::GetModuleInfo(char * module_name, MODULEENTRY32 * m_info, bool about_process)
{

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, m_pID);
	
	m_info->dwSize = sizeof(MODULEENTRY32);


	if (Module32First(snapshot, m_info))
	{
		if (about_process)
		{
			CloseHandle(snapshot);
			return;
		}
		while (Module32Next(snapshot, m_info))
		{
			if (_strcmpi(m_pName, m_info->szModule) == 0)
			{
				CloseHandle(snapshot);
				return;
			}
		}
	}
	else
	{
		CloseHandle(snapshot);
		m_pID = 0;
		return;
	}
}

DWORD MemoryManager::FindSignature(DWORD base, DWORD size, byte * sign, char * mask)
{
	MEMORY_BASIC_INFORMATION mbi = { 0 };
	DWORD offset = 0;

	while (offset < size)
	{
		VirtualQueryEx(m_hProc, (LPCVOID)(base + offset), &mbi, sizeof(MEMORY_BASIC_INFORMATION));
		if (mbi.State != MEM_FREE)
		{
			byte* buffer = new byte[mbi.RegionSize];
			ReadProcessMemory(m_hProc, mbi.BaseAddress, buffer, mbi.RegionSize, nullptr);

			for (int i = 0; i < mbi.RegionSize; i++) 
			{
				if (DataCompare(buffer + i, sign, mask)) 
				{
					delete[] buffer;
					return (DWORD)mbi.BaseAddress + i;
				}
			}
			delete[] buffer;
		}
		offset += mbi.RegionSize;
	}

	return 0;

}


void MemoryManager::Write(void * ptr, DWORD to, size_t size, DWORD mem_protect)
{
	DWORD old_mem_protect = 0;
	VirtualProtectEx(m_hProc, &to, size, mem_protect, &old_mem_protect);
	WriteProcessMemory(m_hProc, &to, ptr, size, nullptr);
	VirtualProtectEx(m_hProc, &to, size, old_mem_protect, &old_mem_protect);

}


MemoryManager & MemoryManager::Read(DWORD from, size_t size, DWORD mem_protect)
{
	
	DWORD old_mem_protect = 0;
	memset(m_buffer, 0, m_buffer_size);
	ReadProcessMemory(m_hProc, &from, m_buffer, size, nullptr);
	VirtualProtectEx(m_hProc, &from, size, mem_protect, &old_mem_protect);
	VirtualProtectEx(m_hProc, &from, size, old_mem_protect, &old_mem_protect);
	return *this;

}

DWORD MemoryManager::ReadPointer(DWORD base, DWORD * offset, size_t count)
{
	for (int i = 0; i < count - 1; i++) {
		base = Read(base + offset[i], 4).ToUINT32();
	}
	return base + offset[count - 1];
}

// ye it's totally bad
double MemoryManager::ToDouble()
{
	double temp = 0;
	memcpy(m_buffer, &temp, sizeof(double));
	return temp;
}

float MemoryManager::ToFloat()
{
	float temp = 0;
	memcpy(m_buffer, &temp, sizeof(float));
	return temp;
}

UINT64 MemoryManager::ToUINT64()
{
	UINT64 temp = 0;
	memcpy(m_buffer, &temp, sizeof(UINT64));
	return temp;
}

INT64 MemoryManager::ToINT64()
{
	INT64 temp = 0;
	memcpy(m_buffer, &temp, sizeof(INT64));
	return temp;
}

UINT32 MemoryManager::ToUINT32()
{
	UINT32 temp = 0;
	memcpy(m_buffer, &temp, sizeof(UINT32));
	return temp;
}

INT32 MemoryManager::ToINT32()
{
	INT32 temp = 0;
	memcpy(m_buffer, &temp, sizeof(INT32));
	return temp;

}

UINT16 MemoryManager::ToUINT16()
{
	UINT16 temp = 0;
	memcpy(m_buffer, &temp, sizeof(UINT16));
	return temp;
}

INT16 MemoryManager::ToINT16()
{

	INT16 temp = 0;
	memcpy(m_buffer, &temp, sizeof(short int));
	return temp;
}

UINT8 MemoryManager::ToUINT8()
{
	UINT8 temp = 0;
	memcpy(m_buffer, &temp, sizeof(UINT8));
	return temp;
}

INT8 MemoryManager::ToINT8()
{
	INT8 temp = 0;
	memcpy(m_buffer, &temp, sizeof(char));
	return temp;
}

char * MemoryManager::ToStringA()
{
	return (char*)m_buffer;
}

wchar_t * MemoryManager::ToStringW()
{
	return (wchar_t*)m_buffer;
}

