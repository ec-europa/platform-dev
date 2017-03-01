The "EC Embedded Video" feature allows to embed videos from YouTube, Vimeo, AV Portal or Dailymotion in "File" fields or in WYSIWYG
fields.

Table of content:
=================
- [Installation](#installation)
- [Proposed features](#proposed-features)

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

The feature also proposes 2 file "formatters" for videos from YouTube, Vimeo, AV Portal or Dailymotion. It can be used in 
the different display modes for these kinds of video files:
1. The one supplied by modules managing every videos of these types (AV Portal Video, Dailymotion Video,  Vimeo Video, YouTube Video).<br />
It embeds videos in an HTML wrapper (DIV tags).
2. The one supplied by the feature itself for these types (AV Portal Video without wrapper, Dailymotion Video without wrapper, 
Vimeo Video without wrapper, YouTube Video without wrapper).<br />
It displays the video player without any HTML wrapper (no DIV tags).

The "EC Embedded Video" module activates by default the second one for the WYSIWYG display mode.
Then, if a contributor selects the "WYSIWYG" display mode for the video file inserted in the WYSIWYG field, the video will be 
displayed without any wrapper.
This behaviour does not concern the video files that are directly uploaded from a local file system.

If necessary, this configuration can be change via the "Manage file display" admin interface for the "Video" bundle"
(see admin/structure/file-types/manage/video/file-display/wysiwyg), and select the mode you want.
**Please note that the 2 mentioned modes cannot be activated together!**

[Go to top](#table-of-content)