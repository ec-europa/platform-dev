/**
 * @file
 * NEPT-91: Delete the History object in order to avoid errors when loading some views with Ajax.
 */
History = {
    pushState: function() {}
};
