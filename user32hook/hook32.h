#pragma once

#include <windows.h>
#include <conio.h>
#include <iostream>
#include <mhook-lib/mhook.h>

#define ALTERNATIVE_REFRESH 144

using namespace std;

typedef BOOL(WINAPI* _EnumDisplaySettingsW)(
	IN LPCWSTR lpszDeviceName,
	IN DWORD iModeNum,
	OUT LPDEVMODEW lpDevMode);

typedef BOOL(WINAPI* _GetDeviceCaps)(
	IN HDC hdc,
	IN int index);

_EnumDisplaySettingsW TrueEnumDisplaySettingsW = (_EnumDisplaySettingsW)
GetProcAddress(GetModuleHandle("user32"), "EnumDisplaySettingsW");

_GetDeviceCaps TrueGetDeviceCaps = (_GetDeviceCaps)
GetProcAddress(GetModuleHandle("gdi32"), "GetDeviceCaps");

BOOL WINAPI HookEnumDisplaySettingsW(IN LPCWSTR lpszDeviceName, IN DWORD iModeNum, OUT DEVMODEW* lpDevMode) {
	BOOL setFlag = FALSE;

	cout << "Call to EnumDisplaySettingsW\n";

	if (TrueEnumDisplaySettingsW((LPCWSTR)lpszDeviceName, (DWORD)iModeNum, (DEVMODEW*)lpDevMode)) {
		setFlag = TRUE;
	}
	else {
		cout << "Could not retrieve display settings.\n";
	}

	lpDevMode->dmDisplayFrequency = 144;

	return setFlag;
}

BOOL WINAPI HookGetDeviceCaps(IN HDC hdc, IN int index) {

	cout << "Call to GetDeviceCaps\n";

	if (index == VREFRESH) {
		return ALTERNATIVE_REFRESH;
	}
	else {
		return TrueGetDeviceCaps(hdc, index);
	}
}