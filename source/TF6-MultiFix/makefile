TARGET = ../../build/TF6-MultiFix
# include more objs here depending on what you use (e.g. "../../includes/psp/mips.o")
OBJS = main.o helpers.o multifix.o multifixconfig.o dueleng.o duelmgr.o dueldraw.o deck.o shop.o field.o charalist.o tutoriallist.o duelrecord.o umdreplace.o decktutorial.o tutorial.o password.o selectcard.o cardalbum.o soundtest.o gallery.o recipeviewer.o story.o title.o YgWindow.o exports.o ../../includes/psp/pspmallochelper.o ../../includes/psp/stringhash.o ../../includes/psp/minjector.o

DEFINES = -DMINJECTOR_MINIMAL

CFLAGS = -O2 -Os -G0 -Wall -fshort-wchar -fwide-exec-charset=wchar_t -fno-pic -mno-check-zero-division -fpack-struct=16 $(DEFINES)
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

BUILD_PRX = 1
PRX_EXPORTS = exports.exp

LIBS = -lpspsystemctrl_user -lpspkubridge -lm

PSPSDK = $(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build_prx.mak
