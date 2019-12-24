src/jobsounds.h: lua/jobsounds.lua
	sh create-lua-code-header.sh lua/jobsounds.lua src

lua-header-creation: src/jobounds.h
