#!/bin/bash

script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

pushd ${script_dir} >/dev/null
export MEGAGON_ROOT_DIR=$(pwd)
popd >/dev/null

function run_megagon()
{
    pushd ${MEGAGON_ROOT_DIR}/ >/dev/null
    rm -rf ./build
    mkdir build
    pushd build >/dev/null
    cmake ../
    make && ./megagon
    popd >/dev/null

    popd >/dev/null
}
