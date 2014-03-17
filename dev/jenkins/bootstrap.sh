#!/bin/bash

if [ ! -e "composer.phar" ]; then
    curl -sS https://getcomposer.org/installer | php
fi

php composer.phar install

if [ ! -e "build.properties" ]; then
    cp build.default.properties build.properties
    echo "[Phing] You have to fill your build.properties configuration file."
fi
