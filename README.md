# drupal-7-module-nbn
Module for Drupal 7 that allows information from NBN web services to be added to panel panes.

Requirements are a Drupal 7 site with the Panels module installed.
When editing the content on a Panels page, the module adds a group of components under an NBN section, which can be selected
and added to the page.
Each component will make calls to NBN web services and the returned results are themed and presented in the pane.
The settings for each component list all possible fields that can be displayed from which the user may select those they wish to
appear. They also list options for theming.
The module is comprised of 
 - nbn.module which contains all the hooks in to Drupal
 - nbn_client.inc which contains all the calls to the web services
 - /templates which contains information for different ways to theme the output
 - /sass which contains styling which is compiled in to /css (don't edit css files directly)
 - /plugins/content_types which contain a .inc file for each panel component.
