<?php
// Page: FusionMaps.php
// Author: InfoSoft Global (P) Ltd.
// This page contains functions that can be used to render FusionMaps.


// encodeDataURL function encodes the dataURL before it's served to FusionMaps.
// If you've parameters in your dataURL, you necessarily need to encode it.
// Param: $strDataURL - dataURL to be fed to Maps
// Param: $addNoCacheStr - Whether to add aditional string to URL to disable caching of data
function encodeDataURL($strDataURL, $addNoCacheStr=false) {
    //Add the no-cache string if required
    if ($addNoCacheStr==true) {
        // We add ?FCCurrTime=xxyyzz
        // If the dataURL already contains a ?, we add &FCCurrTime=xxyyzz
        // We replace : with _, as FusionMaps cannot handle : in URLs
        if (strpos(strDataURL,"?")<>0)
            $strDataURL .= "&FCCurrTime=" . Date("H_i_s");
        else
            $strDataURL .= "?FCCurrTime=" . Date("H_i_s");
    }
    // URL Encode it
    return urlencode($strDataURL);
}


// datePart function converts MySQL database based on requested mask
// Param: $mask - what part of the date to return "m' for month,"d" for day, and "y" for year
// Param: $dateTimeStr - MySQL date/time format (yyyy-mm-dd HH:ii:ss)
function datePart($mask, $dateTimeStr) {
    @list($datePt, $timePt) = explode(" ", $dateTimeStr);
    $arDatePt = explode("-", $datePt);
    $dataStr = "";
    // Ensure we have 3 parameters for the date
    if (count($arDatePt) == 3) {
        list($year, $month, $day) = $arDatePt;
        // determine the request
        switch ($mask) {
        case "m": return $month;
        case "d": return $day;
        case "y": return $year;
        }
        // default to mm/dd/yyyy
        return (trim($month . "/" . $day . "/" . $year));
    }
    return $dataStr;
}


// renderCharts renders the JavaScript + HTML code required to embed a Maps.
// This function assumes that you've already included the FusionMaps JavaScript class
// in your page.

// $MapsSWF - SWF File Name (and Path) of the Maps which you intend to plot
// $strURL - If you intend to use dataURL method for this Maps, pass the URL as this parameter. Else, set it to "" (in case of dataXML method)
// $strXML - If you intend to use dataXML method for this Maps, pass the XML data as this parameter. Else, set it to "" (in case of dataURL method)
// $MapsId - Id for the Maps, using which it will be recognized in the HTML page. Each Maps on the page needs to have a unique Id.
// $MapsWidth - Intended width for the Maps (in pixels)
// $MapsHeight - Intended height for the Maps (in pixels)
// $debugMode - Whether to start the Maps in debug mode
// $registerWithJS - Whether to ask Maps to register itself with JavaScript
function renderChart($MapsSWF, $strURL, $strXML, $MapsId, $MapsWidth, $MapsHeight, $debugMode, $registerWithJS) {
    //First we create a new DIV for each Maps. We specify the name of DIV as "MapsId"Div.           
    //DIV names are case-sensitive.

    // The Steps in the script block below are:
    //
    //  1)In the DIV the text "Maps" is shown to users before the Maps has started loading
    //    (if there is a lag in relaying SWF from server). This text is also shown to users
    //    who do not have Flash Player installed. You can configure it as per your needs.
    //
    //  2) The Maps is rendered using FusionMaps Class. Each Maps's instance (JavaScript) Id 
    //     is named as Maps_"MapsId".
    //
    //  3) Check whether we've to provide data using dataXML method or dataURL method
    //     save the data for usage below 
    if ($strXML=="")
        $tempData = "//Set the dataURL of the Maps\n\t\tMaps_$MapsId.setDataURL(\"$strURL\");";
    else
        $tempData = "//Provide entire XML data using dataXML method\n\t\tMaps_$MapsId.setXMLData(\"$strXML\");";

    // Set up necessary variables for the RENDERCAHRT
    $MapsIdDiv = $MapsId . "Div";
    $ndebugMode = boolToNum($debugMode);
    $nregisterWithJS = boolToNum($registerWithJS);

    // create a string for outputting by the caller
$render_Maps = <<<renderCharts

    <!-- START Script Block for Maps $MapsId -->
    <div id="$MapsIdDiv" align="center" >
        Maps.
    </div>
    <script type="text/javascript">
        //Instantiate the Maps
        var Maps_$MapsId = new FusionCharts("$MapsSWF", "$MapsId", "$MapsWidth", "$MapsHeight", "$ndebugMode", "$nregisterWithJS");
        $tempData
        //Finally, render the Maps.
        Maps_$MapsId.render("$MapsIdDiv");
    </script>
    <!-- END Script Block for Maps $MapsId -->
renderCharts;

  return $render_Maps;
}


//renderChartsHTML function renders the HTML code for the JavaScript. This
//method does NOT embed the Maps using JavaScript class. Instead, it uses
//direct HTML embedding. So, if you see the Mapss on IE 6 (or above), you'll
//see the "Click to activate..." message on the Maps.
// $MapsSWF - SWF File Name (and Path) of the Maps which you intend to plot
// $strURL - If you intend to use dataURL method for this Maps, pass the URL as this parameter. Else, set it to "" (in case of dataXML method)
// $strXML - If you intend to use dataXML method for this Maps, pass the XML data as this parameter. Else, set it to "" (in case of dataURL method)
// $MapsId - Id for the Maps, using which it will be recognized in the HTML page. Each Maps on the page needs to have a unique Id.
// $MapsWidth - Intended width for the Maps (in pixels)
// $MapsHeight - Intended height for the Maps (in pixels)
// $debugMode - Whether to start the Maps in debug mode
function renderChartsHTML($MapsSWF, $strURL, $strXML, $MapsId, $MapsWidth, $MapsHeight, $debugMode) {
    // Generate the FlashVars string based on whether dataURL has been provided
    // or dataXML.
    $strFlashVars = "&MapsWidth=" . $MapsWidth . "&MapsHeight=" . $MapsHeight . "&debugMode=" . boolToNum($debugMode);
    if ($strXML=="")
        // DataURL Mode
        $strFlashVars .= "&dataURL=" . $strURL;
    else
        //DataXML Mode
        $strFlashVars .= "&dataXML=" . $strXML;

$HTML_Maps = <<<HTMLMaps
    <!-- START Code Block for Maps $MapsId -->
    <object classid="clsid:d27cdb6e-ae6d-11cf-96b8-444553540000" codebase="http://fpdownload.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=8,0,0,0" width="$MapsWidth" height="$MapsHeight" id="$MapsId">
        <param name="allowScriptAccess" value="always" />
        <param name="movie" value="$MapsSWF"/>
        <param name="FlashVars" value="$strFlashVars" />
        <param name="quality" value="high" />
        <embed src="$MapsSWF" FlashVars="$strFlashVars" quality="high" width="$MapsWidth" height="$MapsHeight" name="$MapsId" allowScriptAccess="always" type="application/x-shockwave-flash" pluginspage="http://www.macromedia.com/go/getflashplayer" />
    </object>
    <!-- END Code Block for Maps $MapsId -->
HTMLMaps;

  return $HTML_Maps;
}

// boolToNum function converts boolean values to numeric (1/0)
function boolToNum($bVal) {
    return (($bVal==true) ? 1 : 0);
}

?>