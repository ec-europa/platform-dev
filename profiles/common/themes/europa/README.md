
Twig for Drupal is mostly autoconfigured with sensible defaults, however you might want to fixate the location of where the template cache is writen. By default it goes into /files/twig_cache of your site. But you can override this behaviour by setting the file_twigcache_path in your settings.php

$conf['file_twigcache_path'] = 'path_to_cache';
