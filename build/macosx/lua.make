# GNU Make project makefile autogenerated by Premake

ifndef config
  config=release
endif

ifndef verbose
  SILENT = @
endif

.PHONY: clean prebuild

SHELLTYPE := posix
ifeq ($(shell echo "test"), "test")
	SHELLTYPE := msdos
endif

# Configurations
# #############################################

ifeq ($(origin CC), default)
  CC = clang
endif
ifeq ($(origin CXX), default)
  CXX = clang++
endif
ifeq ($(origin AR), default)
  AR = ar
endif
RESCOMP = windres
TARGETDIR = bin
TARGET = $(TARGETDIR)/liblua.a
OBJDIR = obj/Release/lua
DEFINES += -DNDEBUG -DLUA_USE_MACOSX
INCLUDES +=
FORCE_INCLUDE +=
ALL_CPPFLAGS += $(CPPFLAGS) -MD -MP $(DEFINES) $(INCLUDES)
ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -x c++ -O3 -g -arch x86_64 -arch arm64 -fno-strict-aliasing -Wno-multichar -Wno-format-security
ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -x c++ -O3 -g -arch x86_64 -arch arm64 -fno-strict-aliasing -Wno-multichar -Wno-format-security
ALL_RESFLAGS += $(RESFLAGS) $(DEFINES) $(INCLUDES)
LIBS +=
LDDEPS +=
ALL_LDFLAGS += $(LDFLAGS)
LINKCMD = $(AR) -rcs "$@" $(OBJECTS)
define PREBUILDCMDS
endef
define PRELINKCMDS
endef
define POSTBUILDCMDS
endef

# Per File Configurations
# #############################################


# File sets
# #############################################

GENERATED :=
OBJECTS :=

GENERATED += $(OBJDIR)/lapi.o
GENERATED += $(OBJDIR)/lauxlib.o
GENERATED += $(OBJDIR)/lbaselib.o
GENERATED += $(OBJDIR)/lcode.o
GENERATED += $(OBJDIR)/lcorolib.o
GENERATED += $(OBJDIR)/lctype.o
GENERATED += $(OBJDIR)/ldblib.o
GENERATED += $(OBJDIR)/ldebug.o
GENERATED += $(OBJDIR)/ldo.o
GENERATED += $(OBJDIR)/ldump.o
GENERATED += $(OBJDIR)/lfunc.o
GENERATED += $(OBJDIR)/lgc.o
GENERATED += $(OBJDIR)/liolib.o
GENERATED += $(OBJDIR)/llex.o
GENERATED += $(OBJDIR)/lmathlib.o
GENERATED += $(OBJDIR)/lmem.o
GENERATED += $(OBJDIR)/loadlib.o
GENERATED += $(OBJDIR)/lobject.o
GENERATED += $(OBJDIR)/lopcodes.o
GENERATED += $(OBJDIR)/loslib.o
GENERATED += $(OBJDIR)/lparser.o
GENERATED += $(OBJDIR)/lstate.o
GENERATED += $(OBJDIR)/lstring.o
GENERATED += $(OBJDIR)/lstrlib.o
GENERATED += $(OBJDIR)/ltable.o
GENERATED += $(OBJDIR)/ltablib.o
GENERATED += $(OBJDIR)/ltm.o
GENERATED += $(OBJDIR)/lundump.o
GENERATED += $(OBJDIR)/lutf8lib.o
GENERATED += $(OBJDIR)/lvm.o
GENERATED += $(OBJDIR)/lzio.o
OBJECTS += $(OBJDIR)/lapi.o
OBJECTS += $(OBJDIR)/lauxlib.o
OBJECTS += $(OBJDIR)/lbaselib.o
OBJECTS += $(OBJDIR)/lcode.o
OBJECTS += $(OBJDIR)/lcorolib.o
OBJECTS += $(OBJDIR)/lctype.o
OBJECTS += $(OBJDIR)/ldblib.o
OBJECTS += $(OBJDIR)/ldebug.o
OBJECTS += $(OBJDIR)/ldo.o
OBJECTS += $(OBJDIR)/ldump.o
OBJECTS += $(OBJDIR)/lfunc.o
OBJECTS += $(OBJDIR)/lgc.o
OBJECTS += $(OBJDIR)/liolib.o
OBJECTS += $(OBJDIR)/llex.o
OBJECTS += $(OBJDIR)/lmathlib.o
OBJECTS += $(OBJDIR)/lmem.o
OBJECTS += $(OBJDIR)/loadlib.o
OBJECTS += $(OBJDIR)/lobject.o
OBJECTS += $(OBJDIR)/lopcodes.o
OBJECTS += $(OBJDIR)/loslib.o
OBJECTS += $(OBJDIR)/lparser.o
OBJECTS += $(OBJDIR)/lstate.o
OBJECTS += $(OBJDIR)/lstring.o
OBJECTS += $(OBJDIR)/lstrlib.o
OBJECTS += $(OBJDIR)/ltable.o
OBJECTS += $(OBJDIR)/ltablib.o
OBJECTS += $(OBJDIR)/ltm.o
OBJECTS += $(OBJDIR)/lundump.o
OBJECTS += $(OBJDIR)/lutf8lib.o
OBJECTS += $(OBJDIR)/lvm.o
OBJECTS += $(OBJDIR)/lzio.o

