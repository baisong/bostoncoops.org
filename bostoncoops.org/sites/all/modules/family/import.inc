<?php
// $Id: import.inc,v 1.10 2010/03/04 13:20:32 jerdiggity Exp $

/**
 * @file
 * Functions for importing GEDCOM files to database
 * Using the data base defined in simple.mysql
 * This may also be used as a temporary storage before making more processing
 * for import to other database format.
 * @wtf
 * This comment.
 */

//Generate a form for uploading a GEDCOM file
function family_import() {
$content='';
//$content  .= ' Import_view';
$content .= drupal_get_form('family_import_form');
return $content;
}

function family_import_form() {
  $form['#attributes'] = array('enctype' => "multipart/form-data");
  $form['gedcom_file'] = array(
    '#type' => 'file', 
    '#title' => t('GED file to upload'), 
    '#size' => 40, 
  );
  //$form['merge'] = array(
  //  '#type' => 'radios', 
  //  '#title' => t('Merge options'), 
  //  '#options' => array(t('replace existing data'), t('augment current data'), t('merge individuals by name')), 
  //  '#default_value' => variable_get('family_import_replace', 1), 
  //);

  $form['range'] = array(
    '#type' => 'fieldset', 
    '#title' => t('Import range'), 
    '#description' => t('Select a range of records (lines staring with 0) to import.  This allows breaking very large files into multiple import sessions .'), 
  );
  $form['range']['start'] = array(
    '#type' => 'textfield', 
    '#title' => t('First record to import'), 
    '#size' => 10, 
    '#maxlength' => 10, 
    '#description' => t('Enter the number of the first record in the GEDCOM file to include in this import session'), 
  );
  $form['range']['nrecords'] = array(
    '#type' => 'textfield', 
    '#title' => t('Number of records to import'), 
    '#size' => 10, 
    '#maxlength' => 10, 
    '#description' => t('Enter the number of records to process in this import session'), 
  );
  $form['replace'] = array(
    '#type' => 'checkbox', 
    '#title' => t('Replace existing GED data'), 
    '#default_value' => variable_get('family_import_replace', 1), 
  );
  $form['submit'] = array('#type' => 'submit', '#value' => t('Start Import'));
  $form['#submit'] = array('family_import_submit');
  return $form;
}

