#!/bin/bash

# Reorganizes the folder structure according to NEXTEUROPA-2976
# https://webgate.ec.europa.eu/CITnet/jira/browse/NEXTEUROPA-2976
#
# Required packages: git, pwgen

# Populates a folder with symlinks from another folder. Only directories will be
# linked. The source folder should be relative to the destination folder. If the
# destination folder doesn't exist it will be created. All created symlinks will
# be added to the git staging area.
#
# Example: populate_symlinks destination/folder ../../source/folder
function populate_symlinks {
  mkdir -p "$1"
  cd "$1"
  find "$2" -mindepth 1 -maxdepth 1 -type d -exec ln -s "{}" . \;
  git add .
  cd -
}

# Start from the root folder.
cd "$(dirname "$0")"

# Create a temporary repository to perform the reorganization in.
TEMP_BRANCH="feature/NEXTEUROPA-2976-`pwgen -A0N1`"
git checkout -b $TEMP_BRANCH

# 1. Move all modules, libraries and themes from sites/all to profiles/common.
mkdir -p profiles/common/modules/features
git mv sites/all/modules/custom profiles/common/modules/
git mv sites/all/modules/modified/* profiles/common/modules/custom/
git mv sites/all/modules/features/custom/* profiles/common/modules/features/
git mv sites/all/libraries profiles/common/
git mv sites/all/themes profiles/common/
git commit -m "NEXTEUROPA-2976: Move projects from sites/all/ to their new home in profiles/common/."

# 2. Move common modules out of the standard profile.
git mv profiles/multisite_drupal_standard/modules/custom/* profiles/common/modules/custom/
git commit -m "NEXTEUROPA-2976: Move common modules from the standard profile to profiles/common/."

# 3. Move all features from features/custom/ to features/.
git mv profiles/multisite_drupal_communities/modules/features/custom/* profiles/multisite_drupal_communities/modules/features/
git commit -m "NEXTEUROPA-2976: Move features out of the custom/ subfolder. All features are custom."

# 4. Move all modules from modified/ to custom/.
git mv profiles/multisite_drupal_communities/modules/modified/* profiles/multisite_drupal_communities/modules/custom/
git commit -m "NEXTEUROPA-2976: Move modules from modified/ to custom/.

It is irrelevant where the code of a module is coming from. If a module is
maintained in-house it can be considered a custom module."

# 5. Populate the profiles with symlinks pointing to the common projects.
populate_symlinks profiles/multisite_drupal_communities/libraries ../../common/libraries
populate_symlinks profiles/multisite_drupal_standard/libraries ../../common/libraries
populate_symlinks profiles/multisite_drupal_communities/themes ../../common/themes
populate_symlinks profiles/multisite_drupal_standard/themes ../../common/themes
populate_symlinks profiles/multisite_drupal_communities/modules/custom ../../../common/modules/custom
populate_symlinks profiles/multisite_drupal_standard/modules/features ../../../common/modules/features
populate_symlinks profiles/multisite_drupal_communities/modules/features ../../../common/modules/features
populate_symlinks profiles/multisite_drupal_standard/modules/custom ../../../common/modules/custom
git commit -m "NEXTEUROPA-2976: Created symlinks."

# Go back to the original branch and inform the user.
git checkout -
echo "Reorganization completed in branch ${TEMP_BRANCH}."
