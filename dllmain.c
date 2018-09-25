#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#pragma comment(lib, "Version")

int (__stdcall *O_AIL_open_stream)(void *, char *, int);
int __stdcall H_AIL_open_stream(void *ptr, char *stream, int arg3)
{
	char szPath[MAX_PATH];
	char *temp;
	int ret;
	char *basePath = (char *)0x3CFA788;

	temp = strrchr(basePath, '/');

	sprintf(szPath, "%s%s", temp ? temp + 1 : basePath, stream + 5);
	if (ret = O_AIL_open_stream(ptr, szPath, arg3)) return ret;

	return O_AIL_open_stream(ptr, stream, arg3);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	DWORD_PTR dwPatchBase;
	DWORD dwOldProtect;

	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		char szPath[MAX_PATH];
		DWORD dwSize;
		DWORD dwHandle;
		void *pVersionInfo;
		char *pStringFileInfoValue;
		UINT fileInfoLen;

		DisableThreadLibraryCalls(hinstDLL);

		GetModuleFileName(NULL, szPath, sizeof(szPath));

		if (!(dwSize = GetFileVersionInfoSize(szPath, &dwHandle)))
		{
			goto fail;
		}

		if (!(pVersionInfo = malloc(dwSize)))
		{
			goto fail;
		}

		if (!GetFileVersionInfo(szPath, dwHandle, dwSize, pVersionInfo)
			|| !VerQueryValue(pVersionInfo, "\\StringFileInfo\\040904b0\\FileDescription", (LPVOID *)&pStringFileInfoValue, &fileInfoLen)
			|| strcmp(pStringFileInfoValue, "Half-Life Launcher")
			|| !VerQueryValue(pVersionInfo, "\\StringFileInfo\\040904b0\\FileVersion", (LPVOID *)&pStringFileInfoValue, &fileInfoLen)
			|| strcmp(pStringFileInfoValue, "1, 1, 1, 0"))
		{
			free(pVersionInfo);
fail:		return FALSE;
		}

		free(pVersionInfo);

		dwPatchBase = 0x404541;
		if (*(BYTE *)dwPatchBase == 27)
		{
			VirtualProtect((LPVOID)dwPatchBase, sizeof(BYTE), PAGE_EXECUTE_READWRITE, &dwOldProtect);
			*(BYTE *)dwPatchBase = 28;
			VirtualProtect((LPVOID)dwPatchBase, sizeof(BYTE), dwOldProtect, &dwOldProtect);
		}

		dwPatchBase = 0x4AD7E8;
		VirtualProtect((LPVOID)dwPatchBase, sizeof(DWORD_PTR), PAGE_READWRITE, &dwOldProtect);

		(DWORD_PTR)O_AIL_open_stream = *(DWORD_PTR *)dwPatchBase;
		*(DWORD_PTR *)dwPatchBase = (DWORD_PTR)H_AIL_open_stream;

		VirtualProtect((LPVOID)dwPatchBase, sizeof(DWORD_PTR), dwOldProtect, &dwOldProtect);
	}
	else if (fdwReason == DLL_PROCESS_DETACH)
	{
		if (O_AIL_open_stream)
		{
			dwPatchBase = 0x4AD7E8;
			VirtualProtect((LPVOID)dwPatchBase, sizeof(DWORD_PTR), PAGE_READWRITE, &dwOldProtect);

			*(DWORD_PTR *)dwPatchBase = (DWORD_PTR)O_AIL_open_stream;

			VirtualProtect((LPVOID)dwPatchBase, sizeof(DWORD_PTR), dwOldProtect, &dwOldProtect);
		}
	}
	return TRUE;
}
