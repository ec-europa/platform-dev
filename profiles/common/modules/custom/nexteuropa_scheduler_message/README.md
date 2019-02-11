This module checks when a node or revision is scheduled for publication when editing it.
When this happens it checks the publication date configured and, if it is after the limit date
configured on the module, shows a message.

By default, if nothing is configured, the module has these values:
* Message to show (nexteuropa_scheduler_message_text): 
    This node has been scheduled to be published at or after %date_to_check. Please ensure your changes will not lead to the premature publication of sensitive information.
* Date to check (nexteuropa_scheduler_message_time):
    2019-03-30 00:00:00

It is possible to override these values by configuring the values on the settings.php file like this:
* To change the message to show:
    // The text %date_to_check will be replaced by the date value from nexteuropa_scheduler_message_text (see below).
    // The text %date_to_publish will be replaced by the publication date of the node or the revision.
    // If nexteuropa_scheduler_message_text is not configured, it will use the default value (check Date to check (nexteuropa_scheduler_message_time)).
    $conf['nexteuropa_scheduler_message_text'] = 'Replace text %date_to_publish %date_to_check';  
* To change the date to check:
    // Use the format shown here, also take into account that this date will always use CET as timezone.
    $conf['nexteuropa_scheduler_message_time'] = '2019-03-30 01:00:00'; 

You can check the value of both parameters, if you have "administer scheduler" permissions. I will show the default values or the values from settings.php, if they are configured:
* admin/config/content/scheduler/scheduler_message

Translation
    It is possible to translate the default text or the test configured on the settings.php page.
    To allow translation take this steps:
    .- Ensure you have more than one language enabled.
    .- Load the page admin/config/content/scheduler/scheduler_message with a language different to english, for example:
            admin/config/content/scheduler/scheduler_message_fr
    .- Load the page admin/config/regional/translate/translate_en and search for the string translate.
