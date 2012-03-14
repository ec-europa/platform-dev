<?php
/**
 * @file
 * wiki_content.features.content.inc
 */

/**
 * Implements hook_content_defaults().
 */
function wiki_standard_content_content_defaults() {
  $content = array();

  $content['wiki_cheesecake'] = (object) array(
    'exported_path' => 'content/cheese-cake-recipe',
    'title' => 'cheese cake recipe',
    'status' => '1',
    'promote' => '0',
    'sticky' => '0',
    'type' => 'wiki',
    'language' => 'en',
    'created' => '1330966657',
    'comment' => '1',
    'translate' => '0',
    'machine_name' => 'wiki_cheesecake',
    'body' => array(
      'und' => array(
        0 => array(
          'value' => '<p><img alt="" src="http://coffeescorner.files.wordpress.com/2011/11/cheesecake.jpg" style="width: 300px; height: 200px; " /></p>
  <h2>
  	Ingredient</h2>
  <div>
  	<hr />
  	<ul>
  		<li>
  			1 Crust recipe</li>
  		<li>
  			4 Cream cheese -- softened,&nbsp;-12oz ea.</li>
  		<li>
  			1 1/4 c Sugar</li>
  		<li>
  			3 tb All-purpose flour</li>
  		<li>
  			4 Eggs</li>
  		<li>
  			1/4 c Sour cream</li>
  		<li>
  			1/4 c Heavy cream</li>
  		<li>
  			2 Eggs yolks</li>
  		<li>
  			1 t Vanilla extract</li>
  	</ul>
  </div>
  <div>
  	&nbsp;</div>
  <h2>
  	Directions</h2>
  <div>
  	<hr />
  	<ol>
  		<li>
  			Preheat oven to 325 F. Position rack in center of oven.</li>
  		<li>
  			Butter 9? springform pan. Wrap outside of pan with double layer of heavy-duty foil.</li>
  		<li>
  			Press crust firmly into bottom and 1? up sides of pan; refrigerate&nbsp;until needed or bake and cool.</li>
  		<li>
  			With mixer at high speed beat cream cheese until smooth, about 5 minutes.</li>
  		<li>
  			Combine sugar with flour. Reduce speed to low; beat sugar mixture into cream cheese, 1/4 cup at a time until smooth, about 3 minutes.</li>
  		<li>
  			In bowl stir together eggs, sour cream, heavy cream, yolks and vanilla until&nbsp;smooth.</li>
  		<li>
  			Gradually beat egg mixture into cheese mixture until just incorporated.</li>
  		<li>
  			Pour batter into pan. Place pan in large baking pan on oven rack; fill&nbsp;baking pan with water halfway up sides of springform pan.</li>
  		<li>
  			Bake 1 1/2 hours or until center of cheesecake is set. Remove from water bath; remove foil.</li>
  		<li>
  			Cool on wire rack for 30 minutes; cool completely in refrigerator about 3 hours or over nite.</li>
  	</ol>
  </div>
  <p>&nbsp;</p>
  ',
          'summary' => '',
          'format' => 'full_html',
          'safe_value' => '<p><img alt="" src="http://coffeescorner.files.wordpress.com/2011/11/cheesecake.jpg" style="width: 300px; height: 200px; " /></p>
  <h2>
  	Ingredient</h2>
  <div>
  <hr /><ul><li>
  			1 Crust recipe</li>
  <li>
  			4 Cream cheese -- softened, -12oz ea.</li>
  <li>
  			1 1/4 c Sugar</li>
  <li>
  			3 tb All-purpose flour</li>
  <li>
  			4 Eggs</li>
  <li>
  			1/4 c Sour cream</li>
  <li>
  			1/4 c Heavy cream</li>
  <li>
  			2 Eggs yolks</li>
  <li>
  			1 t Vanilla extract</li>
  </ul></div>
  <div>
  	 </div>
  <h2>
  	Directions</h2>
  <div>
  <hr /><ol><li>
  			Preheat oven to 325 F. Position rack in center of oven.</li>
  <li>
  			Butter 9? springform pan. Wrap outside of pan with double layer of heavy-duty foil.</li>
  <li>
  			Press crust firmly into bottom and 1? up sides of pan; refrigerate until needed or bake and cool.</li>
  <li>
  			With mixer at high speed beat cream cheese until smooth, about 5 minutes.</li>
  <li>
  			Combine sugar with flour. Reduce speed to low; beat sugar mixture into cream cheese, 1/4 cup at a time until smooth, about 3 minutes.</li>
  <li>
  			In bowl stir together eggs, sour cream, heavy cream, yolks and vanilla until smooth.</li>
  <li>
  			Gradually beat egg mixture into cheese mixture until just incorporated.</li>
  <li>
  			Pour batter into pan. Place pan in large baking pan on oven rack; fill baking pan with water halfway up sides of springform pan.</li>
  <li>
  			Bake 1 1/2 hours or until center of cheesecake is set. Remove from water bath; remove foil.</li>
  <li>
  			Cool on wire rack for 30 minutes; cool completely in refrigerator about 3 hours or over nite.</li>
  </ol></div>
  <p> </p>
  ',
          'safe_summary' => '',
        ),
      ),
    ),
  );

return $content;
}
