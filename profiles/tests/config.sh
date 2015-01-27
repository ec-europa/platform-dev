#!/bin/bash

# Saves the environment variables that are needed to run Behat tests into a
# configuration file.

# Ask for configuration if the configuration file does not yet exist.
if [ ! -f config.local ]; then
  while [ -z "$BASE_URL" ] ; do
    read -e -p "Please provide the base URL: " -i "http://localhost" BASE_URL
  done

  while [ -z "$ROOT_PATH" ] ; do
    read -e -p "Please provide the root path of the project: " -i "`pwd`" ROOT_PATH
  done
fi

# Write the configuration file.
echo "export BEHAT_PARAMS=\"{\\\"extensions\\\":{\\\"Behat\\\\\\\\MinkExtension\\\":{\\\"base_url\\\":\\\"$BASE_URL\\\"},\\\"Drupal\\\\\\\\DrupalExtension\\\":{\\\"drupal\\\":{\\\"drupal_root\\\":\\\"$ROOT_PATH\\\"}}}}\"" > config.local

# Inform the user to source the configuration file.
echo -e "\nConfiguration has been saved. It can be activated with:\n\$ source config.local"
