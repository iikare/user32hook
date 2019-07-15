#include "hook32.h"

using namespace std;

int wmain(){
	HANDLE hProc = NULL;
	DEVMODEW dMode = { sizeof(DEVMODE) };
	HDC screen = GetDC(NULL);

	while (true) {
		if (Mhook_SetHook((PVOID*)& TrueEnumDisplaySettingsW, HookEnumDisplaySettingsW)) {
			cout << "Success: Hooked into EnumDisplaySettingsW\n";
			EnumDisplaySettingsW(NULL, ENUM_CURRENT_SETTINGS, &dMode);

			cout << (int)dMode.dmDisplayFrequency << "\n";
		}
		else {
			cout<< "Failure to Hook into EnumDisplaySettingsW with Error Code: "  << GetLastError() << "\n";
		}

		if (Mhook_SetHook((PVOID*)& TrueGetDeviceCaps, HookGetDeviceCaps)) {
			cout << "Success: Hooked into GetDeviceCaps\n";
		}
		else {
			cout << "Failure to Hook into GetDeviceCaps with Error Code: " << GetLastError() << "\n";
		}

		cout << "VRefresh: "  << GetDeviceCaps(screen, VREFRESH) << "\n";

		Sleep(100);

		//_getch(); //prevent autoexit
		if (GetKeyState(88) != false) {	//x
			break;
		}
	}

	Mhook_Unhook((PVOID*)& TrueEnumDisplaySettingsW);

	return 0;
}

