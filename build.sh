INPUT=${1:-TestGame}
CONFIG=${2:-debug}
make config=$CONFIG
./run.sh $INPUT $CONFIG
