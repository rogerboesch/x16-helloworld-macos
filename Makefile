
#== Project config ==
#Build mode: debug or release
BUILDTARGET	:= release

BUILDDIR	:= build
OBJDIR		:= obj
INCDIR		:= include
SRCDIR		:= src
RESDIR		:= $(SRCDIR)/res
TOOLDIR		:= tools
OUTPRG		:= $(BUILDDIR)/hello.prg
LIBS		:= cx16.lib
SDCARD		:= 

#== Build tools ==
MKDIR		:= mkdir

#== Target system config ==
TARGET		:= cx16
CFGFILE		:= cx16.cfg

#== Emulator config ==
#Emulator path
X16EMU		:= x16emu
EFLAGS		= 

#Uncomment to launch the PRG on start-up
EFLAGS		+= -run

#Uncomment to position the window at right (needs patch of emulator)
EFLAGS		+= -position right

#Uncomment to attach the SD card image specified above
#EFLAGS		+= -sdcard $(SDCARD)

#Uncomment to enable the emulator's debugger functionality
EFLAGS		+= -debug

#Set to true if the emulator should run from the build directory.
#Otherwise, it will run from current directory (in case you want to mount an SD card image over there)
EMUCHDIR	:= false

#== Compiler config ==
#CC65 binary path (with trailing /). Leave blank to find in system path
CCPATH		:= 

#Compiler Binaries
CC			:= $(CCPATH)cl65
AS			:= $(CCPATH)ca65
LD			:= $(CCPATH)ld65

#Compiler flags
FLAGS		= -t $(TARGET) -I $(INCDIR) -I $(SRCDIR) --create-dep $(OBJDIR)/$*.d
CFLAGS		= $(FLAGS) -c -l $@.lst -O
AFLAGS		= $(FLAGS)
LFLAGS		= -C $(CFGFILE) -m $(BUILDDIR)/memory.map

#== Build targets ==
#List of all source files to be compiled/assembled
M_SRC		= $(wildcard $(SRCDIR)/*.c)
M_ASM		= $(wildcard $(SRCDIR)/*.asm)

#List of all object files that will be created
OBJ_SRC		= $(addprefix $(OBJDIR)/,$(patsubst %.c,%.o,$(notdir $(M_SRC))))
OBJ_ASM		= $(addprefix $(OBJDIR)/,$(patsubst %.asm,%.o,$(notdir $(M_ASM))))

#Final list of objects to link
OBJS		= $(OBJ_ASM) $(OBJ_SRC)

#Dependency files created by the compiler
DEPS		= $(OBJS:%.o=%.d)

#== Build goals ==
all: $(BUILDTARGET)

debug: FLAGS += -d -D _DEBUG
debug: $(OUTPRG)

release: $(OUTPRG)

#Link final PRG file
$(OUTPRG): $(OBJS) | resources $(BUILDDIR)
	$(LD) $(LFLAGS) -o $@ $^ $(LIBS)

#Assemble .asm source files to object code
$(OBJDIR)/%.o: $(SRCDIR)/%.asm | binres $(OBJDIR)
	$(AS) $(AFLAGS) -o $@ $<

#Compile .c source files to object code
$(OBJDIR)/%.o: $(SRCDIR)/%.c | binres $(OBJDIR)
	$(CC) $(CFLAGS) -o $@ $<

#== Resources and Assets ==
#Generate binary/object files for assets/resources at link-time
resources: binres

#Resources that will be included directly in a source file
#These will be generated before compiling any source
binres: $(OBJDIR)

#Include Makefile for resources. You can add more dependencies to 'resources' and 'binres'
-include $(RESDIR)/Makefile

#Load dependency files, if they exist
-include $(DEPS)

#Build the target, then launch the emulator
run: $(BUILDTARGET) runemu

#Launch emulator with the input PRG file
runemu: $(OUTPRG) | $(if $(findstring -sdcard, $(EFLAGS)), $(SDCARD))
ifeq ($(EMUCHDIR), true)
	cd $(dir $<) && $(X16EMU) $(EFLAGS) -prg $(notdir $<)
else
	$(X16EMU) $(EFLAGS) -prg $<
endif

#Create directories for output files, if they don't exist
$(BUILDDIR) $(OBJDIR):
	$(MKDIR) $(subst /,\,$@)