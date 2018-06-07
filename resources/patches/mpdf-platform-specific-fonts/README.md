==========================================================
 mpdf-platform-specific-fonts "patch" 
 https://webgate.ec.europa.eu/CITnet/jira/browse/NEPT-1259
==========================================================
 
From the 6.1.4 release, the mdpf package includes a lot of fonts useless for 
the Platform purposes and make the package heavy: around 105 MB compared with
the 22 MB of the previous version 5.7.4.

In order to reduce the size of the mpdf package inside the platform, 
the "ttfonts" folder present in this repository contains all fonts supplied by 
the version 5.7.4.

It replaces the corresponding folder of the current mpdf version 
in the platform package in order to keep only the fonts supported so far by the 
platform.

This replacement occurs during the build of the platform environment ("build-platform-dev" phing target) and of 
the platform package ("build-multisite-dist" phing target).
