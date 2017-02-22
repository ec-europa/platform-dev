The "EC Embedded Video" feature allows to embed videos from YouTube, Vimeo, AV Portal or Dailymotion in "File" fields or in WYSIWYG
fields.

Table of content:
=================
- [Installation](#installation)
- [Proposed features](#features)

# Installation

The feature is proposed through a Drupal custom module and is available with the NextEuropa platform.

They are 2 ways to activate the feature:
1. Like any Drupal modules; via the "Modules" admin page or with the Drush command);
2. Like a "Feature set" through the Feature set admin page (path: admin/structure/feature-set_en).<br />
Then, Enable the "Embedded videos" feature and click on the "Validate" button.

[Go to top](#table-of-content)

# Proposed features

It allows inserting a video URL of a video hosted by YouTube, Vimeo, AV Portal or Dailymotion in "File" fields or 
in WYSIWYG field.

To do so, you just have to copy the URL from the site and paste it in field accessible via the media browser modal under 
the "Web" tab.

The feature proposed also 2 display modes for videos from YouTube, Vimeo, AV Portal or Dailymotion and that are inserted in WYSIWYG
fields:
1. The one supplied by modules managing every video of these types (AV Portal Video, Dailymotion Video,  Vimeo Video, YouTube Video).<br />
It embeds videos in an HTML wrapper (DIV tags).
2. The one supplied by the feature itself for these types (AV Portal Video without wrapper, Dailymotion Video without wrapper, 
Vimeo Video without wrapper, YouTube Video without wrapper).<br />
It displays the video player with any HTML wrapper (no DIV tags).

The module uses by default the second one for all videos but you can change easily the display in 2 different ways:
1. As administrator, you can change the display mode to apply via the "Manage file display" admin interface for the "Video" bundle"
(see admin/structure/file-types/manage/video/file-display/wysiwyg), and select the mode you want.<br />
There, you can also set one of these modes to another file display (ex.: Default, Teaser and Preview).<br />
**Please note that the 2 mentioned modes cannot be activated together!**
2. As contributor, you can select the view mode to apply after having saved the file. Before the media browser modal is closed,
it proposes a last screen where you can select the video display mode.<br />
If you want it without HTML wrapper, you must select the "WYSIWYG" option. If you want it with a container, select another option that
matches your needs.

[Go to top](#table-of-content)