set -e

make -f df-jobsounds.mak -j8 test

./bin/df-jobsounds-test

make -f df-jobsounds.mak -j executable
