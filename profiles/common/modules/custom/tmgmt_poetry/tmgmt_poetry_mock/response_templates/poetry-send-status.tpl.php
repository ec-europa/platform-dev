<?php
/**
 * @file
 * Template file for the POETRY send status message.
 *
 * Available custom variables:
 * - $demande_id: An array with requester data.
 * - $languages: an array with language codes.
 * - $format: string with attribution format.
 * - $status_code: job status.
 * - $request_status_msg: request status message.
 * - $demande_status_msg: 'demande' status message.
 * - $lg_code: language code.
 */
?>
<?php print '<?xml version="1.0" encoding="UTF-8"?>' . PHP_EOL; ?>
<POETRY xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:noNamespaceSchemaLocation="">
  <request communication="synchrone" id="<?php print rand(1000000, 9999999); ?>" type="status">
    <demandeId>
      <codeDemandeur><?php print $demande_id['codeDemandeur']; ?></codeDemandeur>
      <annee><?php print $demande_id['annee']; ?></annee>
      <numero><?php print $demande_id['numero']; ?></numero>
      <version><?php print $demande_id['version']; ?></version>
      <partie><?php print $demande_id['partie']; ?></partie>
      <produit><?php print $demande_id['produit']; ?></produit>
    </demandeId>
    <status code="0" type="request">
      <statusDate><?php print format_date(time(), 'custom', t('d/m/Y', array(), array('context' => 'php date format'))); ?></statusDate>
      <statusTime><?php print format_date(time(), 'custom', t('H:i:s', array(), array('context' => 'php date format'))); ?></statusTime>
      <statusMessage><?php print $request_status_msg; ?></statusMessage>
    </status>
    <status code="<?php print $status_code; ?>" type="demande">
      <statusDate><?php print format_date(time(), 'custom', t('d/m/Y', array(), array('context' => 'php date format'))); ?></statusDate>
      <statusTime><?php print format_date(time(), 'custom', t('H:i:s', array(), array('context' => 'php date format'))); ?></statusTime>
      <statusMessage><?php print $demande_status_msg; ?></statusMessage>
    </status>
    <status code="<?php print $status_code; ?>" lgCode="<?php print $lg_code; ?>" type="attribution">
      <statusDate><?php print format_date(time(), 'custom', t('d/m/Y', array(), array('context' => 'php date format'))); ?></statusDate>
      <statusTime><?php print format_date(time(), 'custom', t('H:i:s', array(), array('context' => 'php date format'))); ?></statusTime>
    </status>
    <attributions format="<?php print $format ?>" lgCode="<?php print $lg_code; ?>">
      <attributionsDelai><?php print format_date(time(), 'custom', t('d/m/Y H:i:s', array(), array('context' => 'php date format'))); ?></attributionsDelai>
      <attributionsDelaiAccepted/>
    </attributions>
  </request>
</POETRY>
