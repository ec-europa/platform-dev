The "wiki" feature is a collaborative communication tool for users desiring to contribute to its content by adding, modifying or deleting content. This makes the content collaborative as multiple users can work on a same wiki page.

Table of content:
=================
- [Important](#important)
- [Installation](#installation)
- [Usage](#usage)
- [Disabling](#disabling)

# Important

Wiki uses 3 modules to work. Wiki_core is not designed to work alone, but with one of the 2 other sub-modules depending on the profile configuration used in the site.
- For "multisite_drupal_standard" configuration enable the modules wiki_core and wiki_standard.
- For "multisite_drupal_communities" configuration enable the modules wiki_core and wiki_og.

[Go to top](#table-of-content)

# Installation

There are 2 ways to activate the feature:
1. Like any Drupal modules via the "Modules" admin page or with the Drush command.
2. Like a "Feature set" through the Feature set admin page (path: admin/structure/feature-set_en).<br />
Then, Enable the "wiki" feature under "Communication" section, and click on the "Validate" button.

[Go to top](#table-of-content)

# Usage

## Standard configuration
### Wikis list
Wiki feature adds a "Wikis" link in the main menu with the Wikis list.

### Create a Wiki page
Every authenticated user can propose a wiki page. Wiki page is then published after an authorized user has approved it.
Create a wiki:
1. Log in.
2. Select "wiki" among the "Create content" options
3. Fill in the form the form, select the desired option in moderation state and press save.

## Communities configuration:
Besides the usage explained in the Standard configuration, in communities, has the following added functionalities:

### Community Wikis
A Member can see private Wikis according to his membership by going to the community page. The community page will filter the Wikis of this community for its members.

### Public Wikis
A User can see featured public Wikis on the homepage
A User can go to the public Wikis section thanks to the "Wikis" item in the main menu and see the list of public Wikis but not the private, that are only for the community members.

[Go to top](#table-of-content)

# Disabling

As for the installation, there are 2 ways for disabling and uninstalling the feature:
1. Like any Drupal modules via the "Modules" admin page or with the Drush command.
2. Like a "Feature set" through the Feature set admin page (path: admin/structure/feature-set_en).

[Go to top](#table-of-content)
