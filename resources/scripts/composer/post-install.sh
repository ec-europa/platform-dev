#!/bin/sh

# Symlink the git pre-push hook to its destination.
if [ -h ".git/hooks/pre-push" ] ; then
  rm ".git/hooks/pre-push"
fi
ln -s "../../vendor/pfrenssen/phpcs-pre-push/pre-push" ".git/hooks/pre-push"
