PROJECT_NAME = df-jobsounds

INCLUDES := \
	-Isrc

LIBRARIES := \
	-L/mingw64/lib \
	-lmingw32 \
	-lSDL2main \
	-lSDL2 \
	-lSDL2_mixer \
	-lws2_32 \
	-lstdc++fs

CC_FLAGS += -Wpedantic -Wfatal-errors -std=c++17

include base.mak
