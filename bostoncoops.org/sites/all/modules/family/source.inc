<?php
// $Id: source.inc,v 1.5 2010/03/04 13:20:32 jerdiggity Exp $

/**
 * Implementation of hook_access().
 */
function family_source_access($op, $node) {
  if ($op == 'create' || $op == 'update' || $op == 'delete') {
    return user_access('add/edit/delete family');
  }
  if ($op == 'view') {
    return family_check_privacy($node->fid);
  }
}

/**
 * Implementation of hook_view().
 */
function family_source_view(&$node, $teaser = FALSE, $page = FALSE) {
  $node = node_prepare($node, $teaser);
//  $fid = db_result(db_query("SELECT fid FROM {family_facts} WHERE nid= %d", $node->nid));
//  $node->body = family_view_indi($node->fid) . $node->body;
//  $node->teaser = family_view_indi($node->fid) . $node->teaser;
  $node->content['family_individual_view'] = array(
      '#value' => theme($teaser? 'family_source_teaser':'family_source_body', $node), 
      '#weight' => 0, 
  );

  return $node;
}

function theme_family_source_teaser($node) {
  return family_view_source($node->fid);
}
function theme_family_source_body($node) {
  return family_view_source($node->fid);
}
/*
 * Implements showing sources. (NOT source citations, they use the same code (SOUR), but
 * sourcecs have xrefs, citations don't, and a slightly different structure.
 * See family_view_citation)
 */
