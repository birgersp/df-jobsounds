PROJECT_NAME = df-jobsounds

INCLUDES := \
	-Isrc

LIBRARIES :=

CC_FLAGS += -Wpedantic -Wfatal-errors

include base.mak
