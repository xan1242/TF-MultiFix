//
// Yu-Gi-Oh! Tag Force - Konami Code window
// by xan1242 / Tenjoin
//

#ifndef KONAMIDIALOG_H
#define KONAMIDIALOG_H

#define KONAMIDIALOG_TEXT L"\
Cheat menus are now enabled!\n\
\n\
\n\
CONTROLS:\n\
=======================================\n\
 While the WLAN switch is ON:\n\
\x2022 Open global menu: R + \x25CB\n\
\x2022 Open specific menu: R + \x25A1\n\
=======================================\n\
\n\
You can also access them from the config window.\n\
\n\
Have fun!\
"

int konamidialog_Draw();
void konamidialog_Destroy();
int konamidialog_IsActive();

#endif
