/**
 * @author birgersp
 * https://github.com/birgersp
 */

#include "Sound_interval_manager.h"

void Sound_interval_manager::set_sound_interval(int job_id, uint time_ms)
{
}

bool Sound_interval_manager::sound_should_play(int dwarf_id, int job_id)
{
	return false;
}

bool Sound_interval_manager::sound_should_play(int dwarf_id, int job_id, ulong timestamp)
{
	return false;
}

void Sound_interval_manager::set_event(int dwarf_id, int job_id, ulong timestamp)
{

}
