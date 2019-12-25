set -e

make -f transpile-lua.mak
make -f df-jobsounds.mak -j8 test

./bin/df-jobsounds-test

make -f df-jobsounds.mak -j executable
