#include "core.h"
#ifdef OS_WINDOWS
#include <winsock2.h>
#endif

#include <iostream>
#include "Sound_Mixer.h"
#include <cpputil/timing.hpp>
#include <cpputil/errorhandling.hpp>
#include "TCP_Server.h"

typedef const cpputil::Exception &Exception;

int main(int argc, char **argv)
{
    try
    {
        Sound_Mixer sound_mixer;
        sound_mixer.initialize();
        Sound sound = sound_mixer.load_sound("dig.wav");
        sound_mixer.play(sound);

        TCP_Server server;
        server.bind(56730);
        print_line("waiting for connection");
        auto connection = server.accept_connection();
        print_line("yeah!");
    }
    catch (Exception e)
    {
        std::cerr << e.toString() << std::endl;
    }

    return 0;
}
