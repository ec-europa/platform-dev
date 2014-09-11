Multisite review
================

Performs automated review of modules and features for the Multisite platform of the European Commission.

The Multisite Platform (aka FPFIS) is a web platform built on Drupal 7 that hosts websites for the EC.


## Dependencies

- The [Security review](https://www.drupal.org/project/security_review) module.


## Usage

- Enable the module or feature that you want to review.
- Log in as administrator.
- Go to Reports > Security Review (admin/reports/security-review_en).
- Open the "Run" fieldset and click on "Run checklist". The security review will be performed. This usually only takes a few seconds.
- When you get the results, find the line "Multisite Review successful|failed." and click on "Details".
- You get a list of all failures that were found against all enabled modules and features. These are grouped by module, so search for the one that you're reviewing and reap the results.

A list of supported reviews can be found on the [FPFIS wiki](https://webgate.ec.europa.eu/fpfis/wikis/pages/viewpage.action?pageId=84756238). This is only accessible to developers that are registered with the European Commission.
