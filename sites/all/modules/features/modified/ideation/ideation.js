/**
 * Override for fivestarDefaultResult
 */
(function ($) {
  
  //fix some ridiculous issue with IMCE
  $(document).ready(function(){
    if(typeof imce != 'undefined'){
      $(document.body).append('<div style="display:none" id="message-box"></div>');
      imce.msgBox = imce.el('message-box');
    }
  });
  
  //Fix some other ridiculous issue with jquery not calling the success function
  $(document).ajaxComplete(function(e, xhr, settings){
    if(settings.url.indexOf('fivestar/vote/') > -1){
      fivestarResult($(xhr.responseText));
    }
  });
  
  window.fivestarResult = function(result) { 
  
    if ($('vote id', result).size()) {
  	var id = $('vote id', result).text();
  	var average = parseFloat($('result average', result).text());
  	// Convert average to 0 to 5 scale.
  	average = (average == 0 ?  average : (average / 100) * 5);
  	// Format like 4.5 (extra significant digit).
  	average = average.toPrecision(2);
  	var count = parseFloat($('result count', result).text());
  	// Handle plural of vote count.
  	
  	count == 1 ? count = count + ' vote' : count = count + ' votes';
      $("div.fivestar-form-vote-" + id + "> div.fivestar-tally-box > div.fivestar-average").html(average);
      $("div.fivestar-form-vote-" + id + "> div.fivestar-tally-box > div.fivestar-count").html(count);
    }
  }
})(jQuery);