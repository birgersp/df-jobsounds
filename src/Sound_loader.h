/**
 * @author birgersp
 * https://github.com/birgersp
 */

#ifndef SOUND_LOADER_H
#define SOUND_LOADER_H

#include "Sound_Mixer.h"
#include <cpputil/Map.hpp>

class Sound_loader
{
public:

	Sound_loader(Sound_Mixer& mixer);
	void load_wavs(String_ref dir, Vector<Sound>& sounds);

private:

	Sound_Mixer& mixer;
	Map<String, Vector<Sound>> dir_sounds;

};

#endif /* SOUND_LOADER_H */
