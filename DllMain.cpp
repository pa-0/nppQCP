
#include "stdio.h"
#include <shlwapi.h>

#include "NppQCP.h"


extern FuncItem funcItem[COMMNAD_COUNT];
extern NppData nppData;
extern bool doCloseTag;


BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  reasonForCall, 
                       LPVOID lpReserved ) {

    switch (reasonForCall) {
      case DLL_PROCESS_ATTACH:
        AttachDll(hModule);
        break;
      case DLL_PROCESS_DETACH:
        PluginCleanUp();
        break;
      case DLL_THREAD_ATTACH:
        break;
      case DLL_THREAD_DETACH:
        break;
    }

    return TRUE;

}


extern "C" __declspec(dllexport) void setInfo(NppData notpadPlusData) {
	nppData = notpadPlusData;
	PluginInit();
}

extern "C" __declspec(dllexport) const TCHAR * getName() {
	return NPP_PLUGIN_NAME;
}

extern "C" __declspec(dllexport) FuncItem * getFuncsArray(int *nbF) {
	*nbF = COMMNAD_COUNT;
	return funcItem;
}


extern "C" __declspec(dllexport) void beNotified(SCNotification *notifyCode) {

	switch (notifyCode->nmhdr.code) {
		case NPPN_SHUTDOWN:
		{
			commandMenuCleanUp();
			break;
		}
		case SCN_PAINTED:
		{
			HighlightColorCode();
		}
		case SCN_UPDATEUI:
		{
			if (notifyCode->updated & SC_UPDATE_SELECTION ) {
				if (!HasSelection())
					HideColorPicker();
			}
			break;
		}
		case SCN_DOUBLECLICK:
		{
			ShowColorPicker();
			break;
		}
		case SCN_ZOOM:
		{
			HideColorPicker();
			break;
		}
		case SCN_MODIFIED:
		{
			if (notifyCode->modificationType & SC_MOD_DELETETEXT
				|| notifyCode->modificationType & SC_MOD_INSERTTEXT) {
				HideColorPicker();
            }
            break;
		}		
		case NPPN_LANGCHANGED:
		case NPPN_BUFFERACTIVATED:
		{
			HideColorPicker();
            break;
		}
		default:
		{
			// nothing
		}
	}

}


// Here you can process the Npp Messages 
// I will make the messages accessible little by little, according to the need of plugin development.
// Please let me know if you need to access to some messages :
// http://sourceforge.net/forum/forum.php?forum_id=482781
//
extern "C" __declspec(dllexport) LRESULT messageProc(UINT message, WPARAM wParam, LPARAM lParam) {
	
	if (message == WM_MOVE) {
		HideColorPicker();
	}
	return TRUE;

}

#ifdef UNICODE
extern "C" __declspec(dllexport) BOOL isUnicode() {
    return TRUE;
}
#endif //UNICODE