function family_view_source($fid = 0) {
  if (func_num_args() == 0) {
    return "<p><em>We are sorry, but you did not enter the Fact Id for a know source.</em></p>";
  }
    $content="";
//Display all source data
  $fact = family_get_fact_by_fid($fid);
  $subfacts = family_get_subfacts($fid);
  if ($sour_titl = $subfacts['TITL'][0]['value']) {$content .= "<h1>$sour_titl</h1>";}
  if ($sour_abbr = $subfacts['ABBR'][0]['value']) {$content .= "Source Title:$sour_abbr<br />";}
  if ($sour_auth = $subfacts['AUTH'][0]['value']) {
    $content .= "Authority: $sour_auth". family_get_cont($subfacts['AUTH'][0]['fid'])."<br />";
  }
  if ($sour_publ = $subfacts['PUBL'][0]['value']) {
    $content .= "Publisher: $sour_publ". family_get_cont($subfacts['PUBL'][0]['fid'])."<br />";
  }
  if ($sour_data = $subfacts['DATA'][0]['value']) {
    $datafacts = family_get_subfacts($subfacts['DATA'][0]['fid']);
    if ($data_date = $datafacts['DATE'][0]['value']) {
      $content .= "Date: $data_date <br />";
    }
    if ($datafacts['EVEN']) {
      $content .= "Events recorded: <ul>";
      foreach ($datafacts['EVEN'] as $iter => $even_arr) {
        $content .= "<li>". $even_arr['value'];
        if ($evenfacts = family_get_subfacts($even_arr['fid'])) {
          $fact_arr = array("Places: ". $evenfacts['PLAC'][0]['value'], 
                            "Dates: " .$evenfacts['DATE'][0]['value'] );
          $content = implode('<br />', $fact_arr);
        }
        $content  .= "</li>";
      }
      $content .= "</ul>";
    }
    if ($data_agnc = $datafacts['AGNC'][0]['value']) {$content .= "Responsible Agency:$data_agnc<br />";}
    if ($datafacts['NOTE']) {
      $content .= '<p>Notes: ';
      foreach ($subfacts['NOTE'] as $idx => $note) {
        $content .= '<p>'. $note['value'].family_get_cont($note['fid']) .'</p>';
    }
    $content .= '</p>';
  }
  }
  if ($subfacts['NOTE']) {
    $content .= '<p>Notes: ';
    foreach ($subfacts['NOTE'] as $idx => $note) {
        $content .= '<p>'. $note['value'].family_get_cont($note['fid']) .'</p>';
    }
    $content .= '</p>';
  }
  $content .= '<hr />'; //Break before citation listings
/*
 * TODO: Find all linking source citations and list them each within types:
 *         INDI, FAM, NOTE (Never seen this on a root level...), REPO, SUBM, SUBN
 *       This probably requires each supporte type to have a view option to link to.
 */
//
  $seen_fids = array();
  $indi_header = array(
    'Surname', 
    'Given Name', 
    'Sex', 
    'Birth Date', 
    //'Birth Place', 
    'Death Date', 
    //'Death Place'
  );
  $indi_facts = array();
  $fam_header = array(
    'Husband', 
    'Wife', 
    'Date', 
    'Place'
  );
  $fam_facts = array();
  $citations = db_query("SELECT fid, nid, xref, fact_code AS code, fact_value AS value "
          .  "FROM {family_facts} "
          .  "WHERE fact_value = '%s' ", '@'. $fact['xref'] .'@');
  while ($citation = db_fetch_array($citations)) {
    $root = family_get_fact_root($citation['fid']);
    if ($seen_fids[$root['fid']]) { continue; } //Kinda Perlish, I know, but it works.
    else { $seen_fids[$root['fid']] = TRUE; }
    if (strcmp($root['fact_code'], "INDI") == 0) {
      $subfacts = family_get_subfacts($root['fid']);
      $birthfacts = family_get_subfacts($subfacts['BIRT'][0]['fid']);
      $deathfacts = family_get_subfacts($subfacts['DEAT'][0]['fid']);
      $name = $subfacts['NAME'][0]['value'];
        $name_arr = family_get_display_name($name);
      $indi_facts[$root['fid']] = array(
          'SURN' => l(  $name_arr['SURN'], "node/". $root['nid']), 
          'GIVN' => l(  $name_arr['GIVN'], "node/". $root['nid']), 
          'SEX'  => l(  $subfacts['SEX' ][0]['value'], "node/". $root['nid']), 
          'BIRTD' => l($birthfacts['DATE' ][0]['value'], "node/". $root['nid']), 
          //'BIRTP' => family_make_link($fid, $birthfacts['PLAC']['value']), 
          'DEATD' => l($deathfacts['DATE' ][0]['value'], "node/". $root['nid']), 
          //'DEATP' => family_make_link($fid, $deathfacts['PLAC']['value'])
        );
    }
    elseif (strcmp($root['fact_code'], "FAM") == 0) {
      $subfacts = family_get_subfacts($root['fid']);
      $marr_facts = family_get_subfacts($subfacts['MARR'][0]['fid']);
      $couple = family_get_fam_by_famid($root['fid'], array('HUSB', 'WIFE'));
      $couple_husb = family_get_subfacts($couple['HUSB'][0]['fid']);
      $couple_wife = family_get_subfacts($couple['WIFE'][0]['fid']);
      $husb_name = family_get_display_name($couple_husb['NAME'][0]['value']);
      $wife_name = family_get_display_name($couple_wife['NAME'][0]['value']);
      $fam_facts[$root['fid']] = array(
        'HUSB' => l($husb_name['NAME'], "node/". $couple['HUSB'][0]['nid']), 
        'WIFE' => l($wife_name['NAME'], "node/". $couple['WIFE'][0]['nid']), 
        'DATE' => $marr_facts['DATE'][0]['value'], 
        'PLAC' => $marr_facts['PLAC'][0]['value']
      );
    }
  }
  $content .= '<div class="sources-listing">'
           .  "<h3>Individuals with Citations from this Source:</h3>"
           .  '<div class="family-index">'. theme('table', $indi_header, $indi_facts) .'</div>'
           .  "<h3>Families with Citations from this Source:</h3>"
           .  '<div class="family-index">'. theme('table', $fam_header, $fam_facts) .'</div>'
           .  '</div>';
  return ($content);
}

