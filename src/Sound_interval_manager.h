/**
 * @author birgersp
 * https://github.com/birgersp
 */

#ifndef SOUND_INTERVAL_MANAGER_H
#define SOUND_INTERVAL_MANAGER_H

#include <cpputil/Map.hpp>
#include "core.h"

struct Sound_event
{
	int job_id;
	ulong timestamp;
};

class Sound_interval_manager
{
public:

	void set_sound_interval(int job_id, uint time_ms);
	bool sound_should_play(int dwarf_id, int job_id);
	bool sound_should_play(int dwarf_id, int job_id, ulong timestamp);
	void set_event(int dwarf_id, int job_id, ulong timestamp);

private:

	cpputil::Map<int, Sound_event> dwarf_sound_events;

};

#endif /* SOUND_INTERVAL_MANAGER_H */
