<?php
/**
 * @file
 * Template file for the POETRY confirmation of receiving translation request.
 *
 * Available custom variables:
 * - $demande_id: An array with requester data.
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
      <statusDate format="dd/mm/yyyy"><?php print date('d/m/Y'); ?></statusDate>
      <statusTime format="hh:mm:ss"><?php print date('H:i:s'); ?></statusTime>
      <statusMessage><?php print $message; ?></statusMessage>
    </status>
  </request>
</POETRY>
