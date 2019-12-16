#!/bin/sh

# Symlink the git pre-push hook to its destination.
if [ -h ".git/hooks/pre-push" ] ; then
  rm ".git/hooks/pre-push"
fi
ln -s "../../vendor/pfrenssen/phpcs-pre-push/pre-push" ".git/hooks/pre-push"

# Install PHPCompatibility.
./bin/phpcs --config-set installed_paths '../../drupal/coder/coder_sniffer,../../phpcompatibility/php-compatibility,../../ec-europa/qa-automation/phpcs'
