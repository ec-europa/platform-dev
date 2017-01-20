#!/bin/sh

# Symlink the git pre-push hook to its destination.
if [ -h ".git/hooks/pre-push" ] ; then
  rm ".git/hooks/pre-push"
fi
ln -s "../../vendor/pfrenssen/phpcs-pre-push/pre-push" ".git/hooks/pre-push"

# Copy PHPCompatibility coding standard over to CodeSniffer directory.
# See https://github.com/wimg/PHPCompatibility/issues/102.
rm -rf vendor/squizlabs/php_codesniffer/CodeSniffer/Standards/PHPCompatibility;
cp -r vendor/wimg/php-compatibility vendor/squizlabs/php_codesniffer/CodeSniffer/Standards/PHPCompatibility;
