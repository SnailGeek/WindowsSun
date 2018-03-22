#include "CmnHdr.h"
#include <Windows.h>
#include <tchar.h>
#include <strsafe.h>

void DumpEnvStrings()
{
	PTSTR pEnvBlock = GetEnvironmentStrings();

	TCHAR szName[MAX_PATH];
	TCHAR szVaule[MAX_PATH];
	PTSTR pszCurrent = pEnvBlock;
	HRESULT hr = S_OK;
	PCTSTR pszPos = NULL;
	int current = 0;
	while(pszCurrent != NULL)
	{
		if(*pszCurrent != TEXT('='))
		{
			pszPos = _tcschr(pszCurrent, TEXT('='));
			pszPos++;

			size_t cbNameLength = (size_t)pszPos - (size_t)pszCurrent - sizeof(TCHAR);
			hr = StringCbCopyN(szName, MAX_PATH, pszCurrent, cbNameLength);
			if(FAILED(hr))
			{
				break;
			}

			hr = StringCchCopyN(szVaule, MAX_PATH, pszPos, _tcslen(pszPos)+1);
			if(SUCCEEDED(hr))
			{
				_tprintf(TEXT("[%u] %s=%s\r\n"), current, szName, szVaule);
			}
			else
			{
				_tprintf(
					TEXT("[%u] %s = ???\r\n"), current, szName
					);
				break;
			}
		}
		else
		{
			_tprintf(TEXT("[%u] %\r\n"), current, pszCurrent);
		}
		current++;
		while(*pszCurrent != TEXT('\0'))
			pszCurrent++;
		pszCurrent++;
		if(*pszCurrent == TEXT('\0'))
		{
			break;
		}
	}
	FreeEnvironmentStrings(pEnvBlock);
}

int main()
{
	DumpEnvStrings();
	system("pause");
	return 0;
}