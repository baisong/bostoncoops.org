<?php
// $Id: EstimateDates.inc,v 1.7 2010/03/04 13:20:32 jerdiggity Exp $

function family_auto_privacy() {
  $content = t('<p style="text-align: justify;">This will run an algorithm to automatically set privacy.<br/>Generally, the algorithm sets living people and their generation as private. The algorithm tries to evaluate the generation of people, using their own data and data of their relatives. To protect privacy, errors are usually biased for protecting data.<br/>Go to Administer Access control to set which roles may access public or private records.<br/>The results cannot be used to determine if a specific individual is actually living. If you have sensitive data, please check manually that the data is set as private. You should be aware that any database may be hacked and there is no guarantee for your data security<br/>For large files this may take a few minutes.<br/><a href="/admin/settings/family_privacy_done">Start auto privacy</a></p>');
  return $content;
}

/**
 * Decode GEDCOM formatted date field and store it as a range array
 * Currently support only Gregorian dates for years 100-9999
 */
function family_decode_date($date) {
  $range = array( 'MIN' => -99999, 'MAX' => 99999, 'AVG' => 2008, 'VAR'  => 9e9); //Default values
  $date=explode('-', $date);
    if ($date[0]!='0000') {
      $range['AVG']=$date[0];
//      echo $date[0] ."</br>";
      $range['VAR']=0;
      if ($range['AVG']<=100) {
      $range['AVG']=2000;
      }
      return $range;
    }
  return $range;
}

/**
 * Fix range array. Take care of min>max and use information from (min, max) to update (avg, var)
 * and vice versa
 */
function family_fix_range($range) {
  if ($range['VAR']==0) {
    $range['MIN']=$range['AVG'];
    $range['MAX']=$range['AVG'];
  }
  if ($range['MIN'] > $range['MAX']) {
    $range['VAR']=0;
    $range['AVG']=($range['MIN'] + $range['MAX'])/2;
    $range['MAX']=$range['AVG'];
    $range['MIN']=$range['AVG'];
  }
  else {
    if (pow(($range['MAX'] - $range['MIN'])/2, 2)<$range['VAR']) {
      $range['AVG']=($range['MIN'] + $range['MAX'])/2;
      $range['VAR']=pow(($range['MAX'] - $range['MIN'])/2, 2);
    }
  }
  return $range;
}

/**
 * Add two range arrays
 * Used to add offset range between two events to get range of one events, based on the other event
 */
function family_add_ranges($range1, $range2) {
  $range['MIN']=$range1['MIN']+$range2['MIN'];
  $range['MAX']=$range1['MAX']+$range2['MAX'];
  $range['AVG']=$range1['AVG']+$range2['AVG'];
  $range['VAR']=$range1['VAR']+$range2['VAR'];
  $range = family_fix_range($range);
  return $range;
}

/**
 * Merge two range arrays that refer to the same event. It selectss the more accurate data of the two.
 */
function family_merge_ranges($range1, $range2) {
  $range['MIN']=max($range1['MIN'], $range2['MIN']);
  $range['MAX']=min($range1['MAX'], $range2['MAX']);
  if ($range1['VAR']==$range2['VAR']) {
    $range['AVG']=($range1['AVG']+$range2['AVG'])/2;
    $range['VAR']=$range1['VAR'];
  }
  else {
    if ($range1['VAR'] < $range2['VAR']) {
      $range['AVG']=$range1['AVG'];
      $range['VAR']=$range1['VAR'];
    }
    else {
      $range['AVG']=$range2['AVG'];
      $range['VAR']=$range2['VAR'];
    }
  }
  $range = family_fix_range($range);
  return $range;
}

/**
 * Run an estimation algorithm that estimate dates ranges for birth and death events.
 * This is used to determine which records should be private
 */
