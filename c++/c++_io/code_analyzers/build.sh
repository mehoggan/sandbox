#!/bin/bash

echo -ne "/*--*/" >> main.cpp; make
sed -e 's/\/\*--\*\///g' main.cpp > tmp
mv tmp main.cpp
rm -f ./tmp
