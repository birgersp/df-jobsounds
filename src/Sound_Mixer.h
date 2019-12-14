#ifndef SOUNDMIXER_H
#define SOUNDMIXER_H

#include <vector>
#include <SDL2/SDL_mixer.h>
#include "core.h"
#include "Sound.h"

class Sound_Mixer
{
public:
	void initialize();
	Sound load_sound(String_Ref filename);
	void play(const Sound &sound);

private:
	std::vector<Mix_Chunk *> mix_chunks;
	Mix_Chunk *get_mix_chunk(const Sound &sound);
};

#endif
