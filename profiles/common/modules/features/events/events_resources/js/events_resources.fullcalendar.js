/**
 * @file
 * Provides FullCalendar objects and functions.
 */

(function ($) {
  Drupal.behaviors.events_resources = {
    attach: function (context, settings) {
      if (Drupal.settings.events_resources && Drupal.settings.events_resources.resources) {
        Drupal.fullcalendar.plugins.events_resources = {
          options: function (fullcalendar, settings) {
            return {
              // The resources array for the "resourceDay" calendar view mode.
              resources: Drupal.settings.events_resources.resources
            };
          }
        };

        /**
         * Parse Drupal events from the DOM.
         *
         * TODO other way to find and call this func or the callback be called.
         */
        Drupal.fullcalendar.fullcalendar.prototype.parseEvents = function (callback) {
          var events = [];
          var details = this.$calendar.find('.fullcalendar-event-details');
          for (var i = 0; i < details.length; i++) {
            var event = $(details[i]);
            events.push({
              field: event.attr('field'),
              index: event.attr('index'),
              eid: event.attr('eid'),
              entity_type: event.attr('entity_type'),
              title: event.attr('title'),
              start: event.attr('start'),
              end: event.attr('end'),
              url: event.attr('href'),
              allDay: (event.attr('allDay') === '1'),
              resourceId: event.attr('resourceId'),
              className: event.attr('cn'),
              editable: (event.attr('editable') === '1'),
              dom_id: this.dom_id
            });
          }
          callback(events);
        };
      }
    }
  };
}(jQuery));
