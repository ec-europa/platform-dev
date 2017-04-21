<?php
/**
 * @file
 * Template file for the POETRY translation request.
 *
 * @todo add available custom variables
 */
?>
<?xml version="1.0" encoding="utf-8"?>
<POETRY xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
        xsi:noNamespaceSchemaLocation="http://intragate.ec.europa.eu/DGT/poetry_services/poetry.xsd">
    <request communication="asynchrone" id="<?php echo $request_id; ?>" type="newPost">
        <demandeId>
        <?php foreach ($id_data as $item_key => $item): ?>
          <<?php echo $item_key; ?>><?php echo $item; ?></<?php echo $item_key; ?>>
        <?php endforeach; ?>
        </demandeId>
        <demande>
            <userReference>Job ID <?php echo $job->tjid; ?></userReference>
            <titre><?php echo $request_title; ?></titre>
            <organisationResponsable><?php echo $organization['responsable']; ?></organisationResponsable>
            <organisationAuteur><?php echo $organization['auteur']; ?></organisationAuteur>
            <serviceDemandeur><?php echo $organization['demandeur']; ?></serviceDemandeur>
            <applicationReference>FPFIS</applicationReference>
            <delai><?php echo $delai; ?></delai>
            <remarque><?php echo $job->settings['remark']; ?></remarque>
            <referenceFilesNote><?php echo $source_url; ?></referenceFilesNote>
            <procedure id="NEANT"/>
            <destination id="PUBLIC"/>
            <type id="INTER"/>
        </demande>
        <?php foreach ($job->settings['contacts'] as $contact_type => $contact_nickname): ?>
          <contacts type="<?php echo $contact_type; ?>">
            <contactNickname><?php echo $contact_nickname; ?></contactNickname>
          </contacts>
        <?php endforeach; ?>
        <retour type="webService" action="UPDATE">
            <retourUser><?php echo $settings['callback_user']; ?></retourUser>
            <retourPassword><?php echo $settings['callback_password']; ?></retourPassword>
            <retourAddress><?php echo $settings['callback_address']; ?></retourAddress>
            <retourPath><?php echo $settings['callback_path']; ?></retourPath>
            <retourRemark/>
        </retour>
        <documentSource format="HTML">
            <documentSourceName>content.html</documentSourceName>
            <documentSourceLang lgCode="<?php echo $language; ?>">
                <documentSourceLangPages>1</documentSourceLangPages>
            </documentSourceLang>
            <documentSourceFile>
              <?php echo $content; ?>
            </documentSourceFile>
        </documentSource>
        <?php foreach ($request_languages as $item): ?>
          <attributions format="HTML" lgCode="<?php echo $item['lgCode']; ?>" action="<?php echo $item['action']; ?>">
            <attributionsDelai format="DD/MM/YYYY "><?php echo $item['delai']; ?></attributionsDelai>
          </attributions>
        <?php endforeach; ?>
    </request>
</POETRY>