function family_view_source_short($fid) {
  $content="";
  //Display all source data
  $subfacts = family_get_subfacts($fid);
  //Order of display preference decending (we want the abbreviated title if we can)
  $title = 'No Title';
  if ($subfacts['TITL']) {
    $title = $subfacts['TITL'][0]['value'];
  }
  if ($subfacts['ABBR']) {
    $title = $subfacts['ABBR'][0]['value'];
  }
  $content .= $title;
  if ($sour_publ = $subfacts['PUBL'][0]['value']) {
    $content .= "(<i>$sour_publ". family_get_cont($subfacts['PUBL'][0]['fid'])."</i>)";
  }
  return ($content);
}

function family_view_repository($fid) {
  $rep_fact = family_get_fact_by_fid($fid);
  $subfacts = family_get_subfacts($fid);

  $content .= '<h3>'. $subfacts['NAME'][0]['value'] .'</h3>';

  if ($subfacts['ADDR']) {
    $content .= '<p>'. family_get_address($subfacts['ADDR'][0]) . '</p>';
  }

  if ($subfacts['PHON']) {
    $content .= "<p>Phone: <ol>";
    foreach ($subfacts['PHON'] as $idx => $phone) {
      $content .= '<li>'. $phone['value'] .'</li>';
    }
    $content .= "</ol></p>";
  }
  if ($subfacts['EMAIL']) {
    $content .= "<p><ol>";
    foreach ($subfacts['EMAIL'] as $idx => $email) {
      $content .= '<li>'. $email['value'] .'</li>';
    }
    $content .= "</ol></p>";
  }
  if ($subfacts['FAX']) {
    $content .= "<p>Fax: <ol>";
    foreach ($subfacts['FAX'] as $idx => $fax) {
      $content .= '<li>'. $fax['value'] .'</li>';
    }
    $content .= "</ol></p>";
  }
  if ($subfacts['WWW']) {
    $content .= "<p><ol>";
    foreach ($subfacts['WWW'] as $idx => $www) {
      $content .= '<li><a href="'. $www['value'] .'">'. $www['value'] .'</a></li>';
    }
    $content .= "</ol></p>";
  }
  if ($subfacts['NOTE']) {
    $content .= '<p>Notes: ';
    foreach ($subfacts['NOTE'] as $idx => $note) {
        $content .= '<p>'. $note['value'].family_get_cont($note['fid']) .'</p>';
    }
    $content .= '</p>';
  }
}

function family_view_repository_short($fid) {
  $rep_fact = family_get_fact_by_fid($fid);
  if ($rep_fact['nid'] > 0) {
    $link_path = "node/". $rep_fact['nid'];
  }
  else {
    $link_path = "family/view/repository/". $rep_fact['fid'];
  }
  return l(family_get_subvalue_by_code('NAME', $fid), $link_path);
}

function family_view_repository_citation($fid) {
  if (func_num_args() == 0) {
    return "<em>We are sorry, but you did not enter the Fact Id for a know repository citation.</em>";
  }
  elseif (func_num_args() > 1) { //Second value passed could be the xref pointer
    $xref = func_get_arg(1);   //to the owning repository.
  }
  else {
    $xref = family_get_value_by_fid($fid);
  }
  $subfacts = family_get_subfacts($fid);
  $repo_fact = family_get_fact_by_xref($xref);

  //Link to the source being cited
  if ($repo_fact['nid'] > 0) { //I don't know if this case will ever appear, but just in case...
    $link_path = "node/". $repo_fact['nid'];
  }
  else {
    $link_path = "family/view/source/". $repo_fact['fid'];
  }
  $content .= "<h3>". l(family_view_source_short($repo_fact['fid']), $link_path)."</h3>";

  //Display all repository citation data

  if ($subfacts['NOTE']) {
    $content .= '<p>Notes: ';
    foreach ($subfacts['NOTE'] as $idx => $note) {
      $content .= '<p>'. $note['value'].family_get_cont($note['fid']) .'</p>';
    }
    $content .= '</p>';
  }
  if ($subfacts['CALN']) {
    $content .= '<p>Call Number(s): <ul>';
    foreach ($subfacts['CALN'] as $idx => $caln) {
        $content .= '<li>'. $caln['value'];
        if ($media_fact = family_get_subfact_by_code('MEDI', $caln['fid']) ) {
          $content .= ', ('. $media_fact['value'] .')';
        }
        $content .= '</li>';
    }
    $content .= '</ul></p>';
  }

  return ($content);
}

