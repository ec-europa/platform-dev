#!/bin/bash

if [ ! -e "composer.phar" ]; then
    curl -sS https://getcomposer.org/installer | php
fi

php composer.phar install