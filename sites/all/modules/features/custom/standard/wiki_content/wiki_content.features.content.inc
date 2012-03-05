<?php
/**
 * @file
 * wiki_content.features.content.inc
 */

/**
 * Implements hook_content_defaults().
 */
function wiki_content_content_defaults() {
  $content = array();

  $content['wiki_cheesecake'] = (object) array(
    'exported_path' => 'wiki/cheese-cake-recipe',
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
          'value' => '<p>&nbsp;</p>
  <h2>
  	Ingredient</h2>
  <div>
  	&nbsp;</div>
  <div>
  	1 Crust recipe</div>
  <div>
  	4 Cream cheese -- softened,</div>
  <div>
  	-12oz ea.</div>
  <div>
  	1 1/4 c Sugar</div>
  <div>
  	3 tb All-purpose flour</div>
  <div>
  	4 Eggs</div>
  <div>
  	1/4 c Sour cream</div>
  <div>
  	1/4 c Heavy cream</div>
  <div>
  	2 Eggs yolks</div>
  <div>
  	1 t Vanilla extract</div>
  <div>
  	&nbsp;</div>
  <div>
  	&nbsp;</div>
  <h2>
  	Directions</h2>
  <div>
  	&nbsp;</div>
  <div>
  	&nbsp;</div>
  <div>
  	1 Preheat oven to 325 F. Position rack in center of oven.</div>
  <div>
  	2 Butter 9? springform pan. Wrap outside of pan with double layer of heavy-duty foil.</div>
  <div>
  	3 Press crust firmly into bottom and 1? up sides of pan; refrigerate</div>
  <div>
  	until needed or bake and cool.</div>
  <div>
  	4 With mixer at high speed beat cream cheese until smooth, about 5 minutes.</div>
  <div>
  	5 Combine sugar with flour. Reduce speed to low; beat sugar mixture into cream cheese, 1/4 cup at a time until smooth, about 3 minutes.</div>
  <div>
  	6 In bowl stir together eggs, sour cream, heavy cream, yolks and vanilla until</div>
  <div>
  	smooth.</div>
  <div>
  	7 Gradually beat egg mixture into cheese mixture until just incorporated.</div>
  <div>
  	8 Pour batter into pan. Place pan in large baking pan on oven rack; fill</div>
  <div>
  	baking pan with water halfway up sides of springform pan.</div>
  <div>
  	9 Bake 1 1/2 hours or until center of cheesecake is set. Remove from water bath; remove foil.</div>
  <div>
  	10 Cool on wire rack for 30 minutes; cool completely in refrigerator about 3 hours or over nite.</div>
  ',
          'summary' => '',
          'format' => 'full_html',
          'safe_value' => '<p> </p>
  <h2>
  	Ingredient</h2>
  <div>
  	 </div>
  <div>
  	1 Crust recipe</div>
  <div>
  	4 Cream cheese -- softened,</div>
  <div>
  	-12oz ea.</div>
  <div>
  	1 1/4 c Sugar</div>
  <div>
  	3 tb All-purpose flour</div>
  <div>
  	4 Eggs</div>
  <div>
  	1/4 c Sour cream</div>
  <div>
  	1/4 c Heavy cream</div>
  <div>
  	2 Eggs yolks</div>
  <div>
  	1 t Vanilla extract</div>
  <div>
  	 </div>
  <div>
  	 </div>
  <h2>
  	Directions</h2>
  <div>
  	 </div>
  <div>
  	 </div>
  <div>
  	1 Preheat oven to 325 F. Position rack in center of oven.</div>
  <div>
  	2 Butter 9? springform pan. Wrap outside of pan with double layer of heavy-duty foil.</div>
  <div>
  	3 Press crust firmly into bottom and 1? up sides of pan; refrigerate</div>
  <div>
  	until needed or bake and cool.</div>
  <div>
  	4 With mixer at high speed beat cream cheese until smooth, about 5 minutes.</div>
  <div>
  	5 Combine sugar with flour. Reduce speed to low; beat sugar mixture into cream cheese, 1/4 cup at a time until smooth, about 3 minutes.</div>
  <div>
  	6 In bowl stir together eggs, sour cream, heavy cream, yolks and vanilla until</div>
  <div>
  	smooth.</div>
  <div>
  	7 Gradually beat egg mixture into cheese mixture until just incorporated.</div>
  <div>
  	8 Pour batter into pan. Place pan in large baking pan on oven rack; fill</div>
  <div>
  	baking pan with water halfway up sides of springform pan.</div>
  <div>
  	9 Bake 1 1/2 hours or until center of cheesecake is set. Remove from water bath; remove foil.</div>
  <div>
  	10 Cool on wire rack for 30 minutes; cool completely in refrigerator about 3 hours or over nite.</div>
  ',
          'safe_summary' => '',
        ),
      ),
    ),
  );

return $content;
}
