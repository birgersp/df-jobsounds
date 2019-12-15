PROJECT_NAME = df-jobsounds

INCLUDES := \
	-Isrc

LIBRARIES := \
	-L/mingw64/lib \
	-lmingw32 \
	-lSDL2main \
	-lSDL2 \
	-lSDL2_mixer

CC_FLAGS += -Wpedantic -Wfatal-errors

include base.mak
