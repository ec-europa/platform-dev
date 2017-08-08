<?php

/**
 * @file
 * Contains \Drupal\nexteuropa\Component\Utility\Transliterate.
 */

namespace Drupal\nexteuropa\Component\Utility;

/**
 * Class Transliterate.
 */
class Transliterate {

  /**
   * Generate a machine name.
   *
   * @param string $string
   *   The human name.
   *
   * @return string
   *   The machine name.
   */
  public function getMachineName($string) {
    $a = explode(",", " ,&,à,á,â,ã,ä,å,æ,ç,è,é,ê,ë,ì,í,î,ï,ñ,ò,ó,ô,õ,ö,ø,ù,ú,û,ü,ý,ÿ,ā,ă,ą,ć,ĉ,ċ,č,ď,đ,ē,ĕ,ė,ę,ě,ĝ,ğ,ġ,ģ,ĥ,ħ,ĩ,ī,ĭ,į,ı,ĳ,ĵ,ķ,ĺ,ļ,ľ,ŀ,ł,ń,ņ,ň,ŉ,ō,ŏ,ő,œ,ŕ,ŗ,ř,ś,ŝ,ş,š,ţ,ť,ŧ,ũ,ū,ŭ,ů,ű,ų,ŵ,ŷ,ź,ż,ž,ƒ,ơ,ư,ǎ,ǐ,ǒ,ǔ,ǖ,ǘ,ǚ,ǜ,ǻ,ǽ,ǿ,ά,έ,ό,Ώ,ώ,ί,ϊ,ΐ,ύ,ϋ,ΰ,ή");
    $b = explode(",", "_,_,a,a,a,a,a,a,ae,c,e,e,e,e,i,i,i,i,n,o,o,o,o,o,o,u,u,u,u,y,y,a,a,a,c,c,c,c,d,d,e,e,e,e,e,g,g,g,g,h,h,i,i,i,i,i,ij,j,k,l,l,l,l,l,l,n,n,n,n,o,o,o,oe,r,r,r,s,s,s,s,t,t,t,u,u,u,u,u,u,w,y,z,z,z,s,f,o,u,a,i,o,u,u,u,u,u,a,ae,o,α,ε,ο,Ω,ω,ι,ι,ι,υ,υ,υ,η");

    $string = str_replace($a, $b, strtolower($string));

    // Valid characters are:
    // - a-z (U+0030 - U+0039)
    // - the underscore (U+005F)
    // - 0-9 (U+0061 - U+007A)
    // We strip out any character not in the above list.
    $string = preg_replace('/[^\x{0030}-\x{0039}\x{005F}\x{0061}-\x{007A}]/u', '', $string);

    return substr($string, 0, 32);
  }

}
