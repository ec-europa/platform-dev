<?php
/**
 * @file
 * communities.features.content.inc
 */

/**
 * Implements hook_content_defaults().
 */
function communities_content_defaults() {
$content = array();
$content['first community'] = (object)array(
  'title' => 'my first community',
  'status' => '1',
  'promote' => '0',
  'sticky' => '0',
  'type' => 'community',
  'language' => 'en',
  'created' => '1327420321',
  'comment' => '2',
  'translate' => '0',
  'machine_name' => 'first community',
  'body' => array(
    'und' => array(
      0 => array(
        'value' => '<p>This is a example community.</p>
',
        'summary' => '',
        'format' => 'filtered_html',
        'safe_value' => '<p>This is a example community.</p>
',
        'safe_summary' => '',
      ),
    ),
  ),
  'field_thumbnail' => array(
    'und' => array(
      0 => array(
        'alt' => NULL,
        'title' => NULL,
        'width' => '310',
        'height' => '205',
        'filename' => 'aaa.jpg',
        'uri' => 'public://aaa.jpg',
        'filemime' => 'image/jpeg',
        'filesize' => '8756',
        'status' => '1',
        'type' => 'image',
        'uuid' => 'f767439a-705b-2ea4-6d57-e895c5195c70',
        'rdf_mapping' => array(),
        'image' => 'ÿØÿà' . "\0" . 'JFIF' . "\0" . '' . "\0" . '' . "\0" . '' . "\0" . '' . "\0" . '' . "\0" . 'ÿþ' . "\0" . ';CREATOR: gd-jpeg v1.0 (using IJG JPEG v62), quality = 75
ÿÛ' . "\0" . 'C' . "\0" . '		

 $.\' ",#(7),01444\'9=82<.342ÿÛ' . "\0" . 'C			

2!!22222222222222222222222222222222222222222222222222ÿÀ' . "\0" . '' . "\0" . 'Í6"' . "\0" . 'ÿÄ' . "\0" . '' . "\0" . '' . "\0" . '' . "\0" . '' . "\0" . '' . "\0" . '' . "\0" . '' . "\0" . '' . "\0" . '' . "\0" . '' . "\0" . '	
ÿÄ' . "\0" . 'µ' . "\0" . '' . "\0" . '' . "\0" . '}' . "\0" . '!1AQa"q2‘¡#B±ÁRÑð$3br‚	
%&\'()*456789:CDEFGHIJSTUVWXYZcdefghijstuvwxyzƒ„…†‡ˆ‰Š’“”•–—˜™š¢£¤¥¦§¨©ª²³´µ¶·¸¹ºÂÃÄÅÆÇÈÉÊÒÓÔÕÖ×ØÙÚáâãäåæçèéêñòóôõö÷øùúÿÄ' . "\0" . '' . "\0" . '' . "\0" . '' . "\0" . '' . "\0" . '' . "\0" . '' . "\0" . '' . "\0" . '	
ÿÄ' . "\0" . 'µ' . "\0" . '' . "\0" . 'w' . "\0" . '!1AQaq"2B‘¡±Á	#3RðbrÑ
$4á%ñ&\'()*56789:CDEFGHIJSTUVWXYZcdefghijstuvwxyz‚ƒ„…†‡ˆ‰Š’“”•–—˜™š¢£¤¥¦§¨©ª²³´µ¶·¸¹ºÂÃÄÅÆÇÈÉÊÒÓÔÕÖ×ØÙÚâãäåæçèéêòóôõö÷øùúÿÚ' . "\0" . '' . "\0" . '' . "\0" . '?' . "\0" . 'áÕ•22(H|‘ŠèBÄëÚ ’Ù{WÐ´xÄvëÀ«Xãº"¸ÜknÚ+G;:ç©‰=Ó:!‡sÙ˜ÅÒ-£Ìqfº¨´ËIz(5§i§Á' . "\0" . 'Â¨¯/Äj1z;ö:©å•$õzwu§M,„Z¨¥z•ÖŸñTW7qá´	Òžˆ0Õãy¾VŒ²¤¹ª9= Ž”ž@=EuN´·?>3ïP\\›0„.Ì×§tjÊÐM®ç3Á8«É¤sÂ)æ%+ÒŸ!]çoJh9¯F-#Ï”[)M<
ªÑ‘[ÉcçŽ
#è—Ê€Õ2­ìÙQ¡Q«¤`Nò›ÁÅhÿ' . "\0" . 'e]yÁLL2k°±Ða{@FH®fgC”ª=Î¬>¥kô<üÐÒ4`ò+¢Ö<5-«!RËéX~TªpcoÊ»hâ)W‡<ÑËWR”¹dŠÀ5:®E;ìÒ·HÛò©VŒ|ÊEk+Úær„­{2âš5<‹Q
Yš$RE8€ÔÐE' . "\0" . 'óNâ°‡(}©F×0PëÍU•LM‘Eì¸ò…zS†ƒMŠu~
Hcî´Óê„×FA-ª¸éU!9ŠÓŽ
8 aÍ\'"”Üw2„ŠÜ0æ¢{pNPâ¯Of•ëT˜I	ç‘YJëâ6„“øDIäˆáºUÈî•Æ
UYUÆƒ
žTâ…\'ÐrŠ{¢áÁäP}j—ïSÞž·}áUÎºàú0ÂªÉ	^Õ:Î¦¥Ê°§îÈIÊ&Yãµv[`Ç"ŠžFjªDÖŽé£ã5qn×­dœäñOFaÞ°Q-È»#Ó¡Ë8PÄf©–&›æºò)òè
Zêw¶Ákl3\'8îidñQ)ÏÒ¸¾Ÿ¹\'ñ¦é½+Åy¥GV·¼Ùè<Öq,E‡Ä±¹Ãe~µ3êöÒ¾+ÍMìôôº˜õÍáÜÔl(æÕ’×S¶¾K[¨‰ÝŸpk›šŽ@9^+·È«]ýkÓÂá¾¯DîŽlEnù­f@TÓ@ Õ“‚)„WA€ø§’/ºjü:É‡#Ú³3GZS£Nª´ÐãZ¥-bÎÃMº‚ônÆ>µ«¾(º0ÀÃw-°ýÙÅ#ßÝÈy”×Ìã¸ebªßšÑìzô³xÂ
êìô5´ãk5ÚM£‚Ê‹\\Ý\\#n¶~µ§kâ¨€Y>u¬ß
Ö£aê¿Bã›R›ýäKº‡ÙìÁ¡
å®îÒW!µÓM{o}È=swvª’ƒ½œ»é/~üÇ;Î½Æ¬@ræ –"µe2¼µ«N¿(Í{\\É-OA·¡’
(njýÆ™:så6>•^v71«)å½)s+\\¥NWI¡ñ' . "\0" . 'd|ÑJìFŠKA•äŠÄ»Òåµb@,•æàó|>*r§ï#·–Õ£5ª9Y£hŸ"¤‚ðŽ´nm÷qY3[n+Ñi­QÆšz3IdIš\\éXûä‡‘š³ 
MIu%Ó}
' . "\0" . 'Àõ¦K¸¥$CMÞÈyéU~ä[±Ÿ5‘•ªÅdŒ÷­ÍÊõÀ­Ú²•5º5…W³2–àŽT¡â~
O%=*»Y°éYûÈÓÝb5¸<¡¨ÊMNh"h½qRGv:8£Ý~C÷—˜ÁtëÁŠ´)Fx¢¯–}Ðê‹å†zQŒÔe”¿5$Šlv@§¦¢£¥' . "\0" . '‹4=iâñÒ FÇZ—xõ¥¨ô!OARÓÒ¢H¤.Â–£\'%.À*¨•³R	IëE‚äâƒŠŒ04»©€ãŠLSR‡¦´Ô~)6ÐS©2Š1N4 ó@XŠÔ¡•øjŒâŠd´+ÛƒÈ©mg6ÍÊäSñÖœT=*JÌ#\'ttš¥«€²¿QZZé÷,U	ö®\'zÕ›+¦·¹G@‘šòñYb©éIÅž•Å¦•H¦A6j©„UI-Tœ:ŒQˆ-D*EÏÖ‡Öl¤é"þuùÃÉó:UJqw¾çÒ,U	FÍ¡ŸØ¶s®5ü«2óÃ	–Ø+Y/a<«Î ¾Œ]ÄBÊTûW§‚Ææ1«ì±Sq]ìeR	GšLáµ›X£*ª öÅq÷bEvÚŽ™,2çxõ¬Yìƒƒ_ áà%isyŸ/ˆ©%WXØÁ†òH[’qZ°_G0ªÕƒ)ÈCwjRƒ%ÂÖçDWœ¡§,¸8jÅƒPxðñZQ]Å0äŒÖªiìa*rŽåÍÊzaÇzˆ¡ê‡4Ã#†„™1Ta‚TžÍNJÓüÌx˜´r§¸ùšØÊu–À&ŠÔxÕù¢£Ù>†Šªê6úTl‡
·åóG–qÒÙœÀŽÔÌ“Ú¯Iôª’¨”˜æ…˜Ó°®‰Ä¤S¼áÞ«œ‘Q’Aªå\'œ»æ­mPÞ}iÊçÖ•‡Ì_S¼Êª¯OE‡rÆìÑPù˜§	(°\\—4ô|U}ôðÂ‹ËYÍ\'J[Ž)K`S°®HP+ŒÔëÍaOSÍ7m\' Ó?Za¤iÛ…Q 9¤*GJp”S&‘:;Æ¦ÜGå“?Zˆ®i‡ƒYÎ•9é8ÜÒªCàvq©Í*a×šÏóry­H-Òàí\'3xrYbu?ZÃšŽE¢7å­ˆÕêc”IF—žXÑ&áè+a<5z8®·J… ¶X¦' . "\0" . '0kËÌ³ª8j\\ðj^Gn-œäÔÓG‹Ýi’ÂÄ2G¨ªE^#ÜWº_èz‚ Ü{ŠãµÌ˜0ËèjpYÖ¯YöeÖÀ×¥Ó™,ƒÇÃt­ï"˜`àµqàíI	Ö«/…u;¤W¢ñÔ©«ÊjÞ§/Ô§Sh´ÇAå
A"ºö¨§i4ùBH÷«_G(Ãc5×J¬*Çš\'-J3¤ìÈÖb¼*Á$åH¢¶³2æ‰Ñì½;µGÈ4¡Ïq\\¦ã¶ƒÚ –Ýt©·1š»s2K!ØUchTô­¶!Íh,™˜"*1L’éZ¢y4¦ÝXUsÈa4DSBâµå³ã"©IlÀô¢ábÀ 1§l Òù|p*’!±…B)J”ŠvN’Ö¥	ª@‘R+â€Ø¼„æ¤$‘U¢95d)"‹
äåZ§†ã<«0 œÔ)V¡ RlßRiŒqPÙN`Õ™c¹„äE¸qJjÜ¦ž$ÏZv1*¾:Ô™Ï"«žFhWÚh°îZ
ëC' . "\0" . 'i†¬¸ ²Èr	J¹m¬ÜÀ@¸z¬ËÅU<VS§«I\\Ò%x»D&aÄ‘~U­a©Ç~åPEyúNAæ¶t]I-nƒ¹ùOZð³,‹	^Œœ!ï[CÕÂfU£Q)ËCºSJ×qÇ÷Ø~5ƒ}âXâY±Ú¹[ûû«¶$¹QØ_!—ð–&«æ®ùâ{ŒÚ5hêÏJY­¦5‘­[Ê`o³Æã¥p1j7¶äø÷ÍkÚx®é0³' . "\0" . 'ãõ¯n
TÂÔç„¹×fr<Ú•EË+Äåµ-2f¸v•HCYÙIÈ½*}JÇQ‹ Wÿ' . "\0" . 'hZç®-ãÞBò+êè{ñ´£ÊÑã×~ÍóF\\Éœ¢O4<sEmÉ`ŒsŠ+nIw1ö{£zŒÑžô€úÔ4$ÅÇ¡ˆ¤Ü
&iY•tIÜA‹=
05=XŽõJ]=Q¡^
5r*ØÃŽy¨Þ,tù{ŸFC×­1¢VŠqÈ4õaŒI5Ôm=ÑHÛ.h[upÆ®x4ŠŠ­E¡I­ÁÍBö¹­^:SUsNâ²2^Ø¨5B;Vé‡wZ«=¯EÉ±JÁ©' . "\0" . '9¬ÍŒE\\·“ª$–êß*N+E*ÕÒ®$LÉ¿·ÚI÷¬Ee&×­´ÐW2¬Q«oO»“EÁ¡óÂ{UBJÖÓ uÈªügi™´WI;‘†FETl¡æ¦ŽLñšd‹##U¸äÞ*›r8¤I
’Í¹^*´ªy© ”0Å>H·Šs&AŒÔi1CV¦ˆ‚j‹Œ5+™u\'©„«5XÔ¢Lw¥a¦YeRjs¢Ü½·Ú"]Ë×©y¾õÛxNég³h[§×—›c*`°Ï~]×‘Ý€¡E_g>§–Š° ŽÆ¥Y®ûUðå­ú–@OQ\\6¡¤]é’êJvaQ•ç˜\\Â?»•¥Ùî<f[W­®»Œ *˜‘È¢½£Î±¢
ô¼ù¬½Ì:~9©R½Èë3{£Cé@«,äñšœAÇò¤ÜóHzÔFaqGœ\'4X	Ô‘Þ¦Y9æª,ÊOLTÊÂ©Ñ#aœ`ÔLž†œO8ëM$ƒÒ“m' . "\0" . '¯­8H}iIÈÉ¦2¥k™=Çn…P*.sÆœ¬sÍR%“¥1îÆidu§«a©Ø›•g´8Õ?$ÆØÇ·¹ƒÅE-°<ŽiýÈ-ºš.àÞ™Å9ÆzU‘†NzÓLLåî!ÚÇŠŠ)6Èâ·î¬Ã@¬™lÈ\'Š`MDie%^1\\±VŒ÷«6÷Ï<S5.m22µšàÆø­kkÄ™q‘š.-VUÈëM23LŽ´âi’ÀÑH	Å1§bÄ2ïZJk!jÄ2JÁsBX•ÆEeÜÛã‘ZQÊsMš0ëE2=:ÛN”q.Ð¶+¤·ðþ‘2‚¬þ\\UÄI TPÜÍnÙŽW\\zòqx
õµ¥^QûN†6”§I3ÑÓÂúhéšÑ²ÒmìX˜.zâ¼þÓÄº…¾›¼Í]›ã4‰ÄEKdr+äs<;p’U¹ãÛcÙÂæ%hò¿CªlŠ†X£™vÈ‡¸«# aÐŠ‚E+Ò¾9Þ.ÍëI­JÃH²?òÅ?**eEvÿ' . "\0" . 'ic¿çì¾ó?cOùQå dõ¤Ûƒ’;t¨R\\‘Ó uàž1_¸8rJtïL
¼uü
9XŽ @Hp@@çõ¨Ãõ§ïõÀ&Ž	ƒ‘R.8çéLr1ïJŽ´›wëJ?ãM‚)\'‘b‰K;°
¹§:4´r«#©åXt©ö‘çä¾»ÛÈ|®ÜÖÐ^3È¦	£<ñÞ“pïÅhˆh@‡Ó4l§Î}©TàP ' . "\0" . 'tæžªzM¼ñNEÉïïšba·‘@$
' . "\0" . '}èã(¹"n
Á»' . "\0" . 'û´˜íJª%ƒ.áU¤€·“Û¥4€E' . "\0" . 'Œ™íCf³æ¶)[ò!ÍA$aÇ PV†$r4O‘Z–Ú€8Uæ´ç U9#xØñHv:HçNÆ¨ÍfcåzU;k×Œàô­h®Òeù±šjW\'–ÅNÆ¤U«on¬r½j3/j«ŠÉìF”ñR¬¤piÊ;SŒa…;¢yZ!•VEâ³\'Œ£V›FÈMV™CŽ”X.PVÁ«0¾×AÈªÒ!SB6Ò)yæzþ‹r.´Èd?/5fêX¡ˆ¼ŒZà4fYÉ©nè*ž¡­Ýjn|Ç!; <Wçàêµó
’“å¥{ù»ö>«ûj•<<^ò¶Æ½ÿ' . "\0" . 'Œ#†å’‹ þ!Er­{Q_YË#fç8¦ïr|Z”IÓš¥¼ö?­8I^±…‹Ë\'ljEzÖp“§8ÅH%9È9¢Ä³@H00Ô¢LûŠ¤$#œ
‘%©Å;rØçƒÍ(”ñ’
Uö<Óƒy>ÔX.uþ¶óµ¹eùa_”ã¹ÿ' . "\0" . '&º_DƒV‹pÄw
>Y' . "\0" . 'ý¨ª~³6z4[†$—÷Ÿ~Ÿ¥o)¯È³ŒÞsÌå^Œ­ÊìŸ’ÿ' . "\0" . '=O±Áá#*§5¾¯æyuå´ÖW-ñ”‘:ç¿¸¨CõõéZ®“o«[ùrŒ:ýÉU?çµyÝõ…Æ™tÐ\\ÆAu‡F¢¾ë"â
YŒ=œô¨·]ü×ù?.žóGXŒ
Àþ´ýÙ=¸ªÂNzŠx“üëéå²Âpqøâ¥Çz¬²×µL®:E‰¸ÿ' . "\0" . 'Ä~TÝøõ4¤óM8ëÒ‹•O=isŽ•¶	÷§—¾†‹' . "\0" . 'ü‘ïHOÔ{‰ïNóÍhiÂ ûÔ­Œ
Œði…ˆ™=*	!9§cc.¡qäBWÌ õÇjŽæÖkYLsÄÑ·£
ËÛÒu=2æµíÖÆžÎjöÓ¹‡=©*¢«’œt­Ý ñŒÔ2Ù¬€àU´%"µ¾ pVŠL’¯QXÓY<g#¥WK‰`lgŠšÎˆ¯¡°yª6ú”o€Çš×±¶†ý¶}¥"ýÝýãD§Ç™„a)K”åqÈ­|8Ú†˜n-[tŠ~d©_ÂÚ¬|¬K ìU«WÃ±ê:]ö\'¶qœ7|{×‘Ìéû<-X¹Ç[]kmÑß†ÁIUQ­Êü¶ó8»)!£¡VAšèT×·ë³ÕcË(Y;8ë^w¬øZîÁ™™7ÇÙÔTe<C…ÌùgÙþÃ•ÖÃ>e¬{œ j‘_š|–Ìª¯ G–Ë	)hªùÅÅc?=èúnO¥4çµ`v—ìm¡¹lMy°ÿ' . "\0" . 'lü†+§²ð•…Àj¢_úäøšâjtr¼m¹It à×™Áâk»‡É?Òÿ' . "\0" . '‰ÕFµ(|tÔ¾lô¸|¥&7ßêøþU~hñþ†­þóýkÎm<IªZà%ÜŒ=î­t6><™0·vÈã»Fp*ù,nKŸ+¸Ws^RkðÑ~\'­G—ìáËò;ô=):XAø 5f-:Ê>#´~‘ŠÇ²ñv•w€g11þF?^•»ñJ£uu?Ä§"¾?O0 í‰æ^·=z/5zv~–,ŒqR-B¼ô5ar:ŠòäÎ‘ÃÞœ' . "\0" . '=F~´éN³æ	äBßz$?UéÖOÃZ@ßXÅN++Vñ†
Ìûæˆ““øúWVªõ,:nO¢2«*TãÍRÉy–AÒ¤ûÚ|‚ü«+Q³ðÅ€?hUWÿ' . "\0" . 'žqÈÅ¿,ÿ' . "\0" . ':åõê7ä¤,-¡?ÃùÔÖ(rÄ±cžäšý)á|Á%<^"Qþìdïó{}×>g›a¾4ÓóhÖ¾žÉäÿ' . "\0" . 'A‚X“?òÑ÷>ª ”' . "\0" . '*¸cß<zSwry¯¹¥AR‚‚mÛ»mýìð\'UÎWkîÐ¶1à~T¹ÿ' . "\0" . 'õU6ÓS$á¾¾•MÉÉëÇåBÈ1ÉÅ]³Õ¶Ñ-µÄ}Ä‘ŒþcšÝ¶½ðµØÄö"ÙÏ®Jþb¼Ì^:¶_a).ñiþ3²Ž]=¢OÏC–-Àæ·ë^… ÜG¾Þ¤_TŸëOÑÈ' . "\0" . 'Ú‘ô‘¿Æ¼)q–å9§è¿ÌïY%f®¤ŸßþG£\\}›Yµ“=$' . "\0" . 'ýè÷¶·ñ®"Wqô5›ÿ' . "\0" . '–”:,ÈÀäÿ' . "\0" . 'ã[DÕò¼AœPÇW§_	u(«v~[?S×Ë°s¡NTêÙ¦pº§„n-÷KbLñõÙüCükž;£b®¥Hà‚9ëkÖ©jzž«óSl½¤^z9_Õ¥jxÕÌ¿™oó]?S›’Bw•gÛ¡ååU¸aôªw1È	ôð<#{ ú ÿ' . "\0" . 'ˆøÿ' . "\0" . 'ð?ïGÿ' . "\0" . '×¯¦åRÿ' . "\0" . '—–ù?ò<§”cÑüQå³ÙËdŠHoå€àœŠô©ü~Ëò½¼£ýâ?¥sÚ‡€5`ÄÇl¿]âºãeÓWhýöüÌÞœhþ1»´|§÷‘]}§`‘GÚ e?ÞNEy.¥¦Í¤\\y2ÉJ>ò¡ÎßÇÖiªÉ	ÚzVu²Ì»2´œ¿U£ûúšCŠÃ>XËnSÜlõË+öÙo:³ÿ' . "\0" . 'tðjë"•uc^Ea¨§›ðÉ²U9éÚF¤š¥‘p%^}
|7pëË’Äa›püSÿ' . "\0" . '#ÜË³?¬ÞEi~e+ßé×ŽÎ ÄÍ×oJÃ¹øzNL7CñZíÞXáRÒº¢ŽìqYÏâM%&›µÉî ~5Ž9Ïå å4¼¯øØ×‚ÀÞõWó±ÃÉðþùOË4gð¢½"9ã¸Œ<Ç"žàæŠè|Y›EòÊÉùÄÍdø7ª_‰ó©¤àÓÈÅ\'N1_©XùkŒÇœô§MäE
b)àÓCsÒ€Fi¡2d\'5ê¶û6…aóJKšóHMÅÔP¯%Ü/ç^Ëi‚Þ8€á_Æø®Zðë«¿Ýÿ' . "\0" . '{yÔ•GÓBäc‘Š¸½*šTwºµ¦™û™‚žÊ:ŸÂ¿5…
µæ©Ò‹”ŸD}$§.i;#O9âœ+Ï/üuu$àY Š0ˆdµlé^6¶œ¬wÉä9þ5åOøW»[ƒóZTnKù\'ªþ¼:Îu=Ÿ7Ï¡Öà­s~)ðÿ' . "\0" . 'ö•·Ú`Qö˜Çýö=>µÑÃ,W‰!ut=NE)¯‹ÄeØ˜Ö§îÊ/¯äÎêÔiâ)8KTÏÆ©È#¨=©ãŽ¢ºÿ' . "\0" . 'h\':•²aXþùGcë\\pcœ
ýß*ÌèæXXâ)uÝv}Qùî7	<-gN_/4N¤ŒœúRJ29àÓ	P2x4…ÎÞOèœ·!~9˜%!©î{Õwàæ¥—hEr8æ­«†\\Ç¨¬0øÅYŠàŽ•-{‰$Ë¾wSƒZvÞ-Õí1ºUiF^µˆ’î_SQ¾9Æk—‚Ãâ«AKÕÒÄT¥¬$ÑÝZxþÝÀVŽ‡»FÁ‡äq]U•ô…¤w01hß¡#ëÆŠôjôÏæh!O;$aýkàø£"Â`ð¿YÃÇ•Ý\'®–~§ÐåY…jõ}G}¨Jgð¨Çz˜6kàTî}
…`
FA›-õ¤Sˆ%¹‰%=œR•ã#¥i:sŠR”ZObT“vLÄÕ<Qi¤¹…•¥¸î/úšæ¯|Y¨ß+*²Áíç^µÖêºE¦«—s,8Y¿pZ¶…w£É¸æKrx•z~>•÷/ýQ(Tï½ª~>[úžmõØÞP~ç—ê`jxŸtIç>µÎ\\[<LAŠìÃnœÕ+Û4”~ˆàš>nzœ´W/pOÓè~\'šÂ]ÑI±ˆÚ{Šçîìš"p*ŽöºšÂqŒ¢áQ]>ŒêŽ¯šÌïî¯.uó¥¸yAõ=?
¨yìM`éú»BÁ[¥tPË
âeWôìkjQ„b£MYvG-^~kÏQ#¹šÜŸ*i#Ï÷[Sd‘¶°æŠ§N-Ý¡*’JÉœ»/4Ò0*gR§tÅSE§r#Ž´cÒœE&)q1HE/J	 
¿Úr6#+Þ~½«Ó^á-¢2Lêˆ:’kÏ<;©ÚhÚ|÷°iœáPu¬íO[¼Õ¥Ì®V,ñè+ás,›œf-¿vœl¯ß½
Œ¥ƒÃ.²zÛüÎ¯Sñ»1h4åöó[ú
æ¥¹šéÌ“JÎç©cš¡«9À¯­Ërœ._Z³êú¿™àã1•±2¼ÞºR¯8æ«§ˆ†kÔ8±©§ê×Ú\\›í¦u×9ð®ËKñ½½ÆØï“ÉsÆõåúÕÁªö<Šk©Ï
ò3,‹™/ßÃ^ëG÷˜LË…~ä´ìö=ŒÖÄI`c ä^câ
Mÿ' . "\0" . 'åæÙÎcoèj½Ž«y¦ÈÞf_QØþºÞ)´ÕìZÏU‡còÍÎ®+æòü‘b½¦ûJ2ø—_[ukÈõ±ü6cG–§»5³é÷œ‘l“)¬})eÂHÊe' . "\0" . 'Žõs_tÕÏœi§aKv¨œ)Ç#½4·¯42‘qNG#ž)â
“BÊKÏz˜>{ÕE<Ô™çŠd2w ¨È®÷Àr¦ÝGžV@qõýjóðÄ/=+¡ðÞ¿‹oxdRîáv îyï^àêbòÙÒ¤¯\'k/š=¦¼ib”¦ìµüFžö(Zk‰V8×©c\\n­ãy§-
€0ÅÓÌ?xý=+—Õ5›­^2âC´•î­RBAÈ5ãä|C•\\_¿>Ýù¸üîuo
G¿Vi5ÃÈåÙ‹É$óZõý†<‹©ºNWò5†­òƒJ²q__SJ¤9\'×f´<hVœeÍfz—Žw' . "\0" . '·ÖÀú¼Gúñ®†ßTÓ58ÊC<o¼`ÆüíƒÖ¼‘fÁ"§I_3á
z•éËËo»ü¬zÔ3ºðÒ~ò:ýkÂL›®4Ñ‘ÔÁžŸîÿ' . "\0" . '…r¹Ã|©#¥hYøS²ÂÇ9tÃ\'Ì?Z’ûU°ÕÆë¨
­Þ8š.U¿Þk§ÏjXŸÞÃ¤—Ä½W_•ß©–!á1ý/r]žÏÑô9û»A"Šçní6±k©óJœê;Õk›t”sÅ{î*Hóá7q¯˜Ú®Ùê2BÀ‚zÔ·¶[IÀ¬—VŒúW;Ní‹Tw–z´18É¯z+‡†íãÍ¢ª¬`ðÎú³ÆCªr5¯wÖ\\ƒ·hç„ºÉç"ŠFàš@j‹Ïµq@§ši	²=¢¥ŒRm©GZ¤‰“Ð™G¤ñ@ô¦?¬Çv!r
K3TØœÔˆæ¥2å
¨%éÏáV
†\\V\\r
kÛ|àTûœ¶ÖÄ2FUVAÏjÔ‘' . "\0" . 'Àëš§*Bbz"“p©$8¨{ÐZÕ>ÔÃNÅ4ñHhiÅ0­=ºÐ})…Z~}ª01NÎ2XíÜu£&£$ÐI ,Išp#ïQæœ4	“¦qÁ§o8äÓëKÚˆ¸nÁùx©ã“§?Z¬zÒAëJÅ&h«äqÖ†\\ŽÕZ\'lç5a±4¬;‘Ÿ—½*Êzué€=j¾ãŠC<+"ôçÒ°ï¬IŠÝW8ÁçŠdê0@¤ã}…GtqRÂÈæŠÜ»¶Œ=ÊèêzÄ&ÿÙ',
      ),
    ),
  ),
);
return $content;
}
