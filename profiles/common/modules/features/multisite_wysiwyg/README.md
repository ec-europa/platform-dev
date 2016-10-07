The Multisite WYSIWYG feature provides some custom configuration for WYSIWYG 
Drupal module, media_wysiwyg module and the CKEditor plugin.
The feature is enabled by cce_basic_config.
It should be refactored so that all 5 text filters are enabled and configured
inside this feature. Currently the functionality is shared between 
cce_basic_config and Multisite WYSIWYG. 
The module is installed with the profile, there is nothing to do.

Table of content:
=================
- [Best Practices](#best-practice)
- [User stories](#user-stories)
- [Available filters](#available-filters)
  - [Plain Text](#plain-text)
  - [Filtered HTML](#filtered-html)
  - [FULL HTML](#full-html)
  - [FULL HTML + Tracking changes](#full-html-with-tracking-changes)
  - [Basic HTML](#basic-html)
- [Change tracking configuration (CKEditor LITE)](#ckeditor-lite) 
  
  # Best practice
  Whenever working with user-generated content, it's always best to keep input 
  format settings as secure as possible. Here are some things to consider:
  
  Using the "Full HTML" filter allows HTML to be posted unfiltered. This could 
  represent a severe security risk.
  
  Note that blanket inclusion of something like an `<img>` could result in 
  someone posting an image that is just too big for your page layout, breaking 
  the site.

  # User stories
  
  As an ADMINISTRATOR, I can restrict a user role to use a specific filter.
  As an ADMINISTRATOR, I can restrict the length of a URL string.
  As an ADMINISTRATOR, I can modify a filter to allow or restrict tags.
  As an ADMINISTRATOR, I can activate/deactivate the change tracking feature in
  the WYSIWYG profiles.
  
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
 
  ##  FULL HTML + Tracking changes
      The Full HTML & Tracking changes input format :
       * Convert line breaks into HTML (i.e. `<br>` and `<p>`)
       * Convert Media tags to markup
       * Replace tokens (to be implemented)
       * Sanitizes HTML to prevent xss attack. 
       * Convert URLs into links with a limit of 72 characters.
       * Correct faulty and chopped off HTML
     At install, this filter is available for the following user roles 
     authenticated user, administrator, contributor, editor.
     > **Note**: 
     * For older sites, this profile can be missing. If it is required,
     it can be created automatically by clicking the 
     "Create Full HTML + Change tracking profile" button
     on the MULTISITE WYSIWYG settings interface (Admin > 
     Configuration > Content authoring > MULTISITE WYSIWYG > Settings).<br><br>
     Please check afterwards if permissions are correctly set.
     * It has the Change tracking feature activated and should be only used with
     WYSIWYG fields where the feature is required order to avoid browser 
     performances that mainly appear for edit forms that display a huge amount of 
     fields.  
        
  ## Basic HTML
      This format displays any HTML as plain text, convert URLs into links and 
      convert line breaks into HTML (i.e. <br> and <p>) and correct faulty and 
      chopped off HTML.
     At install, this filter is available for the following user roles 
     anonymous user, authenticated user, administrator, contributor, editor
  
  # Change tracking configuration (CKEditor LITE)
  
  Change tracking feature is supplied by the "CKEditor LITE" module that allows
  tracking changes in WYSIWYG fields (e.g. Long text or Long text with summary). 
  Thanks to 5 buttons, it also allows:
    * Showing or hiding tracked changes ("Show/hide tracked changes" button);
    * Accepting or rejecting a change tracked or all changes tracked in 
  a field ("Accept change", "Reject changes", "Accept all changes", "Reject all
  changes" buttons).
  
  In a default installation of the platform, this feature is only available in 
  the "FULL HTML - Tracking changes" text format.
  
  The platform extends the "CKEditor LITE" module at 3 levels:
   * [Centralizing the feature activation](#central-activation);
   * [Impacting the buttons display](#buttons-display);
   * [Control the content saving](#saving-control).
    
   ## Centralizing the feature activation
   
   Normally, with the WYSIWYG module, a feature managed by a specific editor plugin
   must be activated in all WYSIWYG profiles that can be used by the different text
   format filters.
   
   The module proposes an admin interface that centralizes the activation or 
   deactivation of the change tracking feature in the different WYSIWYG profiles.
   
   To do so, access the MULTISITE WYSIWYG settings 
   (Admin > Configuration > Content authoring > MULTISITE WYSIWYG > Settings), below 
   the summary table listing, there is a field set called "Enable/Disable change 
   tracking for selected WYSIWYG profile".
   
   There, by selecting an option in the "_Select operation_" select box and a WYSIWYG 
   profile in the "_Select profile_" one, the change tracking feature can be enable or
   disable for the selected WYSIWYG profile.
   
   Once the form is submitted, **all** buttons related to the feature will appear in or disappear
   from WYSIWYG profile toolbar displayed with WYSIWYG fields. 
   
   ## Impacting the buttons display
   
   Normally, with the CKEditor LITE module that manages the tracking change plugin for CKEditor,
   buttons appear directly in the toolbar once the plugin is activated.
   
   This behaviour generates problems with some browser versions that impact edit form operations.
   
   In order to mitigate these problems, 2 extensions have been introduced by the module:
   * "Disable on create content pages" option: Sets if the change tracking change buttons must be
   displayed with WYSIWYG fields (if the feature is activated) in the content **creation** form.
   <br><br>**It is recommended to enable it** because of problems to fill easily and smoothly WYSIWYG fields
   in IE11.
   
   * "Enable tracking on edit content pages" option: Sets if the change tracking buttons that activate
   and highlight tracked changes must be active by default or not in WYSIWYG fields of a content edit form.
   <br><br>**It is only recommended to enable it** if the change tracking feature is heavily used by contributor
   team.
      
   They can be activated in the MULTISITE WYSIWYG settings 
   (Admin > Configuration > Content authoring > MULTISITE WYSIWYG > Settings).
   
   To do so, checked options and click on the submit button displayed below these options.
   
   ## Control the content saving
    
  The NextEuropa platform extends also the CKEditor LITE module by implementing a control during the content
  saving and during the saving of the Workbench moderation state change.
  If conditions to save a content with tracked changes are not fulfilled, the saving is blocked and error
  messages are displayed.
  
  This extension is managed by the "NextEuropa Editorial" module and more information about it can be found in
  its documentation (README.md).
  