#!/bin/bash


if [ ! -e "composer.phar" ]; then
    curl -sS https://getcomposer.org/installer | php
fi

php composer.phar install

if [ ! -e "behat.yml" ]; then
    cp behat.yml.dist behat.yml
    echo "[Behat] You have to fill your behat.yml configuration file."
    exit 1
fi

if [ ! -e "build.properties" ]; then
    cp build.default.properties build.properties
    echo "[Phing] You have to fill your build.properties configuration file."
    exit 1
fi