# Rules
# #############################################

all: $(TARGET)
	@:

$(TARGET): $(GENERATED) $(OBJECTS) $(LDDEPS) | $(TARGETDIR)
	$(PRELINKCMDS)
	@echo Linking lua
	$(SILENT) $(LINKCMD)
	$(POSTBUILDCMDS)

$(TARGETDIR):
	@echo Creating $(TARGETDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(TARGETDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(TARGETDIR))
endif

$(OBJDIR):
	@echo Creating $(OBJDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(OBJDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(OBJDIR))
endif

clean:
	@echo Cleaning lua
ifeq (posix,$(SHELLTYPE))
	$(SILENT) rm -f  $(TARGET)
	$(SILENT) rm -rf $(GENERATED)
	$(SILENT) rm -rf $(OBJDIR)
else
	$(SILENT) if exist $(subst /,\\,$(TARGET)) del $(subst /,\\,$(TARGET))
	$(SILENT) if exist $(subst /,\\,$(GENERATED)) del /s /q $(subst /,\\,$(GENERATED))
	$(SILENT) if exist $(subst /,\\,$(OBJDIR)) rmdir /s /q $(subst /,\\,$(OBJDIR))
endif

prebuild: | $(OBJDIR)
	$(PREBUILDCMDS)

ifneq (,$(PCH))
$(OBJECTS): $(GCH) | $(PCH_PLACEHOLDER)
$(GCH): $(PCH) | prebuild
	@echo $(notdir $<)
	$(SILENT) $(CXX) -x c++-header $(ALL_CXXFLAGS) -o "$@" -MF "$(@:%.gch=%.d)" -c "$<"
$(PCH_PLACEHOLDER): $(GCH) | $(OBJDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) touch "$@"
else
	$(SILENT) echo $null >> "$@"
endif
else
$(OBJECTS): | prebuild
endif


# File Rules
# #############################################

$(OBJDIR)/lapi.o: ../../lua/src/lapi.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/lauxlib.o: ../../lua/src/lauxlib.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/lbaselib.o: ../../lua/src/lbaselib.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/lcode.o: ../../lua/src/lcode.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/lcorolib.o: ../../lua/src/lcorolib.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/lctype.o: ../../lua/src/lctype.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ldblib.o: ../../lua/src/ldblib.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ldebug.o: ../../lua/src/ldebug.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ldo.o: ../../lua/src/ldo.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ldump.o: ../../lua/src/ldump.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/lfunc.o: ../../lua/src/lfunc.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/lgc.o: ../../lua/src/lgc.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/liolib.o: ../../lua/src/liolib.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/llex.o: ../../lua/src/llex.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/lmathlib.o: ../../lua/src/lmathlib.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/lmem.o: ../../lua/src/lmem.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/loadlib.o: ../../lua/src/loadlib.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/lobject.o: ../../lua/src/lobject.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/lopcodes.o: ../../lua/src/lopcodes.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/loslib.o: ../../lua/src/loslib.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/lparser.o: ../../lua/src/lparser.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/lstate.o: ../../lua/src/lstate.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/lstring.o: ../../lua/src/lstring.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/lstrlib.o: ../../lua/src/lstrlib.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ltable.o: ../../lua/src/ltable.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ltablib.o: ../../lua/src/ltablib.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ltm.o: ../../lua/src/ltm.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/lundump.o: ../../lua/src/lundump.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/lutf8lib.o: ../../lua/src/lutf8lib.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/lvm.o: ../../lua/src/lvm.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/lzio.o: ../../lua/src/lzio.c
	@echo "$(notdir $<)"
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"

-include $(OBJECTS:%.o=%.d)
ifneq (,$(PCH))
  -include $(PCH_PLACEHOLDER).d
endif