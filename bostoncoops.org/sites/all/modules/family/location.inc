<?php
// $Id: location.inc,v 1.5 2010/03/04 13:20:32 jerdiggity Exp $

/**
 * Implementation of hook_access().
 */
function family_location_access($op, $node, $account) {
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
function family_location_form(&$node) {
$type = node_get_types('type', $node);

if ($type->has_title) {
  $form['title'] = array(
    '#title' => check_plain($type->title_label), 
    '#type' => 'hidden', 
    '#default_value' => $node->NAME, 
  );
}
  $form['BUILD'] = array(
    '#type' => 'textfield', 
    '#title' => t('Building'), 
  '#default_value' => $node->BUILD, 
    '#required' => FALSE, 
  );
    $form['STREET'] = array(
    '#type' => 'textfield', 
    '#title' => t('Street'), 
    '#default_value' => $node->STREET, 
    '#required' => FALSE, 
  );
  $form['CITY'] = array(
    '#type' => 'textfield', 
    '#title' => t('City'), 
    '#default_value' => $node->CITY, 
    '#required' => FALSE, 
  );
  $form['COUNTY'] = array(
    '#type' => 'textfield', 
    '#title' => t('County'), 
    '#default_value' => $node->COUNTY, 
  '#required' => FALSE, 
  );
  $form['STATE_PROV'] = array(
    '#type' => 'textfield', 
    '#title' => t('State or Province'), 
    '#default_value' => $node->STATE_PROV, 
  '#required' => FALSE, 
   );
   $form['COUNTRY'] = array(
    '#type' => 'textfield', 
    '#title' => t('Country'), 
    '#default_value' => $node->COUNTRY, 
  '#required' => FALSE, 
  );
  $ancestorgroups=array();
  $groups=db_query('SELECT nid, title_format FROM {family_group}');
  while ($data = db_fetch_array($groups)) {
  $ancestorgroups[$data['nid']]=$data['title_format'];
  }
  $form['GRUP'] = array(
    '#type' => 'select', 
    '#title' => t('Ancestry Group'), 
    '#default_value' => $node->GRUP, 
    '#options' => array('' => 'None', 'Groups' => $ancestorgroups), 
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
function family_location_insert($node) {
if ($node->BUILD||$node->STREET) {
$node->title = $node->BUILD." ". $node->STREET;
}
  elseif ($node->CITY) {
$node->title = $node->CITY;
}
  elseif ($node->COUNTY) {
$node->title = $node->COUNTY;
}
  elseif ($node->STATE_PROV) {
$node->title = $node->STATE_PROV;
}
  else {
$node->title = $node->COUNTRY;
}
  db_query("UPDATE {node} SET title='%s' WHERE nid='%d'", $node->title, $node->nid);
  db_query("UPDATE {node_revisions} SET title='%s' WHERE nid='%d' AND vid='%d'", $node->title, $node->nid, $node->vid);
  $node->title_format= $node->BUILD;
  db_query("INSERT INTO {family_location} (vid, nid, title_format, building, street, city, county, state_province, country, related_group) VALUES (%d, %d, '%s',  '%s', '%s', '%s', '%s', '%s', '%s', %d)", 
  $node->vid, $node->nid, $node->title_format, $node->BUILD, $node->STREET, $node->CITY, $node->COUNTY, $node->STATE_PROV, $node->COUNTRY, $node->GRUP);

  }

/**
 * Implementation of family_individual_load().
 * This function will grab all the descriptive data for an individual
 * Primary use is for filling in form data to preform an edit

 * Returns an array of additions
 */
function family_location_load($node) {
  $nid = $node->nid;
  $data = db_fetch_array(db_query("SELECT * FROM {family_location} WHERE nid = %d", $nid));
  $additions->title_format = $data['title_format'];
  $additions->NAME = $data['title_format'];
  //Address
  $additions->BUILD = $data['building'];
  $additions->STREET = $data['street'];
  $additions->CITY = $data['city'];
  $additions->COUNTY = $data['county'];
  $additions->STATE_PROV = $data['state_province'];
  $additions->COUNTRY = $data['country'];
$additions->GRUP = $data['related_group'];
  return ($additions);
}
/**
 * Implementation of hook_update().
 *  Update the facts and new relationships
 *  Update Node and revision to replace data not in form
 *
 *  See family_individual_insert
 */
function family_location_update($node) {
if ($node->BUILD||$node->STREET) {
$node->title = $node->BUILD." ". $node->STREET;
}
  elseif ($node->CITY) {
$node->title = $node->CITY;
}
  elseif ($node->COUNTY) {
$node->title = $node->COUNTY;
}
  elseif ($node->STATE_PROV) {
$node->title = $node->STATE_PROV;
}
  else {
$node->title = $node->COUNTRY;
}

  db_query("UPDATE {node} SET title='%s' WHERE nid='%d'", $node->title, $node->nid);
  db_query("UPDATE {node_revisions} SET title='%s' WHERE nid='%d' AND vid='%d'", $node->title, $node->nid, $node->vid);
  $node->title_format= $node->BUILD;
  db_query("UPDATE {family_location} SET vid='%d', title_format='%s', building='%s', street='%s', city='%s', county='%s', state_province='%s', country='%s', related_group='%d' WHERE nid='%d'", 
 $node->vid, $node->title_format, $node->BUILD, $node->STREET, $node->CITY, $node->COUNTY, $node->STATE_PROV, $node->COUNTRY, $node->GRUP, $node->nid);

}

/**
 * Implementation of hook_view().
 */
function family_location_view(&$node, $teaser = FALSE, $page = FALSE) {
  $node = node_prepare($node, $teaser);
//  $fid = db_result(db_query("SELECT fid FROM {family_facts} WHERE nid= %d", $node->nid));
//  $node->body = family_view_indi($node->fid) . $node->body;
//  $node->teaser = family_view_indi($node->fid) . $node->teaser;
  $node->content['family_location_view'] = array(
      '#value' => theme($teaser? 'family_location_teaser':'family_location_body', $node), 
      '#weight' => -1, 
  );

  return $node;
}
function theme_family_location_teaser($node) {
  return family_view_loca($node->nid, '0');
}
function theme_family_location_body($node) {
  return family_view_loca($node->nid, '1');
}
/**
 * Implementation of hook_delete().
 */
function family_location_delete(&$node) {
//  $ind_fid = db_result(db_query("SELECT fid FROM {family_facts} WHERE nid = %d", $node->nid));
  //family_remove_fact($node->nid);
  db_query("DELETE FROM {family_location} WHERE nid=%d", $node->nid);
}

function family_view_loca($nid, $type) {
$data = db_fetch_array(db_query("SELECT * FROM {family_location} WHERE nid = %d", $nid));
$content .= "<strong>". family_make_link($node->nid, ($data['building']." ". $data['street'])) ."</strong><br>";
$list=array();
$list[] = 'Building : '. $data['building'];
$list[] = 'Street : '. $data['street'];
$list[] = 'City : '. $data['city'];
$list[] = 'County : '. $data['county'];
$list[] = 'State/Province : '. $data['state_province'];
$list[] = 'Country : '. $data['country'];
  $content .= theme('item_list', $list);
  $content .= "</P><p>&nbsp;</p>";
 //Asociated group
  $asocid = $data['related_group'];
        if ($asocid) {
        $content .= '<p>Family group asociated with here:</br>';
      $content .= '<table width=100% border=1><tr><td>Name</td><td>Gender</td><td>Birth Date</td></tr>';
      $fam=db_fetch_array(db_query("SELECT parent1, parent2 FROM {family_group} WHERE nid='%s'", $asocid));
  $asoc= db_query("SELECT * FROM {family_individual} WHERE nid=%d OR nid=%d OR ancestor_group=%d", $fam['parent1'], $fam['parent2'], $asocid);
  while ($child = db_fetch_array($asoc)) {
        $content .= "<tr><td>". family_make_name($child['nid'], TRUE)."</td><td>". $child['gender']."</td><td>". $child['birthdate']."</td></tr>";
      }
      $content .= "</table>";
      }
 //Born here
  $born = db_query("SELECT * FROM {family_individual} WHERE birthplace=%d", $nid);
      if ($born) {
        $content .= '<p>Individuals born here:</br>';
      $content .= '<table width=100% border=1><tr><td>Name</td><td>Gender</td><td>Birth Date</td></tr>';
      while ($child = db_fetch_array($born)) {
        $content .= "<tr><td>". family_make_name($child['nid'], TRUE)."</td><td>". $child['gender']."</td><td>". $child['birthdate']."</td></tr>";
      }
      $content .= "</table>";
      }
 //died here
  $death = db_query("SELECT * FROM {family_individual} WHERE deathplace=%d", $nid);
      if ($death) {
        $content .= '<p>Individuals died here:</br>';
      $content .= '<table width=100% border=1><tr><td>Name</td><td>Gender</td><td>Death Date</td></tr>';
      while ($child = db_fetch_array($death)) {
        $content .= "<tr><td>". family_make_name($child['nid'], TRUE)."</td><td>". $child['gender']."</td><td>". $child['deathdate']."</td></tr>";
      }
      $content .= "</table>";
      }
  //married here
  $marr = db_query("SELECT * FROM {family_group} WHERE marr_plac=%d", $nid);
      if ($marr) {
        $content .= '<p>Groups married here:</br>';
      $content .= '<table width=100% border=1><tr><td>Name</td><td>Marriage Date</td></tr>';
      while ($child = db_fetch_array($marr)) {
        $content .= "<tr><td>". $child['title_format']."</td><td>". $child['marr_date']."</td></tr>";
      }
      $content .= "</table>";
      }         
  //Divorced here
  $div = db_query("SELECT * FROM {family_group} WHERE div_plac=%d", $nid);
      if ($div) {
        $content .= '<p>Groups divorced here:</br>';
      $content .= '<table width=100% border=1><tr><td>Name</td><td>Divorce Date</td></tr>';
      while ($child = db_fetch_array($div)) {
        $content .= "<tr><td>". $child['title_format']."</td><td>". $child['div_date']."</td></tr>";
      }
      $content .= "</table>";
      }    
return $content;
}