function family_view_citation($fid) {
  if (func_num_args() == 0) {
    return "<em>We are sorry, but you did not enter the Fact Id for a know citation.</em>";
  }
  elseif (func_num_args() > 1) { //Second value passed could be the xref pointer
    $xref = func_get_arg(1);   //to the source being cited.
  }
  else {
    $xref = family_get_value_by_fid($fid);
  }
  $subfacts = family_get_subfacts($fid);
  $sour_fact = family_get_fact_by_xref($xref);

  //Link to the source being cited
  if ($sour_fact['nid'] > 0) { //I don't know if this case will ever appear, but just in case...
    $link_path = "node/". $sour_fact['nid'];
  }
  else {
    $link_path = "family/view/source/". $sour_fact['fid'];
  }
  $content .= "<h3>". l(family_view_source_short($sour_fact['fid']), $link_path)."</h3>";

  //Display all citation data
  if ($sour_page = $subfacts['PAGE'][0]['value']) {$content .= ", pg(s) $sour_page<br />";}
  if ($sour_even = $subfacts['EVEN'][0]['value']) {
    $content .= "Event Type: $sour_even";
    if ($even_role = family_get_subvalue_by_code('ROLE', $subfacts['EVEN'][0]['fid'])) {
      $content .= ", $even_role<br />";
    }
  }
  if ($subfacts['DATA']) {
    $datafacts = family_get_subfacts($subfacts['DATA'][0]['fid']);
    if ($data_date = $datafacts['DATE'][0]['value']) {
      $content .= "Date: $data_date <br />";
    }
    if ($data_text = $datafacts['TEXT'][0]['value']) {
      $content .= "Text from source: $data_text"
               .  family_get_cont($datafacts['TEXT'][0]['fid'])."<br />";
    }
  }
  if ($sour_quay = $subfacts['QUAY'][0]['value']) {$content .= "Quality Assesment: $sour_quay<br />";}
  if ($subfacts['NOTE']) {
    $content .= '<p>Notes: ';
    foreach ($subfacts['NOTE'] as $idx => $note) {
        $content .= '<p>'. $note['value'].family_get_cont($note['fid']) .'</p>';
    }
    $content .= '</p>';
  }

  return ($content);
}

function family_view_citation_short($fid) {
  $subfacts = family_get_subfacts($fid);
  if (func_num_args() > 1) {
    $xref = func_get_arg(1);
  }
  else {
    $xref = family_get_value_by_fid($fid);
  }
  $sour_fact = family_get_fact_by_xref($xref);
  //Display all citation data
  if ($sour_fact['nid'] > 0) { //I don't know if this case will ever appear, but just in case...
    $link_path = "node/". $sour_fact['nid'];
  }
  else {
    $link_path = "family/view/source/". $sour_fact['fid'];
  }
  $content .= family_view_source_short($sour_fact['fid']);
  if ($subfacts['PAGE']) {
    $content .= ", pg(s) ". $subfacts['PAGE'][0]['value'];
  }

  return ($content);
}

/**
 * Implementation of family_source_load().
 * This function will grab all the descriptive data for an individual
 * Primary use is for filling in form data to preform an edit
 * [Code mostly taken from family_individual_load() & family_view_source()]
 *
 * Returns an array of additions, following convention of individual load
 */
function family_source_load($fid) {
  $additions->fid = $fid;

  return ($additions);
}
