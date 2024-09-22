SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
export CMAKE_PREFIX_PATH="`cd $SCRIPT_DIR 1>/dev/null 2>&1; pwd`:$CMAKE_PREFIX_PATH"