// Check the uploaded GEDCOM file
function family_import_submit($form, &$form_state) {
  if (!($file = file_save_upload('gedcom_file'))) {
    form_set_error('', t("Didn't get GED file"));
  }
  else {
  if (!($fp = fopen($file->filepath , "r"))) {
    form_set_error('', t("Couldn't open get GED file"));
  }
  else {

  
  //
  // Empty current content. This is useful for debugging, but more caution should be
  // done before deleting database in the working version
  //
db_query("CREATE TABLE {family_relations_temp} (`nid` VARCHAR( 128 ) NOT NULL , `famc_xref` VARCHAR( 128 ) NOT NULL , `fams_xref` VARCHAR( 128 ) NOT NULL) ENGINE = MYISAM");
if ($form['replace']) {
    db_query("TRUNCATE {family_individual}");
    db_query("TRUNCATE {family_group}");
    db_query("TRUNCATE {family_location}");
    db_query("TRUNCATE {family_variable}");

    
    $q = db_query("SELECT nid FROM {node} WHERE type = 'family_individual'");
    $n = 0;
    while ($o = db_fetch_array($q)) {
      node_delete($o->nid);
      $n++;
    }
    drupal_set_message(t('Deleted @n family_individual nodes .', array('@n' => $n)));
    
    $q = db_query("SELECT nid FROM {node} WHERE type = 'family_group'");
    $n = 0;
    while ($o = db_fetch_array($q)) {
      node_delete($o->nid);
      $n++;
    }
    drupal_set_message(t('Deleted @n family_group nodes .', array('@n' => $n)));
    
  $q = db_query("SELECT nid FROM {node} WHERE type = 'family_location'");
    $n = 0;
    while ($o = db_fetch_array($q)) {
      node_delete($o->nid);
      $n++;
    }
    drupal_set_message(t('Deleted @n family_location nodes .', array('@n' => $n))); 
  }

  $rmin = $form['start']? $form['start']:0;
  $rcount = $form['nrecords']? $form['nrecords']:99999999;
  $rmax = $rmin + $rcount - 1;
  $rnum = 0;
  $rprocessed = 0;
  $lprocessed = 0;
  
  $lnum = 0;
  $gedcom_hier=array();   // References to GEDCOM parents on each level
  
  //declare variables for evaluation
  $current0record = NULL;
  
  while (!feof ($fp))
  {
    $gedline = fgets( $fp, 1024 );
    $lnum++;
    
    if (preg_match("/^\s*(\d+)\s*(?:@([^@]+)@)?\s*(\S+)\s*(.*\S)?\s*$/i", $gedline , $matches)) {
      $level=$matches[1];
      if ($level == 0) ++$rnum;
      if ($rnum < $rmin) continue;
      if ($rnum > $rmax) break;
      if ($level == 0) ++$rprocessed;
      ++$lprocessed;
      $xref=$matches[2];
      $fact_code=$matches[3];
      $value=$matches[4];
      $gedcom_source=$gedline;
      $parent=$gedcom_hier[$level-1];

    //new ged file evaluation code
    //next line is debug
    //echo $level . "<br>";
    switch ($level) {
      case '0':
      $current0xref = $xref;
      $current0record = $fact_code;
      //next line is debug
      //echo $current0record . "<br>";
      switch ($current0record) {
        case 'INDI':
        //create title_format variable that has not yet been set.
        $title_format = $firstname . " " . $middlename . " " . $lastname; //Will change with the implementation of tokens.
        //next line is debug
          //echo $title_format . "<br>";
        //Create family_individual node
        unset($node);
              $node->type = family_individual;
              $node->uid = $user->uid;
              $node->title = $title_format;
              $node->status = 1;
              $node->moderate = 0;
              $node->comment = 2;
              $node->revision = 0;
              node_validate($node, $error);
              if (!node_access("create", $node)) {
                $error['access'] = message_access();
              }
              if ($error) {
                 drupal_set_message(
                  t('Error at line @lnum of GED (@line): @error .', 
            array('@lnum' => $lnum, '@line' => $gedline, '@error' => print_r($error, TRUE))
                  )
        );
              }
              else {
                $node->title=$title_format;
                $node->FORE=$firstname;
                $node->MIDN=$middlename;
                $node->SURN=$lastname;
                $node->SEX=$gender;
                $node->BIRT_DATE=$birthdate;
                $node->BIRT_PLAC=$birthplace;
                $node->DEAT_DATE=$deathdate;
                $node->DEAT_PLAC=$deathplace;
                node_save($node);
                $nid=$node->nid;
        //Insert relationship variables into temporary database
        db_query("INSERT INTO {family_relations_temp} (nid, famc_xref, fams_xref) VALUES (%d, '%s', '%s')", $nid, $famc_xref, $fams_xref);
          //next line is debug
              }
              unset($node);
        //unset all INDI variables
        unset($famc_xref);
        unset($fams_xref);
        unset($vid);
        unset($nid);
        unset($title_format);
        unset($firstname);
        unset($middlename);
        unset($lastname);
        unset($gender);
        unset($birthdate);
        unset($birthplace);
        unset($deathdate);
        unset($deathplace);
        unset($children_num);
      break;
      case 'FAM':
        //Find the group surname shared by the children of the group. - This may be incorrect in cases where the name has not been passed to the children.
                    $current0xref='@'. $current0xref .'@';
        $result = db_query("SELECT r.lastname FROM {family_individual} r INNER JOIN {family_relations_temp} t ON r.nid=t.nid WHERE t.famc_xref = '%s'", $current0xref);
        $group_surname = db_fetch_object($result);
                    //Debug Line Below
                    //drupal_set_message(t('FAM XREF @n', array('@n' => $current0xref))); 

        //Find Parents of group
        $result = db_query("SELECT nid FROM {family_relations_temp} WHERE fams_xref = '%s'", $current0xref);
                    while ($parent = db_fetch_array($result)) {
                      //Debug Line Below
                      //drupal_set_message(t('PARENT NID @n', array('@n' => $parent['nid'])));
          $parents[] = $parent['nid'];
                    }
                    $parent1 = $parents[0];
                    $parent2 = $parents[1];

        //create group node
        unset($node);
              $node->type = family_group;
              $node->uid = $user->uid;
              $node->title = $title_format;
              $node->status = 1;
              $node->moderate = 0;
              $node->comment = 2;
              $node->revision = 0;
              node_validate($node, $error);
              if (!node_access("create", $node)) {
                $error['access'] = message_access();
              }
              if ($error) {
                 drupal_set_message(
                  t('Error at line @lnum of GED (@line): @error .', 
            array('@lnum' => $lnum, '@line' => $gedline, '@error' => print_r($error, TRUE))
                  )
        );
              }
              else {
                $node->title=$title_format;
                $node->MARR_TYPE=$marr_type;
                $node->MARR_DATE=$marr_date;
                $node->MARR_PLAC=$marr_plac;
                $node->DIV_DATE=$div_date;
                $node->DIV_PLAC=$div_plac;
                $node->PAR1=$parent1;
                $node->PAR2=$parent2;
                node_save($node);
                $nid=$node->nid;
        //insert ancestor group value into INDI nodes related to this group
        //db_query("UPDATE {family_individual} SET ancestor_group='%d' WHERE lastname='%s'", $nid, $group_surname);
        //insert variables into family_group table
        //db_query("INSERT INTO {family_group} (vid, nid, title_format, marr_type, marr_date, marr_plac, div_date, div_plac, parent1, parent2) VALUES (%d, %d, '%s', '%s', '%s', '%s', '%s', '%s', '%d', '%d')", $vid, $nid, $title_format, $marr_type, $marr_date, $marr_plac, $div_date, $div_plac, $parent1, $parent2);
        //unset all FAM variables
            $result = db_query("SELECT nid FROM {family_relations_temp} WHERE famc_xref = '%s'", $current0xref);
                while ($child = db_fetch_array($result)) {
                  //Debug Line Below
                  //drupal_set_message(t('CHILD NID @n', array('@n' => $child['nid'])));
      $childnid = $child['nid'];
                  db_query("UPDATE {family_individual} SET ancestor_group = %d WHERE nid =%d", $nid, $childnid);
                }
              }
                 unset($node);
        unset($current0xref);
        unset($child_ref_nid);
        unset($group_surname);
        unset($parent_surname);
        unset($parent1_firstname);
        unset($parent2_firstname);
        unset($vid);
        unset($nid);
        unset($title_format);
        unset($marr_type);
        unset($marr_date);
        unset($marr_plac);
        unset($div_date);
        unset($div_plac);
        unset($parent1);
        unset($parent2);
                    unset($parents);
          break;
      }
      $current0record = NULL;
      //next line is debug
      //echo $fact_code . "<br>";
      switch ($fact_code) {
        case 'FAM':
      case 'INDI':
        $current0record = $fact_code;
        $current0xref = $xref;
      break;
      }  
    break;
    case '1':
      $current1record = $fact_code;
      //next line is debug
      //echo $current0record . "<br>";
      switch ($current0record) {
        case 'INDI':
        //next line is debug
          //echo $fact_code . "<br>";
        switch ($fact_code) {
          case 'SEX':
          $gender = $value;
          $current1record = $fact_code;
        break;
        case 'NCHI':
          $children_num = $value;
          $current1record = $fact_code;
        break;
        case 'NAME':
          //split name value by / to separate surname
          $splitName1 = explode("/", $value);
          $lastname = $splitName1[1];
          // split name by spaces
          $splitName2 = explode(" ", $splitName1[0]);
          // take the first name to be firstname
          $firstname = $splitName2[0];
          // add all the other names together in a string
          $middlename = $splitName2[1] . " " . $splitName2[2] . " " . $splitName2[3] . " " . $splitName2[4] . " " . $splitName2[5] . " " . $splitName2[6] . " " . $splitName2[7];
          $current1record = $fact_code;
        break;
        case 'DEAT':
        case 'BIRT':
          $current1record = $fact_code;
        break;
        case 'FAMS':
          $fams_xref = $value;
        break;
        case 'FAMC':
          $famc_xref = $value;
        break;
        }
      break;
      case 'FAM':
        //next line is debug
          //echo $fact_code . "<br>";
        switch ($fact_code) {
          case 'MARR':
        case 'DIV':
          $current1record = $fact_code;
        break;
        }
      break;
      }
    break;
    case '2':
      $current2record = $fact_code;
      //next line is debug
      //echo $current1record . "<br>";
      switch ($current1record) {
        case 'BIRT':
        //next line is debug
          //echo $fact_code . "<br>";
        switch ($fact_code) {
          case 'DATE':
          $birthdate = family_changeDateFormat($value);
        break;
        case 'PLAC':
          $birthplace = $value;
        break;
        }
      break;
      case 'DEAT':
        //next line is debug
          //echo $fact_code . "<br>";
        switch ($fact_code) {
          case 'DATE':
          $deathdate = family_changeDateFormat($value);
        break;
        case 'PLAC':
          $deathplace = $value;
        break;
        }
      break;
      case 'MARR':
        //next line is debug
          //echo $fact_code . "<br>";
        switch ($fact_code) {
          case 'TYPE':
          $marr_type = $value;
        break;
        case 'DATE':
          $marr_date = family_changeDateFormat($value);
        break;
        case 'PLAC':
          $marr_plac = $value;
        break;
        }
      break;
      case 'DIV':
        //next line is debug
          //echo $fact_code . "<br>";
        switch ($fact_code) {
          case 'DATE':
          $div_date = family_changeDateFormat($value);
        break;
        case 'PLAC':
          $div_plac = $value;
        break;
        }
      break;
      }
    break;
    }
  }
  }

  fclose ($fp);
  db_query("DROP TABLE {family_relations_temp}");  
  drupal_set_message(t('Processed @r records (@n lines) of GED .', array('@r' => $rprocessed, '@n' => $lprocessed)));
  if ($rnum > $rmax) drupal_set_message(t('Next start record: @r .', array('@r' => $rmax + 1)));
  else drupal_set_message(t('No more records to process'));

}}
  return;
}

