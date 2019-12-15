#include <cpputil/errorhandling.hpp>
#include <SDL2/SDL.h>

#include "Sound_Mixer.h"

void Sound_Mixer::initialize()
{
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
		throw functionException("Could not initialize SDL audio");

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
		throw functionException("Could not initialize SDL audio mixer");

	Mix_AllocateChannels(32);
}

Sound Sound_Mixer::load_sound(String_Ref filename)
{
	Mix_Chunk *chunk = Mix_LoadWAV(filename.c_str());
	if (chunk == NULL)
		throw functionException("Could not open sound file \"" + filename + "\": " + Mix_GetError());
	Sound sound;
	sound.id = mix_chunks.size();
	mix_chunks.push_back(chunk);
	return sound;
}

void Sound_Mixer::play(const Sound &sound)
{
	Mix_Chunk *chunk = get_mix_chunk(sound);
	int channel = Mix_PlayChannel(-1, chunk, 0);
	if (channel == -1)
		throw functionException("Error playing sound " + std::to_string(sound.id) + ": " + Mix_GetError());
}

Mix_Chunk *Sound_Mixer::get_mix_chunk(const Sound &sound)
{
	Mix_Chunk *chunk = mix_chunks.at(sound.id);
	return chunk;
}
