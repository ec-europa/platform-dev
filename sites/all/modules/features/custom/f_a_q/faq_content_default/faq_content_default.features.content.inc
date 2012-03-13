<?php
/**
 * @file
 * faq_content_default.features.content.inc
 */

/**
 * Implements hook_content_defaults().
 */
function faq_content_default_content_defaults() {
  $content = array();

  $content['question_europa_01'] = (object) array(
    'exported_path' => 'content/europa-accessible-everyone',
    'title' => 'Is EUROPA accessible to everyone?',
    'status' => '1',
    'promote' => '0',
    'sticky' => '0',
    'type' => 'f_a_q',
    'language' => 'en',
    'created' => '1331112624',
    'comment' => '2',
    'translate' => '0',
    'machine_name' => 'question01',
    'body' => array(
      'und' => array(
        0 => array(
          'value' => '<p>&nbsp;</p>
  <p style="padding-top: 0px; padding-right: 0px; padding-bottom: 8px; padding-left: 0px; margin-top: 5px; margin-right: 0px; margin-bottom: 5px; margin-left: 0px; ">In 2001, the Commission pledged to make EUROPA more accessible for older people and people with disabilities.</p>
  <p style="padding-top: 0px; padding-right: 0px; padding-bottom: 8px; padding-left: 0px; margin-top: 5px; margin-right: 0px; margin-bottom: 5px; margin-left: 0px; ">The ways it is doing this are set out in this&nbsp;<a href="http://eur-lex.europa.eu/LexUriServ/LexUriServ.do?uri=COM:2001:0529:FIN:EN:PDF" style="color: rgb(21, 102, 159); text-decoration: underline; " title="EU policy paper – accessible EU websites">EU policy paper &ndash; accessible EU websites</a>&nbsp;<img border="0" class="alIco" src="http://europa.eu/wel/images/doc_icons/f_pdf_16.gif" style="border-top-style: none; border-right-style: none; border-bottom-style: none; border-left-style: none; border-width: initial; border-color: initial; padding-top: 0px; padding-right: 0px; padding-bottom: 0px; padding-left: 0px; margin-top: 0px; margin-right: 0px; margin-bottom: 0px; margin-left: 0px; " />&nbsp;[102KB]</p>
  <p style="padding-top: 0px; padding-right: 0px; padding-bottom: 8px; padding-left: 0px; margin-top: 5px; margin-right: 0px; margin-bottom: 5px; margin-left: 0px; ">Work has already begun to make&nbsp;<b>new and updated</b>&nbsp;EUROPA pages compliant with&nbsp;<b>conformance level A</b>, meaning they satisfy all&nbsp;<b>priority 1 criteria</b>&nbsp;in the internationally accepted&nbsp;<a href="http://www.w3.org/TR/WAI-WEBCONTENT/" style="color: rgb(21, 102, 159); text-decoration: underline; " title="Web Content Accessibility Guidelines">Web Content Accessibility Guidelines</a>&nbsp;issued by the&nbsp;<a href="http://www.w3.org/WAI/" style="color: rgb(21, 102, 159); text-decoration: underline; " title="Web Accessibility Initiative">Web Accessibility Initiative</a>&nbsp;(WAI) project.</p>
  <p style="padding-top: 0px; padding-right: 0px; padding-bottom: 8px; padding-left: 0px; margin-top: 5px; margin-right: 0px; margin-bottom: 5px; margin-left: 0px; ">Some top-level EUROPA sites (such as the EUROPA and European Commission homepages) already meet conformance level A and contain a logo to that effect.</p>
  <p style="padding-top: 0px; padding-right: 0px; padding-bottom: 8px; padding-left: 0px; margin-top: 5px; margin-right: 0px; margin-bottom: 5px; margin-left: 0px; "><a href="http://europa.eu/geninfo/accessibility_policy_en.htm" style="color: rgb(21, 102, 159); text-decoration: underline; " title="More on EUROPA accessibility policy">More on EUROPA accessibility policy</a>.</p>
  ',
          'summary' => '',
          'format' => 'filtered_html',
          'safe_value' => '<p> <br />
  In 2001, the Commission pledged to make EUROPA more accessible for older people and people with disabilities.<br />
  The ways it is doing this are set out in this <a href="http://eur-lex.europa.eu/LexUriServ/LexUriServ.do?uri=COM:2001:0529:FIN:EN:PDF" title="EU policy paper – accessible EU websites">EU policy paper – accessible EU websites</a>  [102KB]<br />
  Work has already begun to make new and updated EUROPA pages compliant with conformance level A, meaning they satisfy all priority 1 criteria in the internationally accepted <a href="http://www.w3.org/TR/WAI-WEBCONTENT/" title="Web Content Accessibility Guidelines">Web Content Accessibility Guidelines</a> issued by the <a href="http://www.w3.org/WAI/" title="Web Accessibility Initiative">Web Accessibility Initiative</a> (WAI) project.<br />
  Some top-level EUROPA sites (such as the EUROPA and European Commission homepages) already meet conformance level A and contain a logo to that effect.<br /><a href="http://europa.eu/geninfo/accessibility_policy_en.htm" title="More on EUROPA accessibility policy">More on EUROPA accessibility policy</a>.</p>
  ',
          'safe_summary' => '',
        ),
      ),
    ),
  );

  $content['question_europa_02'] = (object) array(
    'exported_path' => 'content/what-europa',
    'title' => 'What is EUROPA?',
    'status' => '1',
    'promote' => '0',
    'sticky' => '0',
    'type' => 'f_a_q',
    'language' => 'en',
    'created' => '1331113239',
    'comment' => '2',
    'translate' => '0',
    'machine_name' => 'question_europa_02',
    'body' => array(
      'und' => array(
        0 => array(
          'value' => '<p>&nbsp;</p>
  <p style="padding-top: 0px; padding-right: 0px; padding-bottom: 8px; padding-left: 0px; margin-top: 5px; margin-right: 0px; margin-bottom: 5px; margin-left: 0px; ">EUROPA is the official website of the European Union (EU). It was created in 1995. Broadly, it allows users do 3 things:</p>
  <ul class="lists" style="margin-top: 0px; margin-right: 0px; margin-bottom: 0px; margin-left: 15px; padding-top: 0px; padding-right: 0px; padding-bottom: 0px; padding-left: 0px; ">
  	<li style="list-style-image: url(http://europa.eu/wel/images/eu_portal/bullet-square.gif); padding-top: 0px; padding-right: 0px; padding-bottom: 6px; padding-left: 0px; ">
  		get&nbsp;<b>information</b>&nbsp;on the EU and what it does</li>
  	<li style="list-style-image: url(http://europa.eu/wel/images/eu_portal/bullet-square.gif); padding-top: 0px; padding-right: 0px; padding-bottom: 6px; padding-left: 0px; ">
  		give us&nbsp;<b>feedback</b>&nbsp;on EU policies, activities and services</li>
  	<li style="list-style-image: url(http://europa.eu/wel/images/eu_portal/bullet-square.gif); padding-top: 0px; padding-right: 0px; padding-bottom: 6px; padding-left: 0px; ">
  		perform certain&nbsp;<b>transactions</b>&nbsp;&ndash; tender for contracts, apply for jobs, enrol for events, order and buy documents, etc.</li>
  </ul>
  ',
          'summary' => '',
          'format' => 'filtered_html',
          'safe_value' => '<p> <br />
  EUROPA is the official website of the European Union (EU). It was created in 1995. Broadly, it allows users do 3 things:</p>
  <ul class="lists"><li>
  		get information on the EU and what it does</li>
  <li>
  		give us feedback on EU policies, activities and services</li>
  <li>
  		perform certain transactions – tender for contracts, apply for jobs, enrol for events, order and buy documents, etc.</li>
  </ul>',
          'safe_summary' => '',
        ),
      ),
    ),
  );

return $content;
}
