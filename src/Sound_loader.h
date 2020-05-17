/**
 * @author birgersp
 * https://github.com/birgersp
 */

#pragma once

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
