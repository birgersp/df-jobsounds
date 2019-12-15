#include <iostream>
#include "Sound_Mixer.h"
#include <cpputil/timing.hpp>
#include <cpputil/errorhandling.hpp>

typedef const cpputil::Exception& Exception;

int main(int argc, char **argv)
{
    try {
        Sound_Mixer sound_mixer;
        sound_mixer.initialize();
        Sound sound = sound_mixer.load_sound("dig.wav");
        sound_mixer.play(sound);
    } catch (Exception e) {
        std::cerr << e.toString() << std::endl;
    }
    std::cout << "Hello world!" << std::endl;
    cpputil::sleepMS(2000);
    return 0;
}
