TARGET = ../../build/TF6-MultiFix
OBJS = ../../includes/psp/minjector.o \
       main.o \
       helpers.o \
       multifix.o \
       multifixconfig.o \
       dueleng.o \
       duelmgr.o \
       dueldraw.o \
       deck.o \
       shop.o \
       field.o \
       charalist.o \
       tutoriallist.o \
       duelrecord.o \
       umdreplace.o \
       decktutorial.o \
       tutorial.o \
       password.o \
       selectcard.o \
       cardalbum.o \
       soundtest.o \
       gallery.o \
       recipeviewer.o \
       story.o \
       title.o \
       YgWindow.o \
       MenuWindow.o \
       DialogWindow.o \
       WindowManager.o \
       windows/multifixwindow.o \
       windows/installdisabledialog.o \
       windows/aboutwindow.o \
       windows/konamidialog.o \
       windows/cheatmenu_duel.o \
       windows/cheatmenu_global.o \
       windows/cheatmenu_trust.o \
       exports.o \
       ../../includes/psp/pspmallochelper.o \
       ../../includes/psp/stringhash.o
       

DEFINES = -DMINJECTOR_MINIMAL -DYGWINDOW_ESSENTIALS_ONLY

CFLAGS = -O2 -Os -G0 -Wall -fshort-wchar -fwide-exec-charset=wchar_t -fno-pic -mno-check-zero-division -fpack-struct=16 $(DEFINES)
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

BUILD_PRX = 1
PRX_EXPORTS = exports.exp

LIBS = -lpspsystemctrl_user -lpspkubridge -lm

PSPSDK = $(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build_prx.mak
