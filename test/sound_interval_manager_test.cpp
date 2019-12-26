/**
 * @author birgersp
 * https://github.com/birgersp
 */

#include <cpputil/testing.hpp>
#include "sound_interval_manager_test.h"
#include "sound_interval_manager.h"

namespace sound_interval_manager
{

void test1()
{
	register_test();
	Sound_interval_manager manager;
	manager.set_sound_interval(1, 100);
	assert_equals(true, manager.sound_should_play(0, 1, 0));
	manager.set_event(0, 1, 0); // sound plays at t=0
	assert_equals(false, manager.sound_should_play(0, 1, 50)); // sound should not play at t=50
	assert_equals(true, manager.sound_should_play(0, 1, 100)); // sound should play at t=100
}

bool testsSucceed()
{
	auto tests = {
		test1
	};
	return test_all(tests);
}

}
