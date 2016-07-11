<?php

/**
 * @file
 * Context reaction.
 */

/**
 * Reaction for the context.
 */
class NexteuropaNewsroomAgendaReaction extends context_reaction {

  /**
   * Provides options_form.
   *
   * @param array $context
   *   Context array.
   *
   * @return array
   *   Form array.
   */
  // @codingStandardsIgnoreLine
  public function options_form($context) {
    $values = $this->fetch_from_context($context);
    $form['type_id'] = array(
      '#type' => 'select',
      '#title' => t('Type'),
      '#options' => NewsroomHelper::getNewsroomTypeOptions(TRUE),
      '#default_value' => $values,
    );

    return $form;
  }

  /**
   * We need a definition for this function but is not required.
   */
  public function execute() {

  }

}
