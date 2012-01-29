<?php
// $Id: group.inc,v 1.5 2010/03/04 13:20:32 jerdiggity Exp $

/**
 * Implementation of hook_access().
 */
function family_group_access($op, $node, $account) {
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
    //return family_check_privacy($node->nid);
    return user_access('access family nodes');
  }
}

/**
* Implementation of hook_form().
*/
function family_group_form(&$node) {
$type = node_get_types('type', $node);

if ($type->has_title) {
  $form['title'] = array(
    '#title' => check_plain($type->title_label), 
    '#type' => 'hidden', 
    '#default_value' => $node->NAME, 
  );
}
  $form['MARR']['MARR_TYPE'] = array(
    '#type' => 'select', 
    '#title' => t('Type of Union'), 
    '#default_value' => $node->MARR_TYPE, 
    '#options' => array(
      'Unmarried' => 'Unmarried', 
      'Religious' => 'Religious', 
    'Common Law' => 'Common Law', 
    'Civil' => 'Civil', 
  ), 
  );
  $form['MARR']['MARR_DATE'] = array(
    '#type' => 'textfield', 
    '#title' => t('Date of Union'), 
    '#description' => t('Year-Month-Day YYYY-MM-DD'), 
    '#default_value' => $node->MARR_DATE, 
  );
  $form['MARR']['MARR_PLAC'] = array(
    '#type' => 'textfield', 
    '#title' => t('Place of Union'), 
    '#default_value' => $node->MARR_PLAC, 
  );
  $form['MARR']['DIV_DATE'] = array(
    '#type' => 'textfield', 
    '#title' => t('Date of Separation'), 
    '#description' => t('Year-Month-Day YYYY-MM-DD'), 
    '#default_value' => $node->DIV_DATE, 
  );
  $form['MARR']['DIV_PLAC'] = array(
    '#type' => 'textfield', 
    '#title' => t('Place of Separation'), 
    '#default_value' => $node->DIV_PLAC, 
  );
  $parents=array();
  $indivs=db_query('SELECT nid, title_format FROM {family_individual}');
  if ($indivs) {
  while ($data = db_fetch_array($indivs)) {
    $parents[$data['nid']]=$data['title_format'];
  }
  }
  $form['PAR1'] = array(
    '#type' => 'select', 
    '#title' => t('Parent 1'), 
  '#description' => t('The parent whose last name is carried by the children .'), 
    '#default_value' => $node->PAR1, 
    '#options' => array('' => 'Unknown', 'Individuals' => $parents), 
  );
  $form['PAR2'] = array(
    '#type' => 'select', 
    '#title' => t('Parent 2'), 
  '#default_value' => $node->PAR2, 
    '#options' => array('' => 'Unknown', 'Individuals' => $parents), 
  );
$form['body_filter']['body_field'] = node_body_field($node, $type->body_label, $type->min_word_count);
  $form['body_filter']['format'] = filter_form($node->format); //Not sure why this goes here, but all the examples have it...
  return $form;
} // function family_group_form(&$node, &$param)

function family_group_insert($node) {
  $parent1first=db_result(db_query("SELECT firstname FROM {family_individual} WHERE nid='%d'", $node->PAR1));
  $parent1last=db_result(db_query("SELECT lastname FROM {family_individual} WHERE nid='%d'", $node->PAR1));
  $parent2=db_result(db_query("SELECT firstname FROM {family_individual} WHERE nid='%d'", $node->PAR2));
  $node->title_format = ($parent1first) .' and '. ($parent2) .' '. ($parent1last);
  $node->title=$node->title_format;
  db_query("UPDATE {node} SET title='%s' WHERE nid='%d'", $node->title, $node->nid);
  db_query("UPDATE {node_revisions} SET title='%s' WHERE nid='%d' AND vid='%d'", $node->title, $node->nid, $node->vid);
  db_query("INSERT INTO {family_group} (vid, nid, title_format, marr_type, marr_date, marr_plac, div_date, div_plac, parent1, parent2) VALUES (%d, %d, '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')", 
  $node->vid, $node->nid, $node->title_format, $node->MARR_TYPE, $node->MARR_DATE, $node->MARR_PLAC, $node->DIV_DATE, $node->DIV_PLAC, $node->PAR1, $node->PAR2);

  }
  function family_group_update($node) {
  $parent1first=db_result(db_query("SELECT firstname FROM {family_individual} WHERE nid='%d'", $node->PAR1));
  $parent1last=db_result(db_query("SELECT lastname FROM {family_individual} WHERE nid='%d'", $node->PAR1));
  $parent2=db_result(db_query("SELECT firstname FROM {family_individual} WHERE nid='%d'", $node->PAR2));
  $node->title_format = ($parent1first) .' and '. ($parent2) .' '. ($parent1last);
  $node->title=$node->title_format;
  db_query("UPDATE {node} SET title='%s' WHERE nid='%d'", $node->title, $node->nid);
 db_query("UPDATE {node_revisions} SET title='%s' WHERE nid='%d' AND vid='%d'", $node->title, $node->nid, $node->vid);
  db_query("UPDATE {family_group} SET vid='%d', title_format='%s', marr_type='%s', marr_date='%s', marr_plac='%s', div_date='%s', div_plac='%s', parent1='%s', parent2='%s' WHERE nid='%d'", 
  $node->vid, $node->title_format, $node->MARR_TYPE, $node->MARR_DATE, $node->MARR_PLAC, $node->DIV_DATE, $node->DIV_PLAC, $node->PAR1, $node->PAR2, $node->nid);

  }
