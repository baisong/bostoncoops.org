<?php
// $Id: views.inc,v 1.5 2010/03/04 13:20:32 jerdiggity Exp $

/**
 * Implementation of hook_views_tables().
 */
function family_views_tables() {
$tables['family_individual'] = array(
  'name' => 'family_individual', 
  'join' => array(
   'left' => array(
      'table' => 'node', 
      'field' => 'nid', 
    ), 
    'right' => array(
      'field' => 'nid', 
    ), 
  ), 
  'fields' => array(
      'firstname' => array(
        'name' => t('Family Indiv: Forename'), 
        'sortable' => TRUE, 
        'help' => t('Family individuals Forename'), 
    'handler' => 'views_handler_field_nodelink', 
            'option' => array(
           '#type' => 'select', 
           '#options' => array(
             'link' => 'As link', 
             'nolink' => 'Without link'
            ), 
        ), 
      ), 
      'middlename' => array(
        'name' => t('Family Indiv: Middlename'), 
        'sortable' => TRUE, 
        'help' => t('Family individuals Middlename'), 
    'handler' => 'views_handler_field_nodelink', 
                'option' => array(
           '#type' => 'select', 
           '#options' => array(
             'link' => 'As link', 
             'nolink' => 'Without link'
            ), 
        ), 
      ), 
      'lastname' => array(
        'name' => t('Family Indiv: Lastname'), 
        'sortable' => TRUE, 
        'help' => t('Family individuals Surname'), 
    'handler' => 'views_handler_field_nodelink', 
                'option' => array(
           '#type' => 'select', 
           '#options' => array(
             'link' => 'As link', 
             'nolink' => 'Without link'
            ), 
        ), 
      ), 
      'gender' => array(
        'name' => t('Family Indiv: Gender'), 
        'help' => t('Family individuals Gender'), 
    'handler' => 'views_handler_field_nodelink', 
            'option' => array(
           '#type' => 'select', 
           '#options' => array(
             'link' => 'As link', 
             'nolink' => 'Without link'
            ), 
        ), 
      ), 
      'birthdate' => array(
        'name' => t('Family Indiv: Birth date'), 
        'sortable' => TRUE, 
        'help' => t('Family individuals Birth Date'), 
        'handler' => 'family_views_date', 
            'option' => array(
           '#type' => 'select', 
           '#options' => array(
             'link' => 'As link', 
             'nolink' => 'Without link'
            ), 
        ), 
      ), 
      'deathdate' => array(
        'name' => t('Family: Deathdate'), 
        'sortable' => TRUE, 
        'help' => t('Family individuals Death Date'), 
    'handler' => 'family_views_date', 
            'option' => array(
           '#type' => 'select', 
           '#options' => array(
             'link' => 'As link', 
             'nolink' => 'Without link'
            ), 
        ), 
      ), 
    ), 
    'filters' => array(
    
    
    ), 
  );
  $tables['family_group'] = array(
  'name' => 'family_group', 
  'join' => array(
   'left' => array(
      'table' => 'node', 
      'field' => 'nid', 
    ), 
    'right' => array(
      'field' => 'nid', 
    ), 
  ), 
  'fields' => array(
      'marr_type' => array(
        'name' => t('Family Group: Type'), 
        'sortable' => TRUE, 
        'help' => t('Family Group marriage type'), 
    'handler' => 'views_handler_field_nodelink', 
            'option' => array(
           '#type' => 'select', 
           '#options' => array(
             'link' => 'As link', 
             'nolink' => 'Without link'
            ), 
        ), 
      ), 
      'marr_date' => array(
        'name' => t('Family Group: Marriage Date'), 
        'sortable' => TRUE, 
        'help' => t('Family Group marriage date'), 
    'handler' => 'views_handler_field_nodelink', 
                'option' => array(
           '#type' => 'select', 
           '#options' => array(
             'link' => 'As link', 
             'nolink' => 'Without link'
            ), 
        ), 
      ), 
      'marr_plac' => array(
        'name' => t('Family Group: Marriage Place'), 
        'sortable' => TRUE, 
        'help' => t('Family Group marriage place'), 
    'handler' => 'family_views_location', 
                'option' => array(
           '#type' => 'select', 
           '#options' => array(
             'link' => 'As link', 
             'nolink' => 'Without link'
            ), 
        ), 
      ), 
      'div_date' => array(
        'name' => t('Family Group: Divorce date'), 
        'help' => t('Family Group divorce date'), 
    'handler' => 'views_handler_field_nodelink', 
            'option' => array(
           '#type' => 'select', 
           '#options' => array(
             'link' => 'As link', 
             'nolink' => 'Without link'
            ), 
        ), 
      ), 
      'div_plac' => array(
        'name' => t('Family Group: Divorce place'), 
        'sortable' => TRUE, 
        'help' => t('Family Group divorce place'), 
    'handler' => 'family_views_location', 
            'option' => array(
           '#type' => 'select', 
           '#options' => array(
             'link' => 'As link', 
             'nolink' => 'Without link'
            ), 
        ), 
      ), 
      'parent1' => array(
        'name' => t('Family Group: Parent 1'), 
        'sortable' => TRUE, 
        'help' => t('Family Group parent 1'), 
            'option' => array(
           '#type' => 'select', 
           '#options' => array(
             'link' => 'As link', 
             'nolink' => 'Without link'
            ), 
        ), 
    'handler' => 'family_views_parent', 
      ), 
    'parent2' => array(
        'name' => t('Family Group: Parent 2'), 
        'sortable' => TRUE, 
        'help' => t('Family Group parent 2'), 
            'option' => array(
           '#type' => 'select', 
           '#options' => array(
             'link' => 'As link', 
             'nolink' => 'Without link'
            ), 
        ), 
    'handler' => 'family_views_parent', 
      ), 
    ), 
  );
  $tables['family_location'] = array(
  'name' => 'family_location', 
  'join' => array(
   'left' => array(
      'table' => 'node', 
      'field' => 'nid', 
    ), 
    'right' => array(
      'field' => 'nid', 
    ), 
  ), 
  'fields' => array(
      'building' => array(
        'name' => t('Family Location: Building'), 
        'help' => t('Family Location building'), 
    'handler' => 'views_handler_field_nodelink', 
            'option' => array(
           '#type' => 'select', 
           '#options' => array(
             'link' => 'As link', 
             'nolink' => 'Without link'
            ), 
        ), 
      ), 
      'street' => array(
        'name' => t('Family Location: Street'), 
        'help' => t('Family Location street'), 
    'handler' => 'views_handler_field_nodelink', 
                'option' => array(
           '#type' => 'select', 
           '#options' => array(
             'link' => 'As link', 
             'nolink' => 'Without link'
            ), 
        ), 
      ), 
      'city' => array(
        'name' => t('Family Location: City'), 
        'sortable' => TRUE, 
        'help' => t('Family Location city'), 
    'handler' => 'views_handler_field_nodelink', 
            'option' => array(
           '#type' => 'select', 
           '#options' => array(
             'link' => 'As link', 
             'nolink' => 'Without link'
            ), 
        ), 
      ), 
      'county' => array(
        'name' => t('Family Location: County'), 
        'help' => t('Family Location county'), 
    'sortable' => TRUE, 
    'handler' => 'views_handler_field_nodelink', 
            'option' => array(
           '#type' => 'select', 
           '#options' => array(
             'link' => 'As link', 
             'nolink' => 'Without link'
            ), 
        ), 
      ), 
      'state_province' => array(
        'name' => t('Family Location: State/Province'), 
        'sortable' => TRUE, 
    'handler' => 'views_handler_field_nodelink', 
        
        'help' => t('Family Location state or province'), 
            'option' => array(
           '#type' => 'select', 
           '#options' => array(
             'link' => 'As link', 
             'nolink' => 'Without link'
            ), 
        ), 
      ), 
      'country' => array(
        'name' => t('Family Location: Country'), 
        'sortable' => TRUE, 
    'handler' => 'views_handler_field_nodelink', 
        'help' => t('Family Location country'), 
            'option' => array(
           '#type' => 'select', 
           '#options' => array(
             'link' => 'As link', 
             'nolink' => 'Without link'
            ), 
        ), 
      ), 
  ), 
  );
  return $tables;
}
function family_views_location($fieldinfo, $fielddata, $value, $data) {
$value = family_make_location($value, FALSE);
  if ($fielddata['options'] == 'nolink') {
    return check_plain($value);
  }
  return l($value, "node/$data->nid");
}
function family_views_parent($fieldinfo, $fielddata, $value, $data) {

$value= family_make_name($value, FALSE, FALSE);
  if ($fielddata['options'] == 'nolink') {
    return check_plain($value);
  }
  return l($value, "node/$data->nid");
}
function family_views_date($fieldinfo, $fielddata, $value, $data) {

$value= family_check_date($value, $data->nid);
  if ($fielddata['options'] == 'nolink') {
    return check_plain($value);
  }
  return l($value, "node/$data->nid");
}
function family_views_default_views() {

// list individuals
  $view = new stdClass(); 
  $view->name = 'list_indi';
  $view->description = 'List of all individuals';
   $view->access = array('' ); 
   $view->view_args_php = ''; 
   $view->page = TRUE; 
   $view->page_title = 'Individuals List'; 
   $view->page_header = ''; 
   $view->page_header_format = '2'; 
   $view->page_footer = ''; 
   $view->page_footer_format = '2'; 
   $view->page_empty = ''; 
   $view->page_empty_format = '2'; 
   $view->page_type = 'table'; 
   $view->url = 'family/list/indi'; 
   $view->use_pager = TRUE; 
   $view->nodes_per_page = '40'; 
   $view->menu = TRUE; 
   $view->menu_title = 'Family Members Index'; 
   $view->menu_tab = FALSE; 
   $view->menu_tab_weight = '0'; 
   $view->menu_tab_default = FALSE; 
   $view->menu_tab_default_parent = NULL; 
   $view->menu_tab_default_parent_type = 'existing'; 
   $view->menu_parent_tab_weight = '0'; 
   $view->menu_parent_title = 'Family'; 
   $view->sort = array( ); 
   $view->argument = array( ); 
   $view->field = array( 
   array( 
   'tablename' => 'family_individual', 
    'field' => 'lastname', 
    'label' => 'Surname', 
    'sortable' => '1', 
    'defaultsort' => 'ASC', 
    'options' => 'link', 
    ), 
    array(
     'tablename' => 'family_individual', 
     'field' => 'firstname', 
     'label' => 'Forename', 
     'sortable' => '1', 
     'options' => 'link', 
    ), 
    array( 
     'tablename' => 'family_individual', 
     'field' => 'middlename', 
     'label' => 'Middlename(s)', 
     'options' => 'link', 
    ), 
    array(
     'tablename' => 'family_individual', 
     'field' => 'gender', 
     'label' => 'Gender', 
     'options' => 'link', 
    ), 
    array(
     'tablename' => 'family_individual', 
     'field' => 'birthdate', 
     'label' => 'Birth Date', 
     'sortable' => '1', 
     'options' => 'link', 
    ), 
    array( 
     'tablename' => 'family_individual', 
     'field' => 'deathdate', 
     'label' => 'Death Date', 
     'sortable' => '1', 
     'options' => 
     'link', 
    ), 
   ); 
   $view->filter = array(
    array(
     'tablename' => 'node', 
     'field' => 'type', 
     'operator' => 'OR', 
     'options' => '', 
     'value' => array(
      0 => 'family_individual', 
     ), 
    ), 
   ); 
   $view->exposed_filter = array( ); 
   $view->requires = array(family_individual, node); 
   $views[$view->name] = $view; 
  
  //list group
  
  $view = new stdClass(); $view->name = 'list_group'; $view->description = 'List of all groups'; $view->access = array( ); $view->view_args_php = ''; $view->page = TRUE; $view->page_title = 'Groups List'; $view->page_header = ''; $view->page_header_format = '2'; $view->page_footer = ''; $view->page_footer_format = '2'; $view->page_empty = ''; $view->page_empty_format = '2'; $view->page_type = 'table'; $view->url = 'family/list/group'; $view->use_pager = TRUE; $view->nodes_per_page = '40'; $view->menu = TRUE; $view->menu_title = 'Family Groups Index'; $view->menu_tab = FALSE; $view->menu_tab_weight = '0'; $view->menu_tab_default = FALSE; $view->menu_tab_default_parent = NULL; $view->menu_tab_default_parent_type = 'existing'; $view->menu_parent_tab_weight = '0'; $view->menu_parent_title = 'Family'; $view->sort = array( ); $view->argument = array( ); $view->field = array( array( 'tablename' => 'node', 'field' => 'title', 'label' => 'Title', 'handler' => 'views_handler_field_nodelink_with_mark', 'options' => 'link', ), array( 'tablename' => 'family_group', 'field' => 'marr_type', 'label' => 'Marriage Type', 'sortable' => '1', 'options' => 'link', ), array( 'tablename' => 'family_group', 'field' => 'parent1', 'label' => 'Parent 1', 'sortable' => '1', 'options' => 'link', ), array( 'tablename' => 'family_group', 'field' => 'parent2', 'label' => 'Parent 2', 'sortable' => '1', 'options' => 'link', ), ); $view->filter = array( array( 'tablename' => 'node', 'field' => 'type', 'operator' => 'OR', 'options' => '', 'value' => array( 0 => 'family_group', ), ), ); $view->exposed_filter = array( ); $view->requires = array(node, family_group); $views[$view->name] = $view; 
  
  //list locations

  $view = new stdClass(); $view->name = 'list_loca'; $view->description = 'List of all locations'; $view->access = array( ); $view->view_args_php = ''; $view->page = TRUE; $view->page_title = 'Locations List'; $view->page_header = ''; $view->page_header_format = '1'; $view->page_footer = ''; $view->page_footer_format = '1'; $view->page_empty = ''; $view->page_empty_format = '1'; $view->page_type = 'table'; $view->url = 'family/list/location'; $view->use_pager = TRUE; $view->nodes_per_page = '40'; $view->menu = TRUE; $view->menu_title = 'Family Locations Index'; $view->menu_tab = FALSE; $view->menu_tab_weight = '0'; $view->menu_tab_default = FALSE; $view->menu_tab_default_parent = NULL; $view->menu_tab_default_parent_type = 'existing'; $view->menu_parent_tab_weight = '0'; $view->menu_parent_title = 'Family'; $view->sort = array( ); $view->argument = array( ); $view->field = array( array( 'tablename' => 'family_location', 'field' => 'building', 'label' => 'Builing', 'options' => 'link', ), array( 'tablename' => 'family_location', 'field' => 'street', 'label' => 'Street', 'options' => 'link', ), array( 'tablename' => 'family_location', 'field' => 'city', 'label' => 'City', 'sortable' => '1', 'defaultsort' => 'ASC', 'options' => 'link', ), array( 'tablename' => 'family_location', 'field' => 'county', 'label' => 'County', 'sortable' => '1', 'options' => 'link', ), array( 'tablename' => 'family_location', 'field' => 'state_province', 'label' => 'State/Province', 'sortable' => '1', 'options' => 'link', ), array( 'tablename' => 'family_location', 'field' => 'country', 'label' => 'Country', 'sortable' => '1', 'options' => 'link', ), ); $view->filter = array( array( 'tablename' => 'node', 'field' => 'type', 'operator' => 'OR', 'options' => '', 'value' => array( 0 => 'family_location', ), ), ); $view->exposed_filter = array( ); $view->requires = array(family_location, node); $views[$view->name] = $view; 
  
  
  $view = new stdClass();
$view->name = 'family_latest';
$view->description = 'Family Content';
$view->access = array(
0 => '3', 
1 => '1', 
2 => '2', 
);
$view->view_args_php = '';
$view->page = TRUE;
$view->page_title = 'Family Content';
$view->page_header = "
<p>
Welcome to the family area. Here you can view all the data on the website. In the left menu you can choose to view all individuals, groups and locations. To view a family tree, ascendancy or descendancy go to the page of the family member you want to view and click the associated tab along the top menu. If you have more information to add to this family tree you can add it by clicking 'create content' on the side menu or commenting on the page you have information to add to. If you are not sure how to do this please contact the webmaster by clicking the contact link in the menu.
</p>
<p>
&nbsp;
</p>
<h2>
Latest Updates:
</h2>
";
$view->page_header_format = '1';
$view->page_footer = '';
$view->page_footer_format = '1';
$view->page_empty = '';
$view->page_empty_format = '1';
$view->page_type = 'table';
$view->url = 'family';
$view->use_pager = FALSE;
$view->nodes_per_page = '10';
$view->menu = TRUE;
$view->menu_title = 'Family';
$view->menu_tab = FALSE;
$view->menu_tab_weight = '0';
$view->menu_tab_default = FALSE;
$view->menu_tab_default_parent = NULL;
$view->menu_tab_default_parent_type = 'normal';
$view->menu_parent_tab_weight = '0';
$view->menu_parent_title = '';
$view->sort = array(
array(
'tablename' => 'node', 
'field' => 'changed', 
'sortorder' => 'DESC', 
'options' => 'normal', 
), 
);
$view->argument = array(
);
$view->field = array(
array(
'tablename' => 'node', 
'field' => 'title', 
'label' => 'Title', 
'handler' => 'views_handler_field_nodelink_with_mark', 
'options' => 'link', 
), 
array(
'tablename' => 'node', 
'field' => 'changed', 
'label' => 'Last Updated', 
'handler' => 'views_handler_field_since', 
), 
array(
'tablename' => 'node', 
'field' => 'type', 
'label' => 'Type', 
), 
);
$view->filter = array(
array(
'tablename' => 'node', 
'field' => 'type', 
'operator' => 'OR', 
'options' => '', 
'value' => array(
0 => 'family_individual', 
1 => 'family_group', 
2 => 'family_location', 
), 
), 
array(
'tablename' => 'node', 
'field' => 'status', 
'operator' => '=', 
'options' => '', 
'value' => '1', 
), 
);
$view->exposed_filter = array(
);
$view->requires = array(node);
$views[$view->name] = $view;

  return $views;
}
