PROJECT_NAME = df-jobsounds

INCLUDES := \
	-Isrc

LIBRARIES := \
	-lSDL2_mixer

LD_FLAGS += `sdl2-config --libs`

CC_FLAGS += -Wpedantic -Wfatal-errors

include base.mak
