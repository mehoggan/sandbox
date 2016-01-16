#!/bin/bash

aclocal && autoconf && autoreconf --no-recursive --install && \
    autoheader && libtoolize && automake --add-missing
