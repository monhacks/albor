# GBA rom header
TITLE       := POKEMON EMER
GAME_CODE   := BPEE
MAKER_CODE  := 01
REVISION    := 0
KEEP_TEMPS  ?= 0

# `File name`.gba
FILE_NAME := pokeemerald
BUILD_DIR := build

# Enables -fanalyzer C flag to analyze in depth potential UBs
ANALYZE      ?= 0
# Count unused warnings as errors. Used by RH-Hideout's repo
UNUSED_ERROR ?= 0
# Adds -Og and -g flags, which optimize the build for debugging and include debug info respectively
DEBUG        ?= 0

ifeq (debug,$(MAKECMDGOALS))
  DEBUG := 1
endif

# Default make rule
all: rom

# Toolchain selection
TOOLCHAIN := $(DEVKITARM)
# don't use dkP's base_tools anymore
# because the redefinition of $(CC) conflicts
# with when we want to use $(CC) to preprocess files
# thus, manually create the variables for the bin
# files, or use arm-none-eabi binaries on the system
# if dkP is not installed on this system
ifneq (,$(TOOLCHAIN))
  ifneq ($(wildcard $(TOOLCHAIN)/bin),)
    export PATH := $(TOOLCHAIN)/bin:$(PATH)
  endif
endif

PREFIX := arm-none-eabi-
OBJCOPY := $(PREFIX)objcopy
OBJDUMP := $(PREFIX)objdump
AS := $(PREFIX)as
LD := $(PREFIX)ld

EXE :=
ifeq ($(OS),Windows_NT)
  EXE := .exe
endif

CPP := $(PREFIX)cpp

ROM_NAME := $(FILE_NAME).gba
OBJ_DIR_NAME := $(BUILD_DIR)/modern
OBJ_DIR_NAME_DEBUG := $(BUILD_DIR)/modern-debug

ELF_NAME := $(ROM_NAME:.gba=.elf)
MAP_NAME := $(ROM_NAME:.gba=.map)

# Pick our active variables
ROM := $(ROM_NAME)
OBJ_DIR := $(OBJ_DIR_NAME)
ifeq ($(DEBUG),1)
  OBJ_DIR := $(OBJ_DIR_NAME_DEBUG)
endif
ELF := $(ROM:.gba=.elf)
MAP := $(ROM:.gba=.map)
SYM := $(ROM:.gba=.sym)

# Commonly used directories
C_SUBDIR = src
ASM_SUBDIR = asm
DATA_SRC_SUBDIR = src/data
DATA_ASM_SUBDIR = data
SONG_SUBDIR = sound/songs
MID_SUBDIR = sound/songs/midi

C_BUILDDIR = $(OBJ_DIR)/$(C_SUBDIR)
ASM_BUILDDIR = $(OBJ_DIR)/$(ASM_SUBDIR)
DATA_ASM_BUILDDIR = $(OBJ_DIR)/$(DATA_ASM_SUBDIR)
SONG_BUILDDIR = $(OBJ_DIR)/$(SONG_SUBDIR)
MID_BUILDDIR = $(OBJ_DIR)/$(MID_SUBDIR)

SHELL := bash -o pipefail

# Set flags for tools
ASFLAGS := -mcpu=arm7tdmi --defsym MODERN=1

INCLUDE_DIRS := include
INCLUDE_CPP_ARGS := $(INCLUDE_DIRS:%=-iquote %)
INCLUDE_SCANINC_ARGS := $(INCLUDE_DIRS:%=-I %)

ifeq ($(DEBUG),1)
O_LEVEL ?= g
else
O_LEVEL ?= 2
endif
CPPFLAGS := $(INCLUDE_CPP_ARGS) -Wno-trigraphs -DMODERN=1
ARMCC := $(PREFIX)gcc
PATH_ARMCC := PATH="$(PATH)" $(ARMCC)
CC1 := $(shell $(PATH_ARMCC) --print-prog-name=cc1) -quiet
override CFLAGS += -mthumb -mthumb-interwork -O$(O_LEVEL) -mabi=apcs-gnu -mtune=arm7tdmi -march=armv4t -fno-toplevel-reorder -Wno-pointer-to-int-cast -std=gnu17 -Werror -Wall -Wno-strict-aliasing -Wno-attribute-alias -Woverride-init
ifeq ($(ANALYZE),1)
  override CFLAGS += -fanalyzer
