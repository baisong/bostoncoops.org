<?php
// $Id: common.inc,v 1.7 2010/03/04 13:20:32 jerdiggity Exp $

function family_changeDateFormat($oldFormat) {
$dateData = explode(" ", $oldFormat);
$day = $dateData[0];
$year = $dateData[2];
switch ($dateData[1]) {
  case "Jan":
  case "jan":
  case "JAN":
     $month = "01";
     break;
  case "feb":
  case "Feb":
  case "FEB":
     $month = "02";
     break;
  case "mar":
  case "Mar":
  case "MAR":
     $month="03";
     break;
  case "apr":
  case "Apr":
  case "APR":
     $month="04";
     break;
  case "may":
  case "May":
  case "MAY":
     $month="05";
     break;
  case "jun":
  case "Jun":
  case "JUN":
     $month="06";
     break;
  case "jul":
  case "Jul":
  case "JUL":
     $month="07";
     break;
  case "aug":
  case "Aug":
  case "AUG":
     $month="08";
     break;
  case "sep":
  case "Sep":
  case "SEP":
     $month="09";
     break;
  case "oct":
  case "Oct":
  case "OCT":
     $month="10";
     break;
  case "nov":
  case "Nov":
  case "NOV":
     $month="11";
     break;
  case "dec":
  case "Dec":
  case "DEC":
     $month="12";
     break;
}
$newDate="$year-$month-$day";
return $newDate;
}

function family_make_link($nid, $text) {
  $output = l($text, "node/$nid");
  return $output;
}
function family_make_name($nid, $link=TRUE, $middle=TRUE)
{
  if ($nid) {
    if (family_check_privacy($nid)) {
      $name = db_fetch_array(db_query("SELECT firstname, middlename, lastname FROM {family_individual} WHERE nid = %d", $nid));
        if ($name) {
            $surname = $name['lastname'];
            $middlename = $name['middlename'];
            $firstname = $name['firstname'];
            if (empty($surname)) {
              $surname = "No data";
            }
            if ((!empty($middlename))&&$middle==TRUE) {
              $middlename .= " ";
            }
            if (empty($firstname)) {
              $firstname = "No data";
            }
       
          $name=$firstname .' '. $middlename.$surname;
        }
  else {
          $name="No data";
        }
            
    if ($link==TRUE) {
    return family_make_link($nid, $name);
    }
  else {
    return $name;
    }
    }
  else {
      return 'Private';
  }
  }
  else {
    return 'No data';
  }
}

function family_check_date($value, $nid) {
  if (family_check_privacy($nid)) {
    if ($value==''||$value=='0000-00-00 00:00:00') {
      $value="None";
    }
  else {
      $value=explode(' ', $value);
      $value=$value[0];
    }
    return $value;
  }
  else {
    return "Private";
  }
  return "Private";
}
