#!/bin/bash

autoconf && autoreconf --no-recursive --install && \
    autoheader && libtoolize && aclocal && automake --add-missing
