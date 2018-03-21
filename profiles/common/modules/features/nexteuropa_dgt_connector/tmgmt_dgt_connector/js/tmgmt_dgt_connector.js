/**
 * @file
 * Scripts for DGT connector module.
 */

jQuery(document).ready(function ($) {
    $(window).bind('beforeunload', function () {
        return "Please send or delete the job before leaving the page";
    });
});