function family_auto_privacy_done($nid=0) {
  $birth2death = array('MIN' => 0, 'MAX' => 100, 'AVG' => 60, 'VAR' => 1600);
  $death2birth = array('MIN' => -100, 'MAX' => 0, 'AVG' => -60, 'VAR' => 1600);
  $parentbirth2childbirth = array('MIN' => 16, 'MAX' => 56, 'AVG' => 32, 'VAR' => 256);
  $parentdeath2childbirth = array('MIN' => -75, 'MAX' => 0, 'AVG' => -30, 'VAR' => 900);
  $childbirth2parentbirth = array('MIN' => -56, 'MAX' => -16, 'AVG' => -32, 'VAR' => 256);
  $childbirth2parentdeath = array('MIN' => 0, 'MAX' => 75, 'AVG' => 30, 'VAR' => 900);
  $today = getdate();
  $thisyear=$today['year'];
$content .= "START</br>";
//Save the individuals and children queries results to save doing the same query each iteration
  $individuals = db_query("SELECT * FROM {family_individual}");
// Collect Individuals Birth and Death data
   while ($data = db_fetch_array($individuals)) {
     $nid=$data['nid'];
     $date_birth=explode('-', $data['birthdate']);
     
      if ($date_birth[0]!='0000') {
        $birthrange[$nid] = family_fix_range(family_decode_date($data['birthdate']));
        $birthrange[$nid]['MAX'] = min($birthrange[$fid]['MAX'], $thisyear);
      }
      else {
        $birthrange[$nid] = array('MIN' => -99999, 'MAX' => $thisyear, 'AVG' => 2000, 'VAR' => 9e9); //Default values
      }
      $date_death=explode('-', $data['deathdate']);
      if ($date_death[0]!='0000') {
        $deathrange[$nid] = family_fix_range(family_decode_date($data['deathdate']));
      }
      else {
        $deathrange[$nid] = array('MIN' => -99999, 'MAX' => 99999, 'AVG' => 2000, 'VAR' => 9e9); //Default values
      }
    }

  $number_iterations = 8;
  for ($iterations = 0; $iterations < $number_iterations; $iterations++) {
//Compare Death and Birth
    echo "<!-- -->"; //Just send an empy HTML comment to avoid client timeout while waiting
     $individuals = db_query("SELECT nid FROM {family_individual}");
    for ($i = 0; $i < db_num_rows($individuals); $i++) {
      $nid=db_result($individuals, $i);
      $deathrange[$nid] = family_merge_ranges($deathrange[$nid], family_add_ranges($birthrange[$nid], $birth2death));
      $birthrange[$nid] = family_merge_ranges($birthrange[$nid], family_add_ranges($deathrange[$nid], $death2birth));
    }
//Compare parents and children
    $children = db_query("SELECT nid, ancestor_group FROM {family_individual} WHERE (ancestor_group<>'' AND ancestor_group<>'Unknown')");
    while ($child = db_fetch_array($children)) {
      $nid1=$child['nid']; //Child fid
      $fam=$child['ancestor_group']; //Family fid
      $parents = db_fetch_array(db_query("SELECT parent1, parent2 FROM {family_group} WHERE nid=%d", $fam));
      //father
      $nid2=$parents['parent1']; //parent fid
          $birthrange[$nid1] = family_merge_ranges($birthrange[$nid1], family_add_ranges($birthrange[$nid2], $parentbirth2childbirth));
          $birthrange[$nid1] = family_merge_ranges($birthrange[$nid1], family_add_ranges($deathrange[$nid2], $parentdeath2childbirth));
          $birthrange[$nid2] = family_merge_ranges($birthrange[$nid2], family_add_ranges($birthrange[$nid1], $childbirth2parentbirth));
          $deathrange[$nid2] = family_merge_ranges($deathrange[$nid2], family_add_ranges($birthrange[$nid1], $childbirth2parentdeath));
        
        //mother
        $nid2=$parents['parent2']; //parent fid
        
          $birthrange[$nid1] = family_merge_ranges($birthrange[$nid1], family_add_ranges($birthrange[$nid2], $parentbirth2childbirth));
          $birthrange[$nid1] = family_merge_ranges($birthrange[$nid1], family_add_ranges($deathrange[$nid2], $parentdeath2childbirth));
          $birthrange[$nid2] = family_merge_ranges($birthrange[$nid2], family_add_ranges($birthrange[$nid1], $childbirth2parentbirth));
          $deathrange[$nid2] = family_merge_ranges($deathrange[$nid2], family_add_ranges($birthrange[$nid1], $childbirth2parentdeath));
      
    }
  }

// Update privacy information
// Privacy is stored in fact _PRV (family module defined tag)
// 0 or none: Auto (public until estimation is run), 1: Always public (overide auto), 2: Always private (overide auto)
// 3: Public (set by estimation algorithm), 4: Private (set by estimation algorithm) 
  $PrivacyLevel = array( 0 => "Auto", 1 => "Public (Manually)", 2=> "Private (Manually)", 3 => "Public (Auto)", 4=> "Private (Auto)");
  $individuals = db_query("SELECT * FROM {family_individual}");
  while ($data = db_fetch_array($individuals)) {
    $nid=$data['nid'];
    $privacy=0;
//    if ($data['privacy']!='') {
//      $privacy = $data['privacy'];
//    }
//   else {
//    $privacy=0;
//    }
    //if (($privacy==0) || ($privacy==3) || ($privacy==4)) {
       if ((($deathrange[$nid]['MAX']+1000)<=$thisyear) || (($deathrange[$nid]['AVG']+1000)+sqrt($deathrange[$nid]['VAR'])<=$thisyear)) {
         $privacy=3;
       }
       else {
         $privacy=4;
       }
      db_query("UPDATE {family_individual} SET privacy='%d' WHERE nid='%d'", $privacy, $nid);
//      $content .= $privacy ."</br>";
     //}

// Write Estimated dates in Biography, for testing
//    $nid = db_result(db_query("SELECT nid FROM family_facts WHERE fid = %d", $fid));
//    $node=node_load($nid);
//    $content .= "<strong>Estimated Dates (calculated by Family Module)</strong>";
//    $content .= "<ul>Birth:&nbsp;&nbsp;". $birthrange[$nid]['MIN'] ."- ". $birthrange[$nid]['MAX'] ."&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;".  round($birthrange[$nid]['AVG'])."&plusmn;". round(sqrt($birthrange[$nid]['VAR']))."</ul>";
//    $content .= "<ul>Death: ". $deathrange[$nid]['MIN'] ."- ". $deathrange[$nid]['MAX'] ."&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;". round($deathrange[$nid]['AVG']) ."&plusmn;". round(sqrt($deathrange[$nid]['VAR'])) ."</ul>";
//    $content .= "<p>Privacy status: ". $PrivacyLevel[$privacy] ."</p>";
//    $node->body = $content;
//    node_save(&$node);

  }
  $content .= "<p>Done</p>";
  return $content;
}
