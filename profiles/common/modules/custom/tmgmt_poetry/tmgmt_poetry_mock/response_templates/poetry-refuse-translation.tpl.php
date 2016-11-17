<?php
/**
 * @file
 * Template file for the POETRY refuse translation message.
 *
 * Available custom variables:
 * - $demande_id: An array with requester data.
 * - $languages: an array with language codes.
 * - $format: string with attribution format.
 * - $status: job status.
 */
?>
<?php print '<?xml version="1.0" encoding="UTF-8"?>' . PHP_EOL; ?>
<POETRY xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:noNamespaceSchemaLocation="">
  <request communication="synchrone" id="<?php print implode('/', $demande_id); ?>" type="translation">
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
      <statusMessage>OK</statusMessage>
    </status>
    <status code="<?php print $status; ?>" type="demande">
      <statusDate><?php print format_date(time(), 'custom', t('d/m/Y', array(), array('context' => 'php date format'))); ?></statusDate>
      <statusTime><?php print format_date(time(), 'custom', t('H:i:s', array(), array('context' => 'php date format'))); ?></statusTime>
      <statusMessage>I'm refusing. Please send a new request.</statusMessage>
    </status>
  <?php foreach ($languages as $language): ?>
    <status code="<?php print $status; ?>" lgCode="<?php print $language; ?>" type="attribution">
      <statusDate><?php print format_date(time(), 'custom', t('d/m/Y', array(), array('context' => 'php date format'))); ?></statusDate>
      <statusTime><?php print format_date(time(), 'custom', t('H:i:s', array(), array('context' => 'php date format'))); ?></statusTime>
    </status>
  <?php endforeach; ?>
  <?php foreach ($languages as $language): ?>
    <attributions format="<?php print $format ?>" lgCode="<?php print $language; ?>">
      <attributionsDelai><?php print format_date(time(), 'custom', t('d/m/Y H:i:s', array(), array('context' => 'php date format'))); ?></attributionsDelai>
      <attributionsDelaiAccepted></attributionsDelaiAccepted>
    </attributions>
  <?php endforeach; ?>
  </request>
</POETRY>
