#!/bin/bash

if [ ! -e "composer.phar" ]; then
    curl -sS https://getcomposer.org/installer | php
fi

php composer.phar install

if [ ! -e "build.properties" ]; then
    cp ../build.properties build.properties
    echo "You may have to fill build.properties to override build.default.properties."
fi