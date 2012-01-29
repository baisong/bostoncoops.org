<?php
// $Id: family.views_default.inc,v 1.4 2010/03/04 13:20:32 jerdiggity Exp $

/**
 * Implementation of hook_default_view_views().
 */
function family_views_default_views() {
$view = new view;
$view->name = 'family';
$view->description = 'Family main page and Family Indexes';
$view->tag = '';
$view->view_php = '';
$view->base_table = 'node';
$view->is_cacheable = FALSE;
$view->api_version = 2;
$view->disabled = FALSE; /* Edit this to TRUE to make a default view disabled initially */
$handler = $view->new_display('default', 'Defaults', 'default');
$handler->override_option('fields', array(
  'title' => array(
    'label' => 'Title', 
    'link_to_node' => 1, 
    'exclude' => 0, 
    'id' => 'title', 
    'table' => 'node', 
    'field' => 'title', 
    'override' => array(
      'button' => 'Override', 
    ), 
    'relationship' => 'none', 
  ), 
  'changed' => array(
    'id' => 'changed', 
    'table' => 'node', 
    'field' => 'changed', 
  ), 
));
$handler->override_option('sorts', array(
  'title' => array(
    'order' => 'DESC', 
    'id' => 'title', 
    'table' => 'node', 
    'field' => 'title', 
    'relationship' => 'none', 
  ), 
));
$handler->override_option('filters', array(
  'type' => array(
    'operator' => 'in', 
    'value' => array(), 
    'group' => '0', 
    'exposed' => FALSE, 
    'expose' => array(
      'operator' => FALSE, 
      'label' => '', 
    ), 
    'id' => 'type', 
    'table' => 'node', 
    'field' => 'type', 
    'relationship' => 'none', 
  ), 
  'status' => array(
    'operator' => '=', 
    'value' => 1, 
    'group' => '0', 
    'exposed' => FALSE, 
    'expose' => array(
      'operator' => FALSE, 
      'label' => '', 
    ), 
    'id' => 'status', 
    'table' => 'node', 
    'field' => 'status', 
    'relationship' => 'none', 
  ), 
));
$handler->override_option('access', array(
  'type' => 'perm', 
  'perm' => 'access family nodes', 
));
$handler->override_option('title', 'Family');
$handler->override_option('items_per_page', 40);
$handler->override_option('use_pager', '1');
$handler->override_option('style_plugin', 'table');
$handler->override_option('style_options', array(
  'grouping' => '', 
  'override' => 1, 
  'sticky' => 0, 
  'order' => 'desc', 
  'columns' => array(
    'lastname' => 'lastname', 
    'firstname' => 'firstname', 
    'middlename' => 'middlename', 
    'gender' => 'gender', 
    'birthdate' => 'birthdate', 
    'deathdate' => 'deathdate', 
  ), 
  'info' => array(
    'lastname' => array(
      'sortable' => 1, 
      'separator' => '', 
    ), 
    'firstname' => array(
      'sortable' => 1, 
      'separator' => '', 
    ), 
    'middlename' => array(
      'sortable' => 1, 
      'separator' => '', 
    ), 
    'gender' => array(
      'sortable' => 1, 
      'separator' => '', 
    ), 
    'birthdate' => array(
      'sortable' => 1, 
      'separator' => '', 
    ), 
    'deathdate' => array(
      'sortable' => 1, 
      'separator' => '', 
    ), 
  ), 
  'default' => '-1', 
));
$handler = $view->new_display('page', 'Family Page', 'page_1');
$handler->override_option('fields', array(
  'title' => array(
    'label' => 'Title', 
    'link_to_node' => 1, 
    'exclude' => 0, 
    'id' => 'title', 
    'table' => 'node', 
    'field' => 'title', 
    'override' => array(
      'button' => 'Override', 
    ), 
    'relationship' => 'none', 
  ), 
  'changed' => array(
    'label' => 'Last Updated', 
    'date_format' => 'time ago', 
    'custom_date_format' => '', 
    'exclude' => 0, 
    'id' => 'changed', 
    'table' => 'node', 
    'field' => 'changed', 
    'override' => array(
      'button' => 'Use default', 
    ), 
    'relationship' => 'none', 
  ), 
  'type' => array(
    'label' => 'Type', 
    'link_to_node' => 0, 
    'exclude' => 0, 
    'id' => 'type', 
    'table' => 'node', 
    'field' => 'type', 
    'override' => array(
      'button' => 'Use default', 
    ), 
    'relationship' => 'none', 
  ), 
));
$handler->override_option('sorts', array(
  'changed' => array(
    'order' => 'DESC', 
    'granularity' => 'second', 
    'id' => 'changed', 
    'table' => 'node', 
    'field' => 'changed', 
    'override' => array(
      'button' => 'Use default', 
    ), 
    'relationship' => 'none', 
  ), 
));
$handler->override_option('filters', array(
  'type' => array(
    'operator' => 'in', 
    'value' => array(
      'family_individual' => 'family_individual', 
      'family_group' => 'family_group', 
      'family_location' => 'family_location', 
    ), 
    'group' => '0', 
    'exposed' => FALSE, 
    'expose' => array(
      'operator' => FALSE, 
      'label' => '', 
    ), 
    'id' => 'type', 
    'table' => 'node', 
    'field' => 'type', 
    'relationship' => 'none', 
    'override' => array(
      'button' => 'Use default', 
    ), 
  ), 
  'status' => array(
    'operator' => '=', 
    'value' => 1, 
    'group' => '0', 
    'exposed' => FALSE, 
    'expose' => array(
      'operator' => FALSE, 
      'label' => '', 
    ), 
    'id' => 'status', 
    'table' => 'node', 
    'field' => 'status', 
    'override' => array(
      'button' => 'Use default', 
    ), 
    'relationship' => 'none', 
  ), 
));
$handler->override_option('header', '<p>
Welcome to the family area. Here you can view all the data on the website. In the left menu you can choose to view all individuals, groups and locations. To view a family tree, ascendancy or descendancy go to the page of the family member you want to view and click the associated tab along the top menu. If you have more information to add to this family tree you can add it by clicking \'create content\' on the side menu or commenting on the page you have information to add to. If you are not sure how to do this please contact the webmaster by clicking the contact link in the menu.
</p>');
$handler->override_option('header_format', '1');
$handler->override_option('header_empty', 1);
$handler->override_option('items_per_page', 10);
$handler->override_option('use_pager', '0');
$handler->override_option('style_options', array(
  'grouping' => '', 
  'override' => 1, 
  'sticky' => 0, 
  'order' => 'desc', 
  'columns' => array(
    'title' => 'title', 
    'changed' => 'changed', 
    'type' => 'type', 
  ), 
  'info' => array(
    'title' => array(
      'sortable' => 0, 
      'separator' => '', 
    ), 
    'changed' => array(
      'sortable' => 0, 
      'separator' => '', 
    ), 
    'type' => array(
      'sortable' => 0, 
      'separator' => '', 
    ), 
  ), 
  'default' => '-1', 
));
$handler->override_option('path', 'family');
$handler->override_option('menu', array(
  'type' => 'normal', 
  'title' => 'Family', 
  'weight' => '0', 
));
$handler->override_option('tab_options', array(
  'type' => 'none', 
  'title' => '', 
  'weight' => 0, 
));
$handler = $view->new_display('page', 'Individuals Page', 'page_2');
$handler->override_option('fields', array(
  'lastname' => array(
    'label' => 'Surname', 
    'link_to_node' => 1, 
    'exclude' => 0, 
    'id' => 'lastname', 
    'table' => 'family_individual', 
    'field' => 'lastname', 
    'relationship' => 'none', 
    'override' => array(
      'button' => 'Use default', 
    ), 
  ), 
  'firstname' => array(
    'label' => 'Forename', 
    'link_to_node' => 1, 
    'exclude' => 0, 
    'id' => 'firstname', 
    'table' => 'family_individual', 
    'field' => 'firstname', 
    'relationship' => 'none', 
  ), 
  'middlename' => array(
    'label' => 'Middlename(s)', 
    'link_to_node' => 1, 
    'exclude' => 0, 
    'id' => 'middlename', 
    'table' => 'family_individual', 
    'field' => 'middlename', 
    'relationship' => 'none', 
  ), 
  'gender' => array(
    'label' => 'Gender', 
    'link_to_node' => 1, 
    'exclude' => 0, 
    'id' => 'gender', 
    'table' => 'family_individual', 
    'field' => 'gender', 
    'relationship' => 'none', 
  ), 
  'birthdate' => array(
    'label' => 'Birth Date', 
    'exclude' => 0, 
    'id' => 'birthdate', 
    'table' => 'family_individual', 
    'field' => 'birthdate', 
    'relationship' => 'none', 
  ), 
  'deathdate' => array(
    'label' => 'Death Date', 
    'exclude' => 0, 
    'id' => 'deathdate', 
    'table' => 'family_individual', 
    'field' => 'deathdate', 
    'relationship' => 'none', 
  ), 
));
$handler->override_option('sorts', array(
  'lastname' => array(
    'order' => 'DESC', 
    'id' => 'lastname', 
    'table' => 'family_individual', 
    'field' => 'lastname', 
    'override' => array(
      'button' => 'Use default', 
    ), 
    'relationship' => 'none', 
  ), 
));
$handler->override_option('filters', array(
  'type' => array(
    'operator' => 'in', 
    'value' => array(
      'family_individual' => 'family_individual', 
    ), 
    'group' => '0', 
    'exposed' => FALSE, 
    'expose' => array(
      'operator' => FALSE, 
      'label' => '', 
    ), 
    'id' => 'type', 
    'table' => 'node', 
    'field' => 'type', 
    'relationship' => 'none', 
    'override' => array(
      'button' => 'Use default', 
    ), 
  ), 
  'status' => array(
    'operator' => '=', 
    'value' => 1, 
    'group' => '0', 
    'exposed' => FALSE, 
    'expose' => array(
      'operator' => FALSE, 
      'label' => '', 
    ), 
    'id' => 'status', 
    'table' => 'node', 
    'field' => 'status', 
    'override' => array(
      'button' => 'Use default', 
    ), 
    'relationship' => 'none', 
  ), 
));
$handler->override_option('title', 'Individuals Index');
$handler->override_option('style_options', array(
  'grouping' => '', 
  'override' => 1, 
  'sticky' => 0, 
  'order' => 'desc', 
  'columns' => array(
    'lastname' => 'lastname', 
    'firstname' => 'firstname', 
    'middlename' => 'middlename', 
    'gender' => 'gender', 
    'birthdate' => 'birthdate', 
    'deathdate' => 'deathdate', 
  ), 
  'info' => array(
    'lastname' => array(
      'sortable' => 1, 
      'separator' => '', 
    ), 
    'firstname' => array(
      'sortable' => 1, 
      'separator' => '', 
    ), 
    'middlename' => array(
      'sortable' => 1, 
      'separator' => '', 
    ), 
    'gender' => array(
      'sortable' => 1, 
      'separator' => '', 
    ), 
    'birthdate' => array(
      'sortable' => 1, 
      'separator' => '', 
    ), 
    'deathdate' => array(
      'sortable' => 1, 
      'separator' => '', 
    ), 
  ), 
  'default' => 'lastname', 
));
$handler->override_option('path', 'family/individual');
$handler->override_option('menu', array(
  'type' => 'normal', 
  'title' => 'Individuals Index', 
  'weight' => '0', 
));
$handler->override_option('tab_options', array(
  'type' => 'none', 
  'title' => '', 
  'weight' => 0, 
));
$handler = $view->new_display('page', 'Groups Page', 'page_3');
$handler->override_option('fields', array(
  'title' => array(
    'label' => 'Title', 
    'link_to_node' => 1, 
    'exclude' => 0, 
    'id' => 'title', 
    'table' => 'node', 
    'field' => 'title', 
    'override' => array(
      'button' => 'Use default', 
    ), 
    'relationship' => 'none', 
  ), 
  'marr_type' => array(
    'label' => 'Type', 
    'link_to_node' => 1, 
    'exclude' => 0, 
    'id' => 'marr_type', 
    'table' => 'family_group', 
    'field' => 'marr_type', 
    'override' => array(
      'button' => 'Use default', 
    ), 
    'relationship' => 'none', 
  ), 
  'parent1' => array(
    'label' => 'Parent 1', 
    'exclude' => 0, 
    'id' => 'parent1', 
    'table' => 'family_group', 
    'field' => 'parent1', 
    'override' => array(
      'button' => 'Use default', 
    ), 
    'relationship' => 'none', 
  ), 
  'parent2' => array(
    'label' => 'Parent 2', 
    'exclude' => 0, 
    'id' => 'parent2', 
    'table' => 'family_group', 
    'field' => 'parent2', 
    'override' => array(
      'button' => 'Use default', 
    ), 
    'relationship' => 'none', 
  ), 
));
$handler->override_option('sorts', array(
  'title' => array(
    'order' => 'DESC', 
    'id' => 'title', 
    'table' => 'node', 
    'field' => 'title', 
    'override' => array(
      'button' => 'Use default', 
    ), 
    'relationship' => 'none', 
  ), 
));
$handler->override_option('filters', array(
  'type' => array(
    'operator' => 'in', 
    'value' => array(
      'family_group' => 'family_group', 
    ), 
    'group' => '0', 
    'exposed' => FALSE, 
    'expose' => array(
      'operator' => FALSE, 
      'label' => '', 
    ), 
    'id' => 'type', 
    'table' => 'node', 
    'field' => 'type', 
    'relationship' => 'none', 
    'override' => array(
      'button' => 'Use default', 
    ), 
  ), 
  'status' => array(
    'operator' => '=', 
    'value' => 1, 
    'group' => '0', 
    'exposed' => FALSE, 
    'expose' => array(
      'operator' => FALSE, 
      'label' => '', 
    ), 
    'id' => 'status', 
    'table' => 'node', 
    'field' => 'status', 
    'override' => array(
      'button' => 'Use default', 
    ), 
    'relationship' => 'none', 
  ), 
));
$handler->override_option('title', 'Groups Index');
$handler->override_option('style_options', array(
  'grouping' => '', 
  'override' => 1, 
  'sticky' => 0, 
  'order' => 'desc', 
  'columns' => array(
    'title' => 'title', 
    'marr_type' => 'marr_type', 
    'parent1' => 'parent1', 
    'parent2' => 'parent2', 
  ), 
  'info' => array(
    'title' => array(
      'sortable' => 1, 
      'separator' => '', 
    ), 
    'marr_type' => array(
      'sortable' => 1, 
      'separator' => '', 
    ), 
    'parent1' => array(
      'sortable' => 1, 
      'separator' => '', 
    ), 
    'parent2' => array(
      'sortable' => 1, 
      'separator' => '', 
    ), 
  ), 
  'default' => 'title', 
));
$handler->override_option('path', 'family/group');
$handler->override_option('menu', array(
  'type' => 'normal', 
  'title' => 'Groups Index', 
  'weight' => '0', 
));
$handler->override_option('tab_options', array(
  'type' => 'none', 
  'title' => '', 
  'weight' => 0, 
));
$handler = $view->new_display('page', 'Locations Page', 'page_4');
$handler->override_option('fields', array(
  'building' => array(
    'label' => 'Building', 
    'link_to_node' => 1, 
    'exclude' => 0, 
    'id' => 'building', 
    'table' => 'family_location', 
    'field' => 'building', 
    'override' => array(
      'button' => 'Use default', 
    ), 
    'relationship' => 'none', 
  ), 
  'street' => array(
    'label' => 'Street', 
    'link_to_node' => 1, 
    'exclude' => 0, 
    'id' => 'street', 
    'table' => 'family_location', 
    'field' => 'street', 
    'override' => array(
      'button' => 'Use default', 
    ), 
    'relationship' => 'none', 
  ), 
  'city' => array(
    'label' => 'City', 
    'link_to_node' => 1, 
    'exclude' => 0, 
    'id' => 'city', 
    'table' => 'family_location', 
    'field' => 'city', 
    'override' => array(
      'button' => 'Use default', 
    ), 
    'relationship' => 'none', 
  ), 
  'county' => array(
    'label' => 'County', 
    'link_to_node' => 1, 
    'exclude' => 0, 
    'id' => 'county', 
    'table' => 'family_location', 
    'field' => 'county', 
    'override' => array(
      'button' => 'Use default', 
    ), 
    'relationship' => 'none', 
  ), 
  'state_province' => array(
    'label' => 'State/Province', 
    'link_to_node' => 1, 
    'exclude' => 1, 
    'id' => 'state_province', 
    'table' => 'family_location', 
    'field' => 'state_province', 
    'override' => array(
      'button' => 'Use default', 
    ), 
    'relationship' => 'none', 
  ), 
  'country' => array(
    'label' => 'Country', 
    'link_to_node' => 1, 
    'exclude' => 0, 
    'id' => 'country', 
    'table' => 'family_location', 
    'field' => 'country', 
    'override' => array(
      'button' => 'Use default', 
    ), 
    'relationship' => 'none', 
  ), 
));
$handler->override_option('sorts', array(
  'title' => array(
    'order' => 'DESC', 
    'id' => 'title', 
    'table' => 'node', 
    'field' => 'title', 
    'override' => array(
      'button' => 'Use default', 
    ), 
    'relationship' => 'none', 
  ), 
));
$handler->override_option('filters', array(
  'type' => array(
    'operator' => 'in', 
    'value' => array(
      'family_location' => 'family_location', 
    ), 
    'group' => '0', 
    'exposed' => FALSE, 
    'expose' => array(
      'operator' => FALSE, 
      'label' => '', 
    ), 
    'id' => 'type', 
    'table' => 'node', 
    'field' => 'type', 
    'relationship' => 'none', 
    'override' => array(
      'button' => 'Use default', 
    ), 
  ), 
  'status' => array(
    'operator' => '=', 
    'value' => 1, 
    'group' => '0', 
    'exposed' => FALSE, 
    'expose' => array(
      'operator' => FALSE, 
      'label' => '', 
    ), 
    'id' => 'status', 
    'table' => 'node', 
    'field' => 'status', 
    'override' => array(
      'button' => 'Use default', 
    ), 
    'relationship' => 'none', 
  ), 
));
$handler->override_option('title', 'Locations Index');
$handler->override_option('style_options', array(
  'grouping' => '', 
  'override' => 1, 
  'sticky' => 0, 
  'order' => 'desc', 
  'columns' => array(
    'building' => 'building', 
    'street' => 'street', 
    'city' => 'city', 
    'county' => 'county', 
    'state_province' => 'state_province', 
    'country' => 'country', 
  ), 
  'info' => array(
    'building' => array(
      'sortable' => 1, 
      'separator' => '', 
    ), 
    'street' => array(
      'sortable' => 1, 
      'separator' => '', 
    ), 
    'city' => array(
      'sortable' => 1, 
      'separator' => '', 
    ), 
    'county' => array(
      'sortable' => 1, 
      'separator' => '', 
    ), 
    'state_province' => array(
      'sortable' => 1, 
      'separator' => '', 
    ), 
    'country' => array(
      'sortable' => 1, 
      'separator' => '', 
    ), 
  ), 
  'default' => '-1', 
));
$handler->override_option('path', 'family/location');
$handler->override_option('menu', array(
  'type' => 'normal', 
  'title' => 'Location Index', 
  'weight' => '0', 
));
$handler->override_option('tab_options', array(
  'type' => 'none', 
  'title' => '', 
  'weight' => 0, 
));
$views[$view->name] = $view;

return $views;
}
