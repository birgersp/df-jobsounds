/**
 * @author birgersp
 * https://github.com/birgersp
 */

#ifndef SOUNDMIXER_H
#define SOUNDMIXER_H

#include "core.h"
#include "Sound.h"
#include <SDL2/SDL_mixer.h>

class Sound_Mixer
{
public:
	void initialize();
	Sound load_sound(String_ref filename);
	void play(const Sound& sound);

private:
	Vector<Mix_Chunk *> mix_chunks;
	Mix_Chunk *get_mix_chunk(const Sound& sound);
};

#endif
