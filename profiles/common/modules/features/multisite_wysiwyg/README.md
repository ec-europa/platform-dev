The multisite_wysiwyg feature provide some custom configuration for wysiwyg 
drupal module, media_wysiwyg module and the CKEditor plugin.
The feature is enabled by cce_basic_config.
It should be refactored so that all 5 text filters are enabled and configured
inside this feature. Currently the functionality is shared between 
cce_basic_config and multisite_wysiwyg. 
The module is installed with the profile, there is nothing to do.

Table of content:
=================
- [Best Practices](#best-practice)
- [User stories](#user-stories)
- [Available filters](#available-filters)
  - [Plain Text](#plain-text)
  - [Filtered HTML](#filtered-html)
  - [FULL HTML](#full-html)
  - [FULL HTML with Tracking changes](#full-html-with-tracking-changes)
  - [Basic HTML](#basic-html)
  
  # Best practice
  Whenever working with user-generated content, it's always best to keep input 
  format settings as secure as possible. Here are some things to consider:
  
  Using the "Full HTML" filter allows HTML to be posted unfiltered. This could 
  represent a severe security risk.
  
  Note that blanket inclusion of something like an `<img>` could result in 
  someone posting an image that is just too big for your page layout, breaking 
  the site.

  # User stories
  
  as an ADMINISTRATOR, I can restrict a user role to use a specific filter
  as an ADMINISTRATOR, I can restrict the length of a URL string
  as an ADMINISTRATOR, I can modify a filter to allow or restrict tags
  
  # Available filters
  
  Your site ships with 5 filters:
  
  ## Plain Text
      This format displays any HTML as plain text, convert URLs into links and 
      convert line breaks into HTML (i.e. <br> and <p>).
     At install, this filter is available for all roles
  
  ## Filtered HTML
      This is the workhorse input format that is used most of the time for 
      displaying posts such as blogs, pages, forum topics and so forth.
      The Full HTML input format :
       * Convert line breaks into HTML (i.e. `<br>` and `<p>`)
       * Replace tokens
       * Sanitizes HTML to prevent xss attack. 
       * Convert URLs into links with a limit of 72 characters.
     At install, this filter is available for anonymous user, authenticated 
     user, administrator, contributor, editor
  
  ##  FULL HTML
      The Full HTML input format :
       * Convert line breaks into HTML (i.e. `<br>` and `<p>`)
       * Convert Media tags to markup
       * Replace tokens
       * Sanitizes HTML to prevent xss attack. 
       * Convert URLs into links with a limit of 72 characters.
       * Correct faulty and chopped off HTML
     At install, this filter is available for the following user roles 
     authenticated user, administrator, contributor, editor
 
  ##  FULL HTML - Tracking changes
      The Full HTML & Tracking changes input format :
       * Convert line breaks into HTML (i.e. `<br>` and `<p>`)
       * Convert Media tags to markup
       * Replace tokens (to be implemented)
       * Sanitizes HTML to prevent xss attack. 
       * Convert URLs into links with a limit of 72 characters.
       * Correct faulty and chopped off HTML
     At install, this filter is available for the following user roles 
     authenticated user, administrator, contributor, editor
   
  ## Basic HTML
      This format displays any HTML as plain text, convert URLs into links and 
      convert line breaks into HTML (i.e. <br> and <p>) and correct faulty and 
      chopped off HTML.
     At install, this filter is available for the following user roles 
     anonymous user, authenticated user, administrator, contributor, editor
  