PROJECT_NAME = df-jobsounds

INCLUDES := \
	-Isrc

LIBRARIES := \
	-lmingw32 \
	-lSDL2_mixer

LD_FLAGS := `sdl2-config --libs`

CC_FLAGS += -I/mingw64/include/SDL2
CC_FLAGS += -Wpedantic -Wfatal-errors

include base.mak
