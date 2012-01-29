<?php
// $Id: individual.inc,v 1.7 2010/03/04 13:20:32 jerdiggity Exp $

/**
 * Implementation of hook_access().
 */
function family_individual_access($op, $node, $account) {
  if ($op == 'create' ) {
   return user_access('create family nodes');
  }
  if ($op == 'update' || $op == 'delete') {
    if (user_access('edit own family nodes') && ($user->uid == $node->uid)) {
      return TRUE;
    }
  else {
      return user_access('edit family nodes');
    }
  }
  if ($op == 'view') {
    return family_check_privacy($node->nid);
  }
}

/**
 * Implementation of hook_form().
 */
function family_individual_form(&$node) {
$type = node_get_types('type', $node);

if ($type->has_title) {
  $form['title'] = array(
    '#title' => check_plain($type->title_label), 
    '#type' => 'hidden', 
    '#default_value' => $node->NAME, 
  );
}
  $form['FORE'] = array(
    '#type' => 'textfield', 
    '#title' => t('Forename'), 
    '#default_value' => $node->FORE, 
    '#required' => FALSE, 
  );
    $form['MIDN'] = array(
    '#type' => 'textfield', 
    '#title' => t('Middle Names'), 
    '#default_value' => $node->MIDN, 
    '#required' => FALSE, 
  );
  $form['SURN'] = array(
    '#type' => 'textfield', 
    '#title' => t('Surname'), 
    '#default_value' => $node->SURN, 
    '#required' => FALSE, 
  );
  $form['SEX'] = array(
    '#type' => 'select', 
    '#title' => t('Gender'), 
    '#default_value' => $node->SEX, 
    '#options' => array(
      '?' => 'Unknown', 
      'M' => 'Male', 
      'F' => 'Female'), 
  );
  $ancestorgroups=array();
  $groups=db_query('SELECT nid, title_format FROM {family_group}');
  if ($groups) {
  while ($data = db_fetch_array($groups)) {
  $ancestorgroups[$data['nid']]=$data['title_format'];
  }
  }
  $form['GRUP'] = array(
    '#type' => 'select', 
    '#title' => t('Ancestry Group'), 
    '#default_value' => $node->GRUP, 
    '#options' => array('' => 'None', 'Groups' => $ancestorgroups), 
  );
   $form['BIRT']['BIRT_DATE'] = array(
    '#type' => 'textfield', 
    '#title' => t('Birth Date'), 
    '#description' => t('Year-Month-Day YYYY-MM-DD'), 
    '#default_value' => $node->BIRT_DATE, 
  );
   $form['BIRT']['BIRT_PLAC'] = array(
    '#type' => 'textfield', 
    '#title' => t(' Birth Place'), 
    '#default_value' => $node->BIRT_PLAC, 
  );
   $form['DEAT']['DEAT_DATE'] = array(
    '#type' => 'textfield', 
    '#title' => t('Death Date'), 
    '#description' => t('Year-Month-Day YYYY-MM-DD'), 
    '#default_value' => $node->DEAT_DATE, 
  );
  $form['DEAT']['DEAT_PLAC'] = array(
    '#type' => 'textfield', 
    '#title' => t('Death Place'), 
    '#default_value' => $node->DEAT_PLAC, 
  );
 $form['body_filter']['body_field'] = node_body_field($node, $type->body_label, $type->min_word_count);

  $form['body_filter']['format'] = filter_form($node->format); //Not sure why this goes here, but all the examples have it...
  return $form;
} // function family_individual_form(&$node, &$param)

/**
 * Implementation of hook_insert().
 *  Insert All the facts and relationships
 *  Update Node and revision to replace data not in form
 *
 */
function family_individual_insert($node) {
  $node->title = $node->FORE .' '. $node->SURN;
  db_query("UPDATE {node} SET title='%s' WHERE nid='%d'", $node->title, $node->nid);
  db_query("UPDATE {node_revisions} SET title='%s' WHERE nid='%d' AND vid='%d'", $node->title, $node->nid, $node->vid);
$birthdate=explode("-", $node->BIRT_DATE);
  $node->title_format= (strtoupper($node->SURN)) .', '. ($node->FORE) .' - '. $birthdate[0];
  
  db_query("INSERT INTO {family_individual} (vid, nid, title_format, firstname, middlename, lastname, gender, birthdate, birthplace, deathdate, deathplace, ancestor_group) VALUES (%d, %d, '%s',  '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')", $node->vid, $node->nid, $node->title_format, $node->FORE, $node->MIDN, $node->SURN, $node->SEX, $node->BIRT_DATE, $node->BIRT_PLAC, $node->DEAT_DATE, $node->DEAT_PLAC, $node->GRUP);

  }

