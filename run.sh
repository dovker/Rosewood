INPUT=${1?Error: no input filename given}
CONFIG=${2:-debug}
PLATFORM=${3:-macosx}
cd bin/$CONFIG-$PLATFORM-x86_64/$INPUT
./$INPUT