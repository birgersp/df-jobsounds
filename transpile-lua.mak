%.h: lua/jobsounds.lua
	sh transpile-to-constant.sh $< src

transpile-lua: src/jobsounds_lua_transpiled.h
