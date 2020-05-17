/**
 * @author birgersp
 * https://github.com/birgersp
 */

#include <cpputil/string.hpp>

#include "Sound_loader.h"
#include "util.h"

Sound_loader::Sound_loader(Sound_Mixer& mixer) :
mixer(mixer)
{
}

void Sound_loader::load_wavs(String_ref dir, Vector<Sound>& sounds)
{
	Vector<Sound>* existing_sounds = dir_sounds.get(dir);
	if (existing_sounds != nullptr)
	{
		sounds = *existing_sounds;
		return;
	}

	Vector<String> filenames = get_filenames_in_dir(dir);
	for (String_ref filename : filenames)
	{
		String extension = filename;
		replace_in_str(".*?\\.", "", extension);
		to_lower_case(extension);
		if (extension != "wav")
			continue;

		print_line(" " + filename);
		Sound sound = mixer.load_sound(filename);
		sounds.push_back(sound);
	}
	dir_sounds.put(dir, sounds);
}