/**
 * Implementation of family_individual_load().
 * This function will grab all the descriptive data for an individual
 * Primary use is for filling in form data to preform an edit

 * Returns an array of additions
 */
function family_individual_load($node) {
  $nid = $node->nid;
  $data = db_fetch_array(db_query("SELECT * FROM {family_individual} WHERE nid = %d", $nid));
  $additions->title_format = $data['title_format'];
  //NAME
  $additions->SURN = $data['lastname'];
  $additions->MIDN = $data['middlename'];
  $additions->FORE = $data['firstname'];
  $additions->NAME = $additions->FORE .' '. $additions->SURN;
  //Gender
  $gender = $data['gender'];
  if ($gender) {$additions->SEX = $gender;}
  //BIRTH
  $birt_date = $data['birthdate'];
  if ($birt_date!='0000-00-00 00:00:00') {
      $value=explode(' ', $birt_date);
      $value=$value[0];
      $additions->BIRT_DATE = $value;
  }
  $birt_plac = $data['birthplace'];
  if ($birt_plac) {
    $additions->BIRT_PLAC = $birt_plac;
  }
  //DEATH
  $deat_date = $data['deathdate'];
  if ($deat_date!='0000-00-00 00:00:00') {
      $value=explode(' ', $deat_date);
      $value=$value[0];
      $additions->DEAT_DATE = $value;
  }
  $deat_plac = $data['deathplace'];
  if ($deat_plac) {
    $additions->DEAT_PLAC = $deat_plac;
  }
  $ans_grup = $data['ancestor_group'];
  if ($ans_grup) {
    $additions->GRUP = $ans_grup;
  }
  return ($additions);
}
/**
 * Implementation of hook_update().
 *  Update the facts and new relationships
 *  Update Node and revision to replace data not in form
 *
 *  See family_individual_insert
 */
function family_individual_update($node) {
  $node->title = $node->FORE .' '. $node->SURN;
  db_query("UPDATE {node} SET title='%s' WHERE nid='%d'", $node->title, $node->nid);
  db_query("UPDATE {node_revisions} SET title='%s' WHERE nid='%d' AND vid='%d'", $node->title, $node->nid, $node->vid);
    db_query("UPDATE {node} SET title='%s' WHERE nid='%d'", $node->title, $node->nid);
    $birthdate=explode("-", $node->BIRT_DATE);
  $node->title_format=(strtoupper($node->SURN)) .', '. ($node->FORE) .' - '. $birthdate[0];
  db_query("UPDATE {family_individual} SET vid='%d', title_format='%s', firstname='%s', middlename='%s', lastname='%s', gender='%s', birthdate='%s', birthplace='%s', deathdate='%s', deathplace='%s', ancestor_group='%s' WHERE nid='%d'", 
  $node->vid, $node->title_format, $node->FORE, $node->MIDN, $node->SURN, $node->SEX, $node->BIRT_DATE, $node->BIRT_PLAC, $node->DEAT_DATE, $node->DEAT_PLAC, $node->GRUP, $node->nid);
}

/**
 * Implementation of hook_view().
 */
function family_individual_view(&$node, $teaser = FALSE, $page = FALSE) {
  $node = node_prepare($node, $teaser);
if ($teaser) { 
 $node->content['family_individual_view'] = array(
      '#value' => theme('family_individual_teaser', $node), 
      '#weight' => -1, 
  );
}
  else {
  $node->content['family_individual_view'] = array(
      '#value' => theme('family_individual_body', $node), 
      '#weight' => -1, 
  );
}
  return $node;
}
function family_theme() {
  return array(
    'family_individual_teaser' => array(
      'arguments' => array('node'), 
    ), 
    'family_individual_body' => array(
      'arguments' => array('node'), 
    ), 
    'family_group_teaser' => array(
      'arguments' => array('node'), 
    ), 
    'family_group_body' => array(
      'arguments' => array('node'), 
    ), 
    'family_location_teaser' => array(
      'arguments' => array('node'), 
    ), 
    'family_location_body' => array(
      'arguments' => array('node'), 
    ), 
  );
}
function theme_family_individual_teaser($node) {
$content = family_view_indi($node->nid, '0');
  return $content;
}
function theme_family_individual_body($node) {
$content = family_view_indi($node->nid, '1');
  return $content;
}
/**
 * Implementation of hook_delete().
 */
function family_individual_delete(&$node) {
//  $ind_fid = db_result(db_query("SELECT fid FROM {family_facts} WHERE nid = %d", $node->nid));
  //family_remove_fact($node->nid);
  db_query("DELETE FROM {family_individual} WHERE nid=%d", $node->nid);
}

/**
 * Just so we don't have to keep formatting a name over and over
 */
function family_get_display_name($name) {
    $name_arr['NAME']=$name_arr['GIVN'] .' '. $name_arr['SURN'];
    return $name_arr;
}
