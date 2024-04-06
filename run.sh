#!/bin/bash

cd "$(dirname "$0")"

export LD_LIBRARY_PATH=./lib:$LD_LIBRARY_PATH
./bin/pts -c config/config.toml 2>&1 > /dev/null &