endif
# Only throw an error for unused elements if its RH-Hideout's repo
ifeq ($(UNUSED_ERROR),0)
  ifneq ($(GITHUB_REPOSITORY_OWNER),rh-hideout)
    override CFLAGS += -Wno-error=unused-variable -Wno-error=unused-const-variable -Wno-error=unused-parameter -Wno-error=unused-function -Wno-error=unused-but-set-parameter -Wno-error=unused-but-set-variable -Wno-error=unused-value -Wno-error=unused-local-typedefs
  endif
endif
LIBPATH := -L "$(dir $(shell $(PATH_ARMCC) -mthumb -print-file-name=libgcc.a))" -L "$(dir $(shell $(PATH_ARMCC) -mthumb -print-file-name=libnosys.a))" -L "$(dir $(shell $(PATH_ARMCC) -mthumb -print-file-name=libc.a))"
LIB := $(LIBPATH) -lc -lnosys -lgcc -L../../libagbsyscall -lagbsyscall
# Enable debug info if set
ifeq ($(DINFO),1)
  override CFLAGS += -g
else
  ifeq ($(DEBUG),1)
    override CFLAGS += -g
  endif
endif

ifeq ($(NOOPT),1)
override CFLAGS := $(filter-out -O1 -Og -O2,$(CFLAGS))
override CFLAGS += -O0
endif

# Variable filled out in other make files
AUTO_GEN_TARGETS :=
include make_tools.mk
# Tool executables
GFX          := $(TOOLS_DIR)/gbagfx/gbagfx$(EXE)
AIF          := $(TOOLS_DIR)/aif2pcm/aif2pcm$(EXE)
MID          := $(TOOLS_DIR)/mid2agb/mid2agb$(EXE)
SCANINC      := $(TOOLS_DIR)/scaninc/scaninc$(EXE)
PREPROC      := $(TOOLS_DIR)/preproc/preproc$(EXE)
RAMSCRGEN    := $(TOOLS_DIR)/ramscrgen/ramscrgen$(EXE)
FIX          := $(TOOLS_DIR)/gbafix/gbafix$(EXE)
MAPJSON      := $(TOOLS_DIR)/mapjson/mapjson$(EXE)
JSONPROC     := $(TOOLS_DIR)/jsonproc/jsonproc$(EXE)
TRAINERPROC  := $(TOOLS_DIR)/trainerproc/trainerproc$(EXE)
PATCHELF     := $(TOOLS_DIR)/patchelf/patchelf$(EXE)

PERL := perl
SHA1 := $(shell { command -v sha1sum || command -v shasum; } 2>/dev/null) -c

MAKEFLAGS += --no-print-directory

# Clear the default suffixes
.SUFFIXES:
# Don't delete intermediate files
.SECONDARY:
# Delete files that weren't built properly
.DELETE_ON_ERROR:

RULES_NO_SCAN += libagbsyscall clean clean-assets tidy tidymodern generated clean-generated
.PHONY: all rom modern check debug
.PHONY: $(RULES_NO_SCAN)

infoshell = $(foreach line, $(shell $1 | sed "s/ /__SPACE__/g"), $(info $(subst __SPACE__, ,$(line))))

# Check if we need to scan dependencies based on the chosen rule OR user preference
NODEP ?= 0
# Check if we need to pre-build tools and generate assets based on the chosen rule.
SETUP_PREREQS ?= 1
# Disable dependency scanning for rules that don't need it.
ifneq (,$(MAKECMDGOALS))
  ifeq (,$(filter-out $(RULES_NO_SCAN),$(MAKECMDGOALS)))
    NODEP := 1
    SETUP_PREREQS := 0
  endif
endif

.SHELLSTATUS ?= 0

