$(function() {
    $(document).ready(function() {
        var $datepicker = $("#datepicker");

        $datepicker.datepicker({
            changeMonth: true,
            changeYear: true
        });

        $(window).resize(function() {
          $datepicker.datepicker('hide');
        });
    });
});
