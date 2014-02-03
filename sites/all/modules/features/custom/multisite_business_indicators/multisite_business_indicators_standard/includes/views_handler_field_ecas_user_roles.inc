<?php

/**
 * @file
 * Definition of views_handler_field_user_roles.
 */

/**
 * Field handler to provide a list of roles.
 *
 * @ingroup views_field_handlers
 */
class views_handler_field_ecas_user_roles extends views_handler_field_prerender_list {
  function construct() {
    parent::construct();
    $this->additional_fields['user_roles'] = array('table' => 'business_indicators_ext_index', 'field' => 'user_roles');
  }

  function query() {
    $this->add_additional_fields();
    $this->field_alias = $this->aliases['user_roles'];
  }

  function pre_render(&$values) {
    $user_roles = array();
    $this->items = array();

    foreach ($values as $result) {
      $user_roles[] = $this->get_value($result, NULL, TRUE);
    }

    if ($user_roles) {
      $result = db_query("SELECT bie.user_roles, r.name
        FROM {role} r
        INNER JOIN {business_indicators_ext_index} bie ON bie.user_roles = r.rid
        WHERE bie.user_roles IN (:user_roles) ORDER BY r.name",
        array(':user_roles' => $user_roles));

      foreach ($result as $role) {
        switch (check_plain($role->user_roles)) {
          case '1':
            $name_role = t('Anonymous User');
          break;
          case '2':
            $name_role = t('Ecas User');
          break;
          case '3':
            $name_role = t('Regular User');
          break;
        }

        $this->items[$role->user_roles][$role->user_roles]['role'] = $name_role;
        $this->items[$role->user_roles][$role->user_roles]['rid'] = $role->user_roles;
      }
    }
  }

  function render_item($count, $item) {
    return $item['role'];
  }

  function document_self_tokens(&$tokens) {
    $tokens['[' . $this->options['id'] . '-role' . ']'] = t('The name of the role.');
    $tokens['[' . $this->options['id'] . '-rid' . ']'] = t('The role ID of the role.');
}

  function add_self_tokens(&$tokens, $item) {
    if (!empty($item['role'])) {
      $tokens['[' . $this->options['id'] . '-role' . ']'] = $item['role'];
      $tokens['[' . $this->options['id'] . '-rid' . ']'] = $item['rid'];
    }
  }
}