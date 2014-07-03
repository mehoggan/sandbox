#!/bin/bash

PROG=pathconf_sysconf_values

awk -f ./scripts/${PROG}.awk > ./scripts/${PROG}.c;
mv ./scripts/${PROG}.c ./apps/${PROG}.c
