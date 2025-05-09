# GNU Make project makefile autogenerated by Premake

ifndef config
  config=release
endif

ifndef verbose
  SILENT = @
endif

.PHONY: clean prebuild prelink

ifeq ($(config),release)
  ifeq ($(origin CC), default)
    CC = clang
  endif
  ifeq ($(origin CXX), default)
    CXX = clang++
  endif
  ifeq ($(origin AR), default)
    AR = ar
  endif
  TARGETDIR = bin/release
  TARGET = $(TARGETDIR)/irrlicht.lib
  OBJDIR = obj/Release/irrlicht
  DEFINES += -DWIN32 -D_WIN32 -DWINVER=0x0601 -DNDEBUG -D_IRR_STATIC_LIB_ -DNO_IRR_COMPILE_WITH_ZIP_ENCRYPTION_ -DNO_IRR_COMPILE_WITH_BZIP2_ -DNO__IRR_COMPILE_WITH_MOUNT_ARCHIVE_LOADER_ -DNO__IRR_COMPILE_WITH_PAK_ARCHIVE_LOADER_ -DNO__IRR_COMPILE_WITH_NPK_ARCHIVE_LOADER_ -DNO__IRR_COMPILE_WITH_TAR_ARCHIVE_LOADER_ -DNO__IRR_COMPILE_WITH_WAD_ARCHIVE_LOADER_ -D_IRR_WCHAR_FILESYSTEM
  INCLUDES += -I../../irrlicht/include -I../../irrlicht/source/Irrlicht -I../../irrlicht/source/Irrlicht/zlib
  FORCE_INCLUDE +=
  ALL_CPPFLAGS += $(CPPFLAGS) -MD -MP $(DEFINES) $(INCLUDES)
  ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -O3 -g -march=native -fno-strict-aliasing -Wno-multichar -Wno-format-security
  ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -O3 -g -fno-exceptions -fno-rtti -march=native -fno-strict-aliasing -Wno-multichar -Wno-format-security
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
all: prebuild prelink $(TARGET)
	@:

endif

ifeq ($(config),debug)
  ifeq ($(origin CC), default)
    CC = clang
  endif
  ifeq ($(origin CXX), default)
    CXX = clang++
  endif
  ifeq ($(origin AR), default)
    AR = ar
  endif
  TARGETDIR = bin/debug
  TARGET = $(TARGETDIR)/irrlicht.lib
  OBJDIR = obj/Debug/irrlicht
  DEFINES += -DWIN32 -D_WIN32 -DWINVER=0x0601 -D_DEBUG -D_IRR_STATIC_LIB_ -DNO_IRR_COMPILE_WITH_ZIP_ENCRYPTION_ -DNO_IRR_COMPILE_WITH_BZIP2_ -DNO__IRR_COMPILE_WITH_MOUNT_ARCHIVE_LOADER_ -DNO__IRR_COMPILE_WITH_PAK_ARCHIVE_LOADER_ -DNO__IRR_COMPILE_WITH_NPK_ARCHIVE_LOADER_ -DNO__IRR_COMPILE_WITH_TAR_ARCHIVE_LOADER_ -DNO__IRR_COMPILE_WITH_WAD_ARCHIVE_LOADER_ -D_IRR_WCHAR_FILESYSTEM
  INCLUDES += -I../../irrlicht/include -I../../irrlicht/source/Irrlicht -I../../irrlicht/source/Irrlicht/zlib
  FORCE_INCLUDE +=
  ALL_CPPFLAGS += $(CPPFLAGS) -MD -MP $(DEFINES) $(INCLUDES)
  ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -g -fno-strict-aliasing -Wno-multichar -Wno-format-security
  ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -g -fno-exceptions -fno-rtti -fno-strict-aliasing -Wno-multichar -Wno-format-security
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
all: prebuild prelink $(TARGET)
	@:

endif

