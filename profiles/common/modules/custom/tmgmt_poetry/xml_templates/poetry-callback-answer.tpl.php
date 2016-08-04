<?php
/**
 * @file
 * Template file for the POETRY confirmation of receiving translation request.
 *
 * Available custom variables:
 * - $demande_id: An array with requester data.
 * - $code: A code integer.
 * - $message: A string which contains message.
 */
?>
<?php print '<?xml version="1.0" encoding="UTF-8"?>' . PHP_EOL; ?>
<POETRY xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:noNamespaceSchemaLocation="http://intragate.ec.europa.eu/DGT/poetry_services/poetry.xsd">
  <request id="<?php print implode('/', $demande_id); ?>" type="status">
    <demandeId>
      <codeDemandeur><?php print $demande_id['codeDemandeur']; ?></codeDemandeur>
      <annee><?php print $demande_id['annee']; ?></annee>
      <numero><?php print $demande_id['numero']; ?></numero>
      <version><?php print $demande_id['version']; ?></version>
      <partie><?php print $demande_id['partie']; ?></partie>
      <produit><?php print $demande_id['produit']; ?></produit>
    </demandeId>
    <status type="request" code="<?php print $code; ?>">
      <statusDate format="dd/mm/yyyy"><?php print date('d/m/Y'); ?></statusDate>
      <statusTime format="hh:mm:ss"><?php print date('H:i:s'); ?></statusTime>
      <statusMessage><?php print $message; ?></statusMessage>
    </status>
  </request>
</POETRY>
