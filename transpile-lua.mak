src/jobsounds.h: lua/jobsounds.lua
	sh transpile-to-constant.sh lua/jobsounds.lua src

transpile-lua: src/jobounds.h
