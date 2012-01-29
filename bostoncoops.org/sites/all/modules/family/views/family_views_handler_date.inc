<?php
// $Id: family_views_handler_date.inc,v 1.4 2010/03/04 13:20:32 jerdiggity Exp $

class family_views_handler_date extends views_handler_field {
  function render($values) {
    $value = $values->{$this->field_alias};
    $value = family_check_date($value,$values->nid);
    return check_plain($value);
  }
}