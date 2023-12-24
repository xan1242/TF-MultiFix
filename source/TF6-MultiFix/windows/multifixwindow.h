//
// Yu-Gi-Oh! Tag Force - MultiFix configuration window
// by xan1242 / Tenjoin
//

#ifndef MULTIFIXWINDOW_H
#define MULTIFIXWINDOW_H

typedef struct _mfWindowSetting
{
    int* val;
    float* fval;
    int min;
    int max;
    float fmin;
    float fmax;
    int type;
    int hidden;
    int selectable;
    int greyedout;
    int loopable;
    int index;
    char* name;
    char* description;
}mfWindowSetting;

typedef enum _mfWindowSettingType
{
    MFWINDOW_SETTING_TYPE_UNK = -1,
    MFWINDOW_SETTING_TYPE_INT,
    MFWINDOW_SETTING_TYPE_BOOL,
    MFWINDOW_SETTING_TYPE_FLOAT,
    MFWINDOW_SETTING_TYPE_INTSTRING,
    MFWINDOW_SETTING_TYPE_NONE,
    MFWINDOW_SETTING_TYPE_COUNT
}mfWindowSettingType;

typedef enum _mfWindowItem
{
    MFWINDOW_ITEM_UNK = -1,
    MFWINDOW_ITEM_SWAPBUTTON,
    MFWINDOW_ITEM_MATRIXFONT,
    MFWINDOW_ITEM_PARTNERCARD,
    MFWINDOW_ITEM_DUELHELP,
    MFWINDOW_ITEM_INSTALLDISABLE,
    MFWINDOW_ITEM_SOUNDTEST,
    MFWINDOW_ITEM_CHEATSGLOBAL,   // do not touch position of this
    MFWINDOW_ITEM_CHEATSLOCAL,    // do not touch position of this
    MFWINDOW_ITEM_ABOUT,          // do not touch position of this
    MFWINDOW_ITEM_COUNT
}mfWindowItem;

#define MFWINDOW_ITEM_NAME_SWAPBUTTON       "Use X as confirm button"
#define MFWINDOW_ITEM_NAME_MATRIXFONT       "Matrix font on cards"
#define MFWINDOW_ITEM_NAME_PARTNERCARD      "See partner's cards"
#define MFWINDOW_ITEM_NAME_DUELHELP         "Disable duel \"Help\" icon"
#define MFWINDOW_ITEM_NAME_INSTALLDISABLE   "Disable install feature"
#define MFWINDOW_ITEM_NAME_SOUNDTEST        "Sound Test"
#define MFWINDOW_ITEM_NAME_CHEATSGLOBAL     "Cheats (global)"
#define MFWINDOW_ITEM_NAME_CHEATSLOCAL      "Cheats (specifics)"
#define MFWINDOW_ITEM_NAME_ABOUT            "About MultiFix"

#define MFWINDOW_ITEM_DESC_SWAPBUTTON       "Swaps cross and circle as confirm buttons."
#define MFWINDOW_ITEM_DESC_MATRIXFONT       "Enables matrix font style (uppercase glyphs for lowercase letters) on card names, types, etc."
#define MFWINDOW_ITEM_DESC_PARTNERCARD      "Shows partner's cards mid-duel, just like the older Tag Force games."
#define MFWINDOW_ITEM_DESC_DUELHELP         "Disables the \"Help\" icon in the lower right corner during duels. The icon can obstruct the visibility of the card there."
#define MFWINDOW_ITEM_DESC_INSTALLDISABLE   "Disables the \"Install Data\" feature. It is recommended to keep it disabled as it could potentially cause issues for translations and/or mods. This acts as a safe guard against it."
#define MFWINDOW_ITEM_DESC_SOUNDTEST        "Play sound effects & music. (UNIMPLEMENTED)"
#define MFWINDOW_ITEM_DESC_CHEATSGLOBAL     "Cheats that affect the entire game."
#define MFWINDOW_ITEM_DESC_CHEATSLOCAL      "Cheats that are specific to the mode that you're currently in."
#define MFWINDOW_ITEM_DESC_ABOUT            "About this plugin."

#define MFWINDOW_LABEL_BOOL_TRUE "<On>"
#define MFWINDOW_LABEL_BOOL_FALSE "<Off>"
#define MFWINDOW_SELWIDTH_DIFF 12

int mfwindow_Draw();
int mfwindow_GetItemCount();
void mfwindow_SetCheatsEnabled(int val);
//void mfwindow_SetCheatLocals(int val);
int mfwindow_IsActive();
void mfwindow_Destroy();
void mfWindowSetting_AddInt(mfWindowSetting* setting, int addval);
void mfWindowSetting_HandleExtraControls(mfWindowSetting* setting);

#endif