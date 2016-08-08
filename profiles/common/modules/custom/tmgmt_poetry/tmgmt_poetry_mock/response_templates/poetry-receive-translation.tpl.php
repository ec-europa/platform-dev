<?php
/**
 * @file
 * Template file for the POETRY receive translation message.
 *
 * Available custom variables:
 * - $demande_id: An array with requester data.
 * - $content: String which contains translated content.
 * - $language: string with language code.
 * - $format: string with attribution format.
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
    <attributions format="<?php print $format; ?>" lgCode="<?php print $language; ?>">
      <attributionsFile>
        <?php print $content; ?>
      </attributionsFile>
    </attributions>
  </request>
</POETRY>
