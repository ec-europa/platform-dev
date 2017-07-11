The NextEuropa Europa Search" feature provides a search interface integrated with the 
Europa Search services (ESS).


Table of content:
=================
- [Installation](#installation)
- [Proposed features](#features)
- [Configuration](#configuration)

# Installation

The feature is proposed through a Drupal custom module and is enabled by default in the NextEuropa platform.

[Go to top](#table-of-content)

# Proposed features

In the current module version, the module only provides a block with a "simple search" form allowing inserting search 
keywords. 
The search results will be displayed in the ESS interface.

With the Europa theme, the form is directly displayed in the site header while in the "ec_resp" one (old platform theme), 
it needs to be inserted manually like any Drupal block. 

## Foreseen evolution

* Full integration of the Europa Search services in order to display search results in the site instead of in the ES interface.

# Configuration
The block settings can be modified through the "NextEuropa Europa Search" form accessible via the admin menu 
(Configuration / Search and metadata / Europa Search settings).

It allows configuring 3 options:
1. **`Europa Search URL`**: the "action" URL defined for the simple search form
2. **`Default language`**: The language in which the Europa Search results are going to be displayed:<br />
* By selecting "Current language", the results page will be displayed in the same language as the page where the search has been submitted.<br />
* By selecting a language (e.g. "English"), the results page will be **always** displayed in this language.
3. **`Subset name for Restricted Search`**: the data subset that will be added to the action URL in order to instruct EuropaSearch to filter search results on its basis.<br />
 For more information, please consult the [Europa search documentation](http://ec.europa.eu/ipg/docs/services/search-guidelines_en.pdf), section  2.3.



