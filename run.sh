INPUT=${1?Error: no input filename given}
CONFIG=${2:-debug}
cd bin/$CONFIG-macosx-x86_64/$INPUT
./$INPUT