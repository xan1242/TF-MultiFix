//
// Yu-Gi-Oh! Tag Force - Window manager class
// by xan1242 / Tenjoin
//

#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#define WINDOWMANAGER_DISP_MFWINDOW (1)
#define WINDOWMANAGER_DISP_ABOUT (1 << 1)
#define WINDOWMANAGER_DISP_KONAMI (1 << 2)
#define WINDOWMANAGER_DISP_CHEATGLOBAL (1 << 3)
#define WINDOWMANAGER_DISP_CHEATDUEL (1 << 4)
#define WINDOWMANAGER_DISP_TRUSTMENU (1 << 5)

//unsigned int WM_GetDispMask();
//void WM_SetDispMask(unsigned int mask);
void WM_DestroyAllWindows();
int WM_bIsAnyWindowShown();
void WM_Draw();
void WM_SwitchToWindow(unsigned int windowMask);
void WM_ShowWindow(unsigned int windowMask);


#endif