function family_group_load($node) {
  $nid = $node->nid;
  $data = db_fetch_array(db_query("SELECT * FROM {family_group} WHERE nid = %d", $nid));
  $parent1=db_fetch_array(db_query("SELECT firstname, lastname FROM {family_individual} WHERE nid=%d", $node->PAR1));
  $parent2=db_fetch_array(db_query("SELECT firstname FROM {family_individual} WHERE nid=%d", $node->PAR2));
  $additions->NAME = $parent1['firstname'] .' and '. $parent2['firstname'] .' '. $parent1['$lastname'];
  $additions->title_format = $data['title_format'];
  $additions->MARR_TYPE = $data['marr_type'];
  //Marriage data
  if ($data['marr_date']!='0000-00-00 00:00:00') {
      $value=explode(' ', $data['marr_date']);
      $value=$value[0];
      $additions->MARR_DATE = $value;
  }
  $additions->MARR_PLAC = $data['marr_plac'];
  //Divorce data
  if ($data['div_date']!='0000-00-00 00:00:00') {
      $value=explode(' ', $data['div_date']);
      $value=$value[0];
      $additions->DIV_DATE = $value;
  }
  $additions->DIV_PLAC = $data['div_plac'];
  //Parents of the group
  $additions->PAR1 = $data['parent1'];
  $additions->PAR2 = $data['parent2'];
  
  return ($additions);
}  
  function family_group_view(&$node, $teaser = FALSE, $page = FALSE) {
  $node = node_prepare($node, $teaser);
  $node->content['family_group_view'] = array(
      '#value' => theme($teaser? 'family_group_teaser':'family_group_body', $node), 
      '#weight' => -1, 
  );

  return $node;
}
function theme_family_group_teaser($node) {
  return family_view_unison($node->nid, '0');
}
function theme_family_group_body($node) {
  return family_view_unison($node->nid, '1');
}
function family_group_delete(&$node) {
db_query("DELETE FROM {family_group} WHERE nid=%d", $node->nid);
}
function family_summ_group($nid) {
      $family=db_fetch_array(db_query("SELECT * FROM {family_location} WHERE nid='%d'", $nid));
      $list1=array();
      if ($family['marr_type']) {
         $list1[] ='Marriage Type: '. $family['marr_type'];
      }
      if ($family['marr_date']) {
         $list1[] ='Marriage Date: '. $family['marr_date'];
      }
      
      if ($family['marr_plac']) {
        $list1[] ='Marriage Place: '. family_make_location($family['marr_plac']);
      }
      if ($family['div_date']) {
        $list1[] ='Divorce Date: '. $family['div_date'];
      }
      if ($family['div_place']) {
        $list1[] ='Divorce Place: '. family_make_location($family['div_plac']);
      }
    
    return theme('item_list', $list1);

}
function family_view_unison($nid, $type) {
  $content="";
  $content .= family_summ_group ($nid);
  $data=db_fetch_array(db_query("SELECT * FROM {family_group} WHERE nid='%d'", $nid));
  
  //Find children of the family group
  $children = db_query("SELECT * FROM {family_individual} WHERE ancestor_group = %d", $nid);
      if ($children) {
        $content .= '<p>Children of '. family_make_name($data['parent1'], TRUE) .' and '. family_make_name($data['parent2'], TRUE) .':</p>';
      $content .= '<p><table width=100% border=1><tr><td>Name</td><td>Gender</td><td>Birth Date</td><td>Death Date</td></tr>';
      while ($child = db_fetch_array($children)) {
        $content .= "<tr><td>". family_make_name($child['nid'], TRUE)."</td><td>". $child['gender']."</td><td>". $child['birthdate']."</td><td>". $child['deathdate']."</td></tr>";
      }
      $content .= "</table>";
      }
return $content;
}
