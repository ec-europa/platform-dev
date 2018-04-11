The "News" feature provides a link in the main menu to the list of news, and allows filtering news according to the community in "multisite_drupal_communities" configuration.

Table of content:
=================
- [Important](#important)
- [Installation](#installation)
- [Usage](#usage)

# Important

News uses 3 modules to work. "news_core" is not designed to work alone, but with one of the 2 other sub-modules depending on the profile configuration used in the site.

 [Go to top](#table-of-content)


# Installation

For "multisite_drupal_standard" configuration enable the modules "news_core" and "news_standard".
For "multisite_drupal_communities" configuration enable the modules "news_core" and "news_og".

[Go to top](#table-of-content)

# Usage

## Standard configuration
### News list
- News feature adds a "News" link in the main menu with the News list.

## Communities configuration:

### Propose News for publication
- A Member can create a news as any other content. When the news is saved, it will remain ad "Draft" or "Needs Review".<br />
To request approval from community manager the news must be saved with the moderation state of "Needs Review".

### Community News
- A Member can see private news according to his membership by going to the community page.<br />
The community page will filter the news of this community for its members.

### Public News
- A User can see featured public news on the homepage
- A User can go to the public news section thanks to the "News" item in the main menu and see the list of public news but not the private, that are only for the community members.

### Flag News
- A Community manager can flag news within his community as "highlighted" while creating or editing a news:
  - Check "Promoted to front page" to make the news appear at community's homepage.
  - Check "Sticky at top of lists" to keep it always at top.
- A Community manager can manage News within his community thanks to my workbench.

[Go to top](#table-of-content)
