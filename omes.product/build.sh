#!/usr/bin/env bash

EOSCPP=/usr/local/bin/eosiocpp

SRC=omes.product.cpp

contract=$(basename ${SRC} .cpp)

${EOSCPP} -o ${contract}.wast src/${SRC}
#${EOSCPP} -g ${contract}.abi src/${SRC}
