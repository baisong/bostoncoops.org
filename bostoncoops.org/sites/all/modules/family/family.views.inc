<?php
// $Id: family.views.inc,v 1.4 2010/03/04 13:20:32 jerdiggity Exp $

/** 
 * Implementation of hook_views_tables().
 */
function family_views_data() {
  // Define the base group of this table. Fields that don't
  // have a group defined will go into this field by default.
  $data['family_individual']['table']['group']  = t('Family Individual');

  // For other base tables, explain how we join
  $data['family_individual']['table']['join'] = array(
    'node' => array(
      'left_field' => 'nid', 
      'field' => 'nid', 
     ), 
  );
  $data['family_individual']['firstname'] = array(
   'title' => t('Forename'), 
   'help' => t('Family individuals Forename'), 
   'field' => array(
     'handler' => 'views_handler_field_node', 
     'click sortable' => TRUE, 
   ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string', 
      'label' => t('Value'), 
    ), 
   'sort' => array(
    'handler' => 'views_handler_sort', 
   ), 
  );
  $data['family_individual']['middlename'] = array(
   'title' => t('Middlename(s)'), 
   'help' => t('Family individuals Middlename'), 
   'field' => array(
     'handler' => 'views_handler_field_node', 
     'click sortable' => TRUE, 
   ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string', 
      'label' => t('Value'), 
    ), 
   'sort' => array(
    'handler' => 'views_handler_sort', 
   ), 
  );
  $data['family_individual']['lastname'] = array(
   'title' => t('Surname'), 
   'help' => t('Family individuals Surname'), 
   'field' => array(
     'handler' => 'views_handler_field_node', 
     'click sortable' => TRUE, 
   ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string', 
      'label' => t('Value'), 
    ), 
   'sort' => array(
    'handler' => 'views_handler_sort', 
   ), 
  );
  $data['family_individual']['gender'] = array(
   'title' => t('Gender'), 
   'help' => t('Family individuals Gender'), 
   'field' => array(
     'handler' => 'views_handler_field_node', 
     'click sortable' => TRUE, 
   ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string', 
      'label' => t('Value'), 
    ), 
   'sort' => array(
    'handler' => 'views_handler_sort', 
   ), 
  );
  $data['family_individual']['birthdate'] = array(
   'title' => t('Birth Date'), 
   'help' => t('Family individuals Birth Date'), 
   'field' => array(
     'handler' => 'family_views_handler_date', 
     'click sortable' => TRUE, 
   ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string', 
      'label' => t('Value'), 
    ), 
   'sort' => array(
    'handler' => 'views_handler_sort', 
   ), 
  );
  $data['family_individual']['deathdate'] = array(
   'title' => t('Death Date'), 
   'help' => t('Family individuals Death Date'), 
   'field' => array(
     'handler' => 'family_views_handler_date', 
     'click sortable' => TRUE, 
   ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string', 
      'label' => t('Value'), 
    ), 
   'sort' => array(
    'handler' => 'views_handler_sort', 
   ), 
  );
  // Define the base group of this table. Fields that don't
  // have a group defined will go into this field by default.
  $data['family_group']['table']['group']  = t('Family Group');

  // For other base tables, explain how we join
  $data['family_group']['table']['join'] = array(
    'node' => array(
      'left_field' => 'nid', 
      'field' => 'nid', 
     ), 
  );
  $data['family_group']['marr_type'] = array(
   'title' => t('Type'), 
   'help' => t('Family group Type'), 
   'field' => array(
     'handler' => 'views_handler_field_node', 
     'click sortable' => TRUE, 
   ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string', 
      'label' => t('Value'), 
    ), 
   'sort' => array(
    'handler' => 'views_handler_sort', 
   ), 
  );
  $data['family_group']['marr_date'] = array(
   'title' => t('Marriage Date'), 
   'help' => t('Family group marriage date'), 
   'field' => array(
     'handler' => 'family_views_handler_date', 
     'click sortable' => TRUE, 
   ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string', 
      'label' => t('Value'), 
    ), 
   'sort' => array(
    'handler' => 'views_handler_sort', 
   ), 
  );
  $data['family_group']['marr_plac'] = array(
   'title' => t('Marriage Place'), 
   'help' => t('Family group Marriage Place'), 
   'field' => array(
     'handler' => 'family_views_handler_location', 
     'click sortable' => TRUE, 
   ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string', 
      'label' => t('Value'), 
    ), 
   'sort' => array(
    'handler' => 'views_handler_sort', 
   ), 
  );
  $data['family_group']['div_date'] = array(
   'title' => t('Divorce Date'), 
   'help' => t('Family group divorce date'), 
   'field' => array(
     'handler' => 'family_views_handler_date', 
     'click sortable' => TRUE, 
   ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string', 
      'label' => t('Value'), 
    ), 
   'sort' => array(
    'handler' => 'views_handler_sort', 
   ), 
  );
  $data['family_group']['div_plac'] = array(
   'title' => t('Divorce Place'), 
   'help' => t('Family group divorce place'), 
   'field' => array(
     'handler' => 'family_views_handler_location', 
     'click sortable' => TRUE, 
   ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string', 
      'label' => t('Value'), 
    ), 
   'sort' => array(
    'handler' => 'views_handler_sort', 
   ), 
  );
  $data['family_group']['parent1'] = array(
   'title' => t('Parent 1'), 
   'help' => t('Family group parent 1'), 
   'field' => array(
     'handler' => 'family_views_handler_parent', 
     'click sortable' => TRUE, 
   ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string', 
      'label' => t('Value'), 
    ), 
   'sort' => array(
    'handler' => 'views_handler_sort', 
   ), 
  );
  $data['family_group']['parent2'] = array(
   'title' => t('Parent 2'), 
   'help' => t('Family group parent 2'), 
   'field' => array(
     'handler' => 'family_views_handler_parent', 
     'click sortable' => TRUE, 
   ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string', 
      'label' => t('Value'), 
    ), 
   'sort' => array(
    'handler' => 'views_handler_sort', 
   ), 
  );
  // Define the base group of this table. Fields that don't
  // have a group defined will go into this field by default.
  $data['family_location']['table']['group']  = t('Family Location');

  // For other base tables, explain how we join
  $data['family_location']['table']['join'] = array(
    'node' => array(
      'left_field' => 'nid', 
      'field' => 'nid', 
     ), 
  );
  $data['family_location']['building'] = array(
   'title' => t('Building'), 
   'help' => t('Family location building'), 
   'field' => array(
     'handler' => 'views_handler_field_node', 
     'click sortable' => TRUE, 
   ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string', 
      'label' => t('Value'), 
    ), 
   'sort' => array(
    'handler' => 'views_handler_sort', 
   ), 
  );
  $data['family_location']['street'] = array(
   'title' => t('Street'), 
   'help' => t('Family location street'), 
   'field' => array(
     'handler' => 'views_handler_field_node', 
     'click sortable' => TRUE, 
   ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string', 
      'label' => t('Value'), 
    ), 
   'sort' => array(
    'handler' => 'views_handler_sort', 
   ), 
  );
  $data['family_location']['city'] = array(
   'title' => t('City'), 
   'help' => t('Family location city'), 
   'field' => array(
     'handler' => 'views_handler_field_node', 
     'click sortable' => TRUE, 
   ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string', 
      'label' => t('Value'), 
    ), 
   'sort' => array(
    'handler' => 'views_handler_sort', 
   ), 
  );
  $data['family_location']['county'] = array(
   'title' => t('County'), 
   'help' => t('Family location county'), 
   'field' => array(
     'handler' => 'views_handler_field_node', 
     'click sortable' => TRUE, 
   ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string', 
      'label' => t('Value'), 
    ), 
   'sort' => array(
    'handler' => 'views_handler_sort', 
   ), 
  );
  $data['family_location']['state_province'] = array(
   'title' => t('State/Province'), 
   'help' => t('Family location state or province'), 
   'field' => array(
     'handler' => 'views_handler_field_node', 
     'click sortable' => TRUE, 
   ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string', 
      'label' => t('Value'), 
    ), 
   'sort' => array(
    'handler' => 'views_handler_sort', 
   ), 
  );
  $data['family_location']['country'] = array(
   'title' => t('Country'), 
   'help' => t('Family location country'), 
   'field' => array(
     'handler' => 'views_handler_field_node', 
     'click sortable' => TRUE, 
   ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string', 
      'label' => t('Value'), 
    ), 
   'sort' => array(
    'handler' => 'views_handler_sort', 
   ), 
  );

  return $data;
}

function family_views_handlers() {
  return array(
    'handlers' => array(
       'family_views_handler_date' => array(
        'parent' => 'views_handler_field', 
        'path' => drupal_get_path('module', 'family') .'/views', 
      ), 
       'family_views_handler_location' => array(
        'parent' => 'views_handler_field', 
        'path' => drupal_get_path('module', 'family') .'/views', 
      ), 
       'family_views_handler_parent' => array(
        'parent' => 'views_handler_field', 
        'path' => drupal_get_path('module', 'family') .'/views', 
      ), 
    ), 
  );
}
