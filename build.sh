INPUT=${1:-TestGame}
CONFIG=${2:-debug}
PLATFORM=${3:-macosx}
make config=$CONFIG
./run.sh $INPUT $CONFIG $PLATFORM
