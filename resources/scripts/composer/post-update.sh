#!/bin/sh

# Copy PHPCompatibility coding standard over to CodeSniffer directory.
# See https://github.com/wimg/PHPCompatibility/issues/102.
rm -rf vendor/squizlabs/php_codesniffer/CodeSniffer/Standards/PHPCompatibility;
cp -rd vendor/wimg/php-compatibility vendor/squizlabs/php_codesniffer/CodeSniffer/Standards/PHPCompatibility;