ifeq ($(SETUP_PREREQS),1)
  # If set on: Default target or a rule requiring a scan
  # Forcibly execute `make tools` since we need them for what we are doing.
  $(foreach line, $(shell $(MAKE) -f make_tools.mk | sed "s/ /__SPACE__/g"), $(info $(subst __SPACE__, ,$(line))))
  ifneq ($(.SHELLSTATUS),0)
    $(error Errors occurred while building tools. See error messages above for more details)
  endif
  # Oh and also generate mapjson sources before we use `SCANINC`.
  $(foreach line, $(shell $(MAKE) generated | sed "s/ /__SPACE__/g"), $(info $(subst __SPACE__, ,$(line))))
  ifneq ($(.SHELLSTATUS),0)
    $(error Errors occurred while generating map-related sources. See error messages above for more details)
  endif
endif

# Collect sources
C_SRCS_IN := $(wildcard $(C_SUBDIR)/*.c $(C_SUBDIR)/*/*.c $(C_SUBDIR)/*/*/*.c)
C_SRCS := $(foreach src,$(C_SRCS_IN),$(if $(findstring .inc.c,$(src)),,$(src)))
C_OBJS := $(patsubst $(C_SUBDIR)/%.c,$(C_BUILDDIR)/%.o,$(C_SRCS))

C_ASM_SRCS := $(wildcard $(C_SUBDIR)/*.s $(C_SUBDIR)/*/*.s $(C_SUBDIR)/*/*/*.s)
C_ASM_OBJS := $(patsubst $(C_SUBDIR)/%.s,$(C_BUILDDIR)/%.o,$(C_ASM_SRCS))

