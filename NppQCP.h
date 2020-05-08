
#ifndef PLUGINDEFINITION_H
#define PLUGINDEFINITION_H


#include "PluginInterface.h"
#include "csscolorparser.hpp"

const TCHAR NPP_PLUGIN_NAME[] = TEXT("Quick Color Picker");
const TCHAR NPP_PLUGIN_VER[] = TEXT("1.0");

const int COMMNAD_COUNT = 7;

void AttachDll(HANDLE module);

void PluginInit();
void PluginCleanUp();


void LoadConfig();
void SaveConfig();

void InitCommandMenu();
void commandMenuCleanUp();
bool setCommand(size_t index, TCHAR *cmdName, PFUNCPLUGINCMD pFunc, ShortcutKey *sk = NULL, bool check0nInit = false);


////////////////////////////////////////////
void InvokeColorPicker(bool use_screen_picker = false);
void InsertByPalette();
void PickFromScreen();

void ToggleQCP();
void ToggleColorHighlight();
void VisitWebsite();

HWND GetScintilla();

void CreateMessageWindow();
void DestroyMessageWindow();
LRESULT CALLBACK MessageWindowWinproc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

void AddNppSubclass();
void RemoveNppSubclass();
LRESULT CALLBACK NppSubclassProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);

void CreateColorPicker();

bool ShowColorPicker();
void HideColorPicker();
bool HasSelection();
void PlaceColorPickerAt(HWND h_scintilla, int pos);

bool CheckSelectionForHexColor(const HWND h_scintilla, const int start, const int end);
bool CheckSelectionForBracketColor(const HWND h_scintilla, const int start, const int end);

void WriteColor(COLORREF color);

void LoadRecentColor();
void SaveRecentColor();

void HighlightColorCode();

void EmptyColorMarker();
bool SaveColorMarker(CSSColorParser::Color color, int marker_start, int marker_end);

void FindHexColor(const HWND h_scintilla, const int start_position, const int end_position);
void FindBracketColor(const HWND h_scintilla, const int start_position, const int end_position, char* suff);

void DrawColorMarkers(const HWND h_scintilla);
void ClearColorMarkers();

#endif //PLUGINDEFINITION_H
