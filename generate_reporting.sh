#!/bin/bash
rm reporting_jrc-hub_production.txt
rm reporting_features-diff_jrc-hub_production.txt
drush status >> reporting_jrc-hub_production.txt
drush fc node >> reporting_jrc-hub_production.txt
drush field-info types >> reporting_jrc-hub_production.txt
drush field-info fields >> reporting_jrc-hub_production.txt
drush fl >> reporting_jrc-hub_production.txt
drush pml >> reporting_jrc-hub_production.txt
drush vl >> reporting_jrc-hub_production.txt
drush fc views_view >> reporting_jrc-hub_production.txt
drush fc taxonomy >> reporting_jrc-hub_production.txt
drush sqlq 'SELECT tid, vid, name FROM taxonomy_term_data;' >> reporting_jrc-hub_production.txt
drush fc variable >> reporting_jrc-hub_production.txt
drush fc context >> reporting_jrc-hub_production.txt
drush fc user_role >> reporting_jrc-hub_production.txt
drush fc user_permission >> reporting_jrc-hub_production.txt
drush sqlq 'SELECT * FROM custom_breadcrumb;' >> reporting_jrc-hub_production.txt
drush fc menu_links >> reporting_jrc-hub_production.txt

drush fd faq_content_default >> reporting_features-diff_jrc-hub_production.txt
drush fd news_standard_content >> reporting_features-diff_jrc-hub_production.txt
drush fd multisite_rules_configuration >> reporting_features-diff_jrc-hub_production.txt
drush fd article_extended >> reporting_features-diff_jrc-hub_production.txt
drush fd cce_basic_config >> reporting_features-diff_jrc-hub_production.txt
drush fd content_examples >> reporting_features-diff_jrc-hub_production.txt
drush fd f_a_q >> reporting_features-diff_jrc-hub_production.txt
drush fd fat_footer >> reporting_features-diff_jrc-hub_production.txt
drush fd gallerymedia_core >> reporting_features-diff_jrc-hub_production.txt
drush fd multilingual_tools >> reporting_features-diff_jrc-hub_production.txt
drush fd solr_config >> reporting_features-diff_jrc-hub_production.txt
drush fd multisite_settings_core >> reporting_features-diff_jrc-hub_production.txt
drush fd news_core >> reporting_features-diff_jrc-hub_production.txt
drush fd newsletters >> reporting_features-diff_jrc-hub_production.txt
drush fd sitemap >> reporting_features-diff_jrc-hub_production.txt
drush fd social_bookmark >> reporting_features-diff_jrc-hub_production.txt

date >> reporting_jrc-hub_production.txt
date >> reporting_features-diff_jrc-hub_production.txt

