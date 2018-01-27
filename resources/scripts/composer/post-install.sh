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

# Execute the drush-m2c to regenerate the composer.json files.
for profile in multisite_drupal_standard multisite_drupal_communities; do
  cd profiles/$profile
  ../../bin/drush m2c \
    $profile.make \
    composer.json \
    --require-dev \
    --custom=modules/custom,modules/features
  cd ../..
done
