#******************************************************************************
#
#   ALLGO EMBEDDED SYSTEMS CONFIDENTIAL PROPRIETARY
#
#   (C) 2015-16 ALLGO EMBEDDED SYSTEMS INDIA PVT. LTD.
#
#   FILENAME       - Makefile
#
#   COMPILER       - <gcc 4.6.3 or similar>
#
#******************************************************************************
#   CHANGE HISTORY
#   ---------------------------------------------------------------------------
#   DATE           REVISION    AUTHOR           COMMENTS
#   ---------------------------------------------------------------------------
#   26/09/2017     1.0         Dipankar Saha    Intial version.
#   28/09/2017     1.1         Kartik Inani     Seperated out compilation of
#                                               ALSA player, based on PLAYER_TYPE
#                                               environment variable
#******************************************************************************
#  File Description
#  ---------------------
#  This Makefile contains the compilation rule, clean rule and install rule
#  for the audio player.
#
#******************************************************************************

##########################################################################
# ARCHITECTURE
##########################################################################
#ARCH=i386
#ARCH=arm

##########################################################################
# DEFINES
##########################################################################
# linux os platform
CROSS_COMPILE = $(GCC_TOOLCHAIN_PATH)
CXX = $(CROSS_COMPILE)g++
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)g++
AR = $(CROSS_COMPILE)ar

##########################################################################
# DIRECTORIES
##########################################################################
OBJ_DIR=./obj
LIB_DIR=./lib
SRC_DIR=./src

##########################################################################
# INCLUDES AND FLAGS
##########################################################################

C_FLAGS += -W -Wall -fPIC $(DEFS)
ifeq ($(BUILDTYPE), debug)
C_FLAGS += -g
else ifeq ($(BUILDTYPE), debug_coverage)
C_FLAGS += -ftest-coverage -fprofile-arcs -g
else
C_FLAGS += -O2
endif

C_INCLUDES += -I./inc

# This interface header path must contain all the interface headers while compiling
# this module separately. In normal compilation this path is not required.
C_INCLUDES += -I./interface_header/

C_INCLUDES += -I$(TARGET_ROOTFS)/usr/include

AAP_ADPLAY_LIB_OBJECTS += \
	$(OBJ_DIR)/alsa_audio_player.o

AAP_ADPLAY_LIB_OBJECTS += \
	$(OBJ_DIR)/aap_plat_aplayer_interface.o

AAP_ADPLAYER_LIB = libaap_adplayer.so

all: init $(AAP_ADPLAYER_LIB)

init:
	@echo "AAP_REPO_PATH is set to = $(AAP_REPO_PATH)"
	@test -d $(OBJ_DIR) || mkdir $(OBJ_DIR) 2>/dev/null
	@test -d $(LIB_DIR) || mkdir $(LIB_DIR) 2>/dev/null

$(AAP_ADPLAYER_LIB) : $(AAP_ADPLAY_LIB_OBJECTS)
	$(CXX) $(C_FLAGS) -shared -Wl,-export-dynamic -o $@ $(AAP_ADPLAY_LIB_OBJECTS) -L$(OBJ_DIR)
ifneq ($(AAP_REPO_PATH), )
	-cp $(AAP_ADPLAYER_LIB) $(AAP_REPO_PATH)/vendor/allgo/build/lib/
endif
	mv $(AAP_ADPLAYER_LIB) $(LIB_DIR)/

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CXX) $(C_FLAGS) $(C_INCLUDES) -c  $^ -o $@

clean:
	rm -f $(OBJ_DIR)/*.*
	rm -rf $(OBJ_DIR)
	rm -rf $(LIB_DIR)/*
	rm -rf $(LIB_DIR)
