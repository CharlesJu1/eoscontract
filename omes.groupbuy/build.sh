#!/usr/bin/env bash

EOSCPP=/usr/local/bin/eosiocpp

SRC=omes.groupbuy.cpp

contract=$(basename ${SRC} .cpp)

${EOSCPP} -o ${contract}.wast src/${SRC}
#${EOSCPP} -g ${contract}.abi src/${SRC}