OBJECTS := \
	$(OBJDIR)/CAttributes.o \
	$(OBJDIR)/CFileList.o \
	$(OBJDIR)/CFileSystem.o \
	$(OBJDIR)/CLimitReadFile.o \
	$(OBJDIR)/CMemoryFile.o \
	$(OBJDIR)/CReadFile.o \
	$(OBJDIR)/CWriteFile.o \
	$(OBJDIR)/CXMLReader.o \
	$(OBJDIR)/CXMLWriter.o \
	$(OBJDIR)/CZipReader.o \
	$(OBJDIR)/os.o \
	$(OBJDIR)/adler32.o \
	$(OBJDIR)/crc32.o \
	$(OBJDIR)/inffast.o \
	$(OBJDIR)/inflate.o \
	$(OBJDIR)/inftrees.o \
	$(OBJDIR)/zutil.o \

RESOURCES := \

CUSTOMFILES := \

SHELLTYPE := posix
ifeq (.exe,$(findstring .exe,$(ComSpec)))
	SHELLTYPE := msdos
endif

$(TARGET): $(GCH) ${CUSTOMFILES} $(OBJECTS) $(LDDEPS) $(RESOURCES) | $(TARGETDIR)
	@echo Linking irrlicht
	$(SILENT) $(LINKCMD)
	$(POSTBUILDCMDS)

$(CUSTOMFILES): | $(OBJDIR)

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
	@echo Cleaning irrlicht
ifeq (posix,$(SHELLTYPE))
	$(SILENT) rm -f  $(TARGET)
	$(SILENT) rm -rf $(OBJDIR)
else
	$(SILENT) if exist $(subst /,\\,$(TARGET)) del $(subst /,\\,$(TARGET))
	$(SILENT) if exist $(subst /,\\,$(OBJDIR)) rmdir /s /q $(subst /,\\,$(OBJDIR))
endif

prebuild:
	$(PREBUILDCMDS)

prelink:
	$(PRELINKCMDS)

ifneq (,$(PCH))
$(OBJECTS): $(GCH) $(PCH) | $(OBJDIR)
$(GCH): $(PCH) | $(OBJDIR)
	@echo $(notdir $<)
	$(SILENT) $(CXX) -x c++-header $(ALL_CXXFLAGS) -o "$@" -MF "$(@:%.gch=%.d)" -c "$<"
else
$(OBJECTS): | $(OBJDIR)
endif

$(OBJDIR)/CAttributes.o: ../../irrlicht/source/Irrlicht/CAttributes.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/CFileList.o: ../../irrlicht/source/Irrlicht/CFileList.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/CFileSystem.o: ../../irrlicht/source/Irrlicht/CFileSystem.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/CLimitReadFile.o: ../../irrlicht/source/Irrlicht/CLimitReadFile.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/CMemoryFile.o: ../../irrlicht/source/Irrlicht/CMemoryFile.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/CReadFile.o: ../../irrlicht/source/Irrlicht/CReadFile.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/CWriteFile.o: ../../irrlicht/source/Irrlicht/CWriteFile.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/CXMLReader.o: ../../irrlicht/source/Irrlicht/CXMLReader.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/CXMLWriter.o: ../../irrlicht/source/Irrlicht/CXMLWriter.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/CZipReader.o: ../../irrlicht/source/Irrlicht/CZipReader.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/os.o: ../../irrlicht/source/Irrlicht/os.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/adler32.o: ../../irrlicht/source/Irrlicht/zlib/adler32.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/crc32.o: ../../irrlicht/source/Irrlicht/zlib/crc32.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/inffast.o: ../../irrlicht/source/Irrlicht/zlib/inffast.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/inflate.o: ../../irrlicht/source/Irrlicht/zlib/inflate.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/inftrees.o: ../../irrlicht/source/Irrlicht/zlib/inftrees.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/zutil.o: ../../irrlicht/source/Irrlicht/zlib/zutil.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"

-include $(OBJECTS:%.o=%.d)
ifneq (,$(PCH))
  -include $(OBJDIR)/$(notdir $(PCH)).d
endif