ASM_SRCS := $(wildcard $(ASM_SUBDIR)/*.s)
ASM_OBJS := $(patsubst $(ASM_SUBDIR)/%.s,$(ASM_BUILDDIR)/%.o,$(ASM_SRCS))

# get all the data/*.s files EXCEPT the ones with specific rules
REGULAR_DATA_ASM_SRCS := $(filter-out $(DATA_ASM_SUBDIR)/maps.s $(DATA_ASM_SUBDIR)/map_events.s, $(wildcard $(DATA_ASM_SUBDIR)/*.s))

DATA_ASM_SRCS := $(wildcard $(DATA_ASM_SUBDIR)/*.s)
DATA_ASM_OBJS := $(patsubst $(DATA_ASM_SUBDIR)/%.s,$(DATA_ASM_BUILDDIR)/%.o,$(DATA_ASM_SRCS))

SONG_SRCS := $(wildcard $(SONG_SUBDIR)/*.s)
SONG_OBJS := $(patsubst $(SONG_SUBDIR)/%.s,$(SONG_BUILDDIR)/%.o,$(SONG_SRCS))

MID_SRCS := $(wildcard $(MID_SUBDIR)/*.mid)
MID_OBJS := $(patsubst $(MID_SUBDIR)/%.mid,$(MID_BUILDDIR)/%.o,$(MID_SRCS))

OBJS     := $(C_OBJS) $(C_ASM_OBJS) $(ASM_OBJS) $(DATA_ASM_OBJS) $(SONG_OBJS) $(MID_OBJS)
OBJS_REL := $(patsubst $(OBJ_DIR)/%,%,$(OBJS))

SUBDIRS  := $(sort $(dir $(OBJS)))
$(shell mkdir -p $(SUBDIRS))

# Pretend rules that are actually flags defer to `make all`
modern: all
debug: all

# Other rules
rom: $(ROM)

syms: $(SYM)

clean: tidy clean-tools clean-check-tools clean-generated clean-assets
	@$(MAKE) clean -C libagbsyscall

clean-assets:
	rm -f $(MID_SUBDIR)/*.s
	rm -f $(DATA_ASM_SUBDIR)/layouts/layouts.inc $(DATA_ASM_SUBDIR)/layouts/layouts_table.inc
	rm -f $(DATA_ASM_SUBDIR)/maps/connections.inc $(DATA_ASM_SUBDIR)/maps/events.inc $(DATA_ASM_SUBDIR)/maps/groups.inc $(DATA_ASM_SUBDIR)/maps/headers.inc $(DATA_SRC_SUBDIR)/map_group_count.h
	find sound -iname '*.bin' -exec rm {} +
	find . \( -iname '*.1bpp' -o -iname '*.4bpp' -o -iname '*.8bpp' -o -iname '*.gbapal' -o -iname '*.lz' -o -iname '*.rl' -o -iname '*.latfont' -o -iname '*.hwjpnfont' -o -iname '*.fwjpnfont' \) -exec rm {} +
	find $(DATA_ASM_SUBDIR)/maps \( -iname 'connections.inc' -o -iname 'events.inc' -o -iname 'header.inc' \) -exec rm {} +

tidy: tidymodern tidydebug

tidymodern:
	rm -f $(ROM_NAME) $(ELF_NAME) $(MAP_NAME)
	rm -rf $(OBJ_DIR_NAME)

tidydebug:
	rm -rf $(DEBUG_OBJ_DIR_NAME)

# Other rules
include graphics_file_rules.mk
include map_data_rules.mk
include spritesheet_rules.mk
include json_data_rules.mk
include audio_rules.mk

# NOTE: Tools must have been built prior (FIXME)
# so you can't really call this rule directly
generated: $(AUTO_GEN_TARGETS)

%.s:   ;
%.png: ;
%.pal: ;
%.aif: ;

%.1bpp:   %.png  ; $(GFX) $< $@
%.4bpp:   %.png  ; $(GFX) $< $@
%.8bpp:   %.png  ; $(GFX) $< $@
%.gbapal: %.pal  ; $(GFX) $< $@
%.gbapal: %.png  ; $(GFX) $< $@
%.lz:     %      ; $(GFX) $< $@
%.rl:     %      ; $(GFX) $< $@

clean-generated:
	-rm -f $(AUTO_GEN_TARGETS)

COMPETITIVE_PARTY_SYNTAX := $(shell PATH="$(PATH)"; echo 'COMPETITIVE_PARTY_SYNTAX' | $(CPP) $(CPPFLAGS) -imacros include/gba/defines.h -imacros include/config/general.h | tail -n1)
ifeq ($(COMPETITIVE_PARTY_SYNTAX),1)
%.h: %.party ; $(CPP) $(CPPFLAGS) -traditional-cpp - < $< | $(TRAINERPROC) -o $@ -i $< -
endif

$(C_BUILDDIR)/pokedex.o: CFLAGS := -mthumb -mthumb-interwork -O2 -mabi=apcs-gnu -mtune=arm7tdmi -march=armv4t -Wno-pointer-to-int-cast -std=gnu17 -Werror -Wall -Wno-strict-aliasing -Wno-attribute-alias -Woverride-init
# Annoyingly we can't turn this on just for src/data/trainers.h
$(C_BUILDDIR)/data.o: CFLAGS += -fno-show-column -fno-diagnostics-show-caret

# Dependency rules (for the *.c & *.s sources to .o files)
# Have to be explicit or else missing files won't be reported.

# As a side effect, they're evaluated immediately instead of when the rule is invoked.
# It doesn't look like $(shell) can be deferred so there might not be a better way (Icedude_907: there is soon).

$(C_BUILDDIR)/%.o: $(C_SUBDIR)/%.c
ifneq ($(KEEP_TEMPS),1)
	@echo "$(CC1) <flags> -o $@ $<"
	@$(CPP) $(CPPFLAGS) $< | $(PREPROC) -i $< charmap.txt | $(CC1) $(CFLAGS) -o - - | cat - <(echo -e ".text\n\t.align\t2, 0") | $(AS) $(ASFLAGS) -o $@ -
else
	@$(CPP) $(CPPFLAGS) $< -o $*.i
	@$(PREPROC) $*.i charmap.txt | $(CC1) $(CFLAGS) -o $*.s
	@echo -e ".text\n\t.align\t2, 0\n" >> $*.s
	$(AS) $(ASFLAGS) -o $@ $*.s
endif

$(C_BUILDDIR)/%.d: $(C_SUBDIR)/%.c
	$(SCANINC) -M $@ $(INCLUDE_SCANINC_ARGS) -I "" $<

ifneq ($(NODEP),1)
-include $(addprefix $(OBJ_DIR)/,$(C_SRCS:.c=.d))
endif

$(ASM_BUILDDIR)/%.o: $(ASM_SUBDIR)/%.s
	$(AS) $(ASFLAGS) -o $@ $<

$(ASM_BUILDDIR)/%.d: $(ASM_SUBDIR)/%.s
	$(SCANINC) -M $@ $(INCLUDE_SCANINC_ARGS) -I "" $<

ifneq ($(NODEP),1)
-include $(addprefix $(OBJ_DIR)/,$(ASM_SRCS:.s=.d))
endif

$(C_BUILDDIR)/%.o: $(C_SUBDIR)/%.s
	$(PREPROC) $< charmap.txt | $(CPP) $(INCLUDE_SCANINC_ARGS) - | $(PREPROC) -ie $< charmap.txt | $(AS) $(ASFLAGS) -o $@

$(C_BUILDDIR)/%.d: $(C_SUBDIR)/%.s
	$(SCANINC) -M $@ $(INCLUDE_SCANINC_ARGS) -I "" $<

ifneq ($(NODEP),1)
-include $(addprefix $(OBJ_DIR)/,$(C_ASM_SRCS:.s=.d))
endif

$(DATA_ASM_BUILDDIR)/%.o: $(DATA_ASM_SUBDIR)/%.s
	$(PREPROC) $< charmap.txt | $(CPP) $(INCLUDE_SCANINC_ARGS) - | $(PREPROC) -ie $< charmap.txt | $(AS) $(ASFLAGS) -o $@

$(DATA_ASM_BUILDDIR)/%.d: $(DATA_ASM_SUBDIR)/%.s
	$(SCANINC) -M $@ $(INCLUDE_SCANINC_ARGS) -I "" $<

ifneq ($(NODEP),1)
-include $(addprefix $(OBJ_DIR)/,$(REGULAR_DATA_ASM_SRCS:.s=.d))
endif

$(OBJ_DIR)/sym_bss.ld: sym_bss.txt
	$(RAMSCRGEN) .bss $< ENGLISH > $@

$(OBJ_DIR)/sym_common.ld: sym_common.txt $(C_OBJS) $(wildcard common_syms/*.txt)
	$(RAMSCRGEN) COMMON $< ENGLISH -c $(C_BUILDDIR),common_syms > $@

$(OBJ_DIR)/sym_ewram.ld: sym_ewram.txt
	$(RAMSCRGEN) ewram_data $< ENGLISH > $@

# Linker script
LD_SCRIPT := ld_script_modern.ld
LD_SCRIPT_DEPS :=

# Final rules

libagbsyscall:
	@$(MAKE) -C libagbsyscall TOOLCHAIN=$(TOOLCHAIN) MODERN=1

# Elf from object files
$(ELF): $(LD_SCRIPT) $(LD_SCRIPT_DEPS) $(OBJS) libagbsyscall
	@cd $(OBJ_DIR) && $(LD) $(LDFLAGS) -T ../../$< --print-memory-usage -o ../../$@ $(OBJS_REL) $(LIB) | cat
	@echo "cd $(OBJ_DIR) && $(LD) $(LDFLAGS) -T ../../$< --print-memory-usage -o ../../$@ <objs> <libs> | cat"
	$(FIX) $@ -t"$(TITLE)" -c$(GAME_CODE) -m$(MAKER_CODE) -r$(REVISION) --silent

# Builds the rom from the elf file
$(ROM): $(ELF)
	$(OBJCOPY) -O binary $< $@
	$(FIX) $@ -p --silent

# Symbol file (`make syms`)
$(SYM): $(ELF)
	$(OBJDUMP) -t $< | sort -u | grep -E "^0[2389]" | $(PERL) -p -e 's/^(\w{8}) (\w).{6} \S+\t(\w{8}) (\S+)$$/\1 \2 \3 \4/g' > $@
