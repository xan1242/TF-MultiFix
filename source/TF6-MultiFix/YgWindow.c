//
// Yu-Gi-Oh! Tag Force - ygBasicWindow & YgSelWnd interface
// by xan1242 / Tenjoin
//

#include "YgWindow.h"

uintptr_t(*_YgSelWnd_Init)(YgSelWnd* window) = (uintptr_t(*)(YgSelWnd*))(0);
uintptr_t(*_YgSelWnd_Cont)(YgSelWnd* window) = (uintptr_t(*)(YgSelWnd*))(0);
uintptr_t(*_YgSelWnd_Draw)(uintptr_t ehpacket, YgSelWnd* window) = (uintptr_t(*)(uintptr_t, YgSelWnd*))(0);

uintptr_t YgSelWnd_Init(YgSelWnd* window)
{
    return _YgSelWnd_Init(window);
}

uintptr_t YgSelWnd_Cont(YgSelWnd* window)
{
    return _YgSelWnd_Cont(window);
}

uintptr_t YgSelWnd_Draw(uintptr_t ehpacket, YgSelWnd* window)
{
    return _YgSelWnd_Draw(ehpacket, window);
}

void YgWindow_Init(uintptr_t base_addr)
{
    _YgSelWnd_Init = (uintptr_t(*)(YgSelWnd*))(0x67A0 + base_addr);
    _YgSelWnd_Cont = (uintptr_t(*)(YgSelWnd*))(0x7534 + base_addr);
    _YgSelWnd_Draw = (uintptr_t(*)(uintptr_t, YgSelWnd*))(0x6A84 + base_addr);
}
