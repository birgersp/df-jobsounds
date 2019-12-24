/**
 * @author birgersp
 * https://github.com/birgersp
 */

#include "Sound_interval_manager.h"
#include "util.h"

void Sound_interval_manager::set_sound_interval(int job_id, uint time_ms)
{
	sound_min_time.put(job_id, time_ms);
}

bool Sound_interval_manager::sound_should_play(int unit_id, int job_id)
{
	ulong current_time = get_millisec();
	return sound_should_play(unit_id, job_id, current_time);
}

bool Sound_interval_manager::sound_should_play(int unit_id, int job_id, ulong timestamp)
{
	uint* min_time_ptr = sound_min_time.get(job_id);
	if (min_time_ptr == nullptr)
		return true;
	uint min_time = *min_time_ptr;
	Sound_event* event = unit_sound_events.get(unit_id);
	if (event == nullptr)
		return true;
	ulong time_difference = timestamp - event->timestamp;
	if (time_difference >= min_time)
		return true;
	return false;
}

void Sound_interval_manager::set_event(int unit_id, int job_id, ulong timestamp)
{
	Sound_event event;
	event.job_id = job_id;
	event.timestamp = timestamp;
	unit_sound_events.put(unit_id, event);
}
