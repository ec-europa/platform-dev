<?php
/**
 * @file
 * Template file for the POETRY mock about receiving wrong translation request.
 *
 * Available custom variables:
 * - $demande_id: An array with requester data.
 * - $message: A string with the error message.
 */
?>
<POETRY xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:noNamespaceSchemaLocation="">
  <request communication="asynchrone" id="<?php print implode('/', $demande_id); ?>" type="status">
    <demandeId>
      <codeDemandeur><?php print $demande_id['codeDemandeur']; ?></codeDemandeur>
      <annee><?php print $demande_id['annee']; ?></annee>
      <numero><?php print $demande_id['numero']; ?></numero>
      <version><?php print $demande_id['version']; ?></version>
      <partie><?php print $demande_id['partie']; ?></partie>
      <produit><?php print $demande_id['produit']; ?></produit>
    </demandeId>
    <status code="-1" type="request">
      <statusDate format="dd/mm/yyyy"><?php print format_date(time(), 'custom', t('d/m/Y', array(), array('context' => 'php date format'))); ?></statusDate>
      <statusTime format="hh:mm:ss"><?php print format_date(time(), 'custom', t('H:i:s', array(), array('context' => 'php date format'))); ?></statusTime>
      <statusMessage><?php print $message; ?></statusMessage>
    </status>
  </request>
</POETRY>
