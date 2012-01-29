<?php
// $Id: view.inc,v 1.9 2010/03/04 13:20:32 jerdiggity Exp $

function family_make_location($var, $link=TRUE) {
    if (is_numeric($var)) {
    $location=db_fetch_array(db_query("SELECT * FROM {family_location} WHERE nid=%d", $var));
    $locationname="";
    $start=FALSE;
    if ($location['building']) {
    $start=TRUE;
       $locationname .= $location['building'];
    }
    if ($location['street']) {
    if ($start==TRUE) {
    $locationname .= " ";
    }
    $start=TRUE;
      $locationname .= $location['street'];
    }
    if ($location['city']) {
    if ($start==TRUE) {
    $locationname .= ", ";
    }
    $start=TRUE;
      $locationname .= $location['city'];
    }
    if ($location['county']) {
    if ($start==TRUE) {
    $locationname .= ", ";
    }
    $start=TRUE;
      $locationname .= $location['county'];
    }
    if ($location['state_province']) {
    if ($start==TRUE) {
    $locationname .= ", ";
    }
    $start=TRUE;
      $locationname .= $location['state_province'];
    }
    if ($location['country']) {
    if ($start==TRUE) {
    $locationname .= ", ";
    }
    $start=TRUE;
      $locationname .= $location['country'];
    }
    if ($link==TRUE) {
    $locationname = family_make_link($var, ($locationname));
    }
      return $locationname;
    }
  else {
        return $var;
    }
}


// Generate summary of individual information
function family_summ_indi ($nid) {
  $content="<P>";
  $content .= "<strong>". family_make_name($nid, TRUE) ."</strong>";
  $facts=db_fetch_array(db_query("SELECT * FROM {family_individual} WHERE nid = %d", $nid));
  if ($show_record = TRUE) { //this should check privacy
    if ($facts['gender']) {
      $content .= ", ". $facts['gender'];
    }
    $content .= "<br>";
  }
$content .= "<font size=\"-2\">". l("View Ascendants", "node/". $nid."/tree/asc")."&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;". l("View Descendants", "node/". $nid."/tree/desc")."</font></br>";
//Find parents
  $fam=db_fetch_array(db_query("SELECT parent1, parent2 FROM {family_group} WHERE nid='%s'", $facts['ancestor_group']));
  if ($fam) {
    $father = $fam['parent1'];
    if ($father) {
      $list[] = 'Father: '. family_make_name($father, TRUE);
    }
    $mother = $fam['parent2'];
    if ($mother) {
      $list[] = 'Mother: '. family_make_name($mother, TRUE);
    }
  }
  if ($show_record) {
    if ($facts['birthdate']!='0000-00-00 00:00:00') {
            $value=explode(' ', $facts['birthdate']);
      $value=$value[0];
      $list[] = 'Birth Date: '. $value;
    }
    if ($facts['birthplace']) {

        $list[] = 'Birth Place: '. family_make_location($facts['birthplace']);
    }
    if ($facts['deathdate']!='0000-00-00 00:00:00') {
            $value=explode(' ', $facts['deathdate']);
      $value=$value[0];
      $list[] = 'Death Date: '. $value;
    }
    if ($facts['deathplace']) {
    $list[] = 'Death Place: '. family_make_location($facts['deathplace']);
  }
  }
  $content .= theme('item_list', $list);
  $content .= "</P>";
  return ($content);
}

// Display family view of individual fid (fact id)
function family_view_indi($nid, $type) {
  $content="";
  $content .= family_summ_indi ($nid);

//Find families where the individual is husband or wife
  $families = db_query("SELECT * FROM {family_group} WHERE (parent1='%s' OR parent2='%s')", $nid, $nid);
    if ($families) {
    $list1 = array();
    while ($family = db_fetch_array($families)) {
      
      //Spouse info
      if ($family['parent1'] == $nid) {
        $spouse = $family['parent2'];
      }
      else {
        $spouse = $family['parent1'];
      }
      if ($spouse) {
        $parents=TRUE;
        $content .= "<hr><strong>Spouse: </strong>". family_summ_indi($spouse);
        $spousename = family_make_name($spouse, FALSE);
      }
      else {
        $content .= "<hr><p><strong>Spouse: </strong>Unknown</p>";
        $spousename = "Unknown";
      }
      //Marriage info
$content   .= ' <div class="marriage_data"><p>';
      $content .= family_summ_group($family['nid']);
      $content .= '</p></div>';
      $children = db_query("SELECT * FROM {family_individual} WHERE ancestor_group=%d", $family['nid']);
      //Children info
      if ($children) {
      $content .= '<p>Children of '. family_make_name($nid, FALSE) .' and '. $spousename .':</p>';
      $content .= '<p><table width=100% border=1><tr><td>Name</td><td>Gender</td><td>Birth Date</td><td>Death Date</td></tr>';
      while ($child = db_fetch_array($children)) {
        $content .= "<tr><td>". family_make_name($child['nid'], TRUE)."</td><td>". $child['gender']."</td><td>". $child['birthdate']."</td><td>". $child['deathdate']."</td></tr>";
      }
      $content .= "</table>";
      }
    }
    
  }
  $content .= '<hr />'; //Break before sources, biography, and comments
  
  return ($content);
}
