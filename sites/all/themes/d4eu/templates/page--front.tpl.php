<?php
/**
 * @file
 * Page template for the homepage.
 */
 ?>
<div class="layout" id="layout">
  <a id="top-page"></a>

  <header id="layout-header">
    <div class="container">
      <?php echo $regions['header_top']; ?>
      <div class="headerBannerContainer">
        <div id="main-logo"><img id="banner-flag" src="<?php echo $logo; ?>" alt="European Commission logo"></div>
        <div id="main-title"><span><?php echo $site_name; ?></span></div>
        <div id="sub-title"><span><?php echo $site_slogan; ?></span></div>
      </div>
    </div>
  </header><!-- /header#layout-header -->

  <div id="path" class="hideWhenSmall">
    <div class="container">
      <?php echo render($page['breadcrumbs']); ?>
    </div>
  </div><!-- /div#path -->

  <?php if ($page['main_navigation']): ?>
    <nav id="main-navigation">
      <div class="container"><?php echo render($page['main_navigation']); ?></div>
    </nav>
  <?php endif; ?><!-- /nav#main-navigation -->

  <?php if ($page['banner']): ?>
    <div id="banner">
      <div class="container"><?php echo render($page['banner']); ?></div>
    </div>
  <?php endif; ?><!-- /div# -->

  <div class="identityContainer">
    <div id="layout-body" class="container">
      <div id="pageCenter" class="clearfix">
        <?php echo $regions['featured']; ?>
        <?php if ($regions['tools']): ?>
          <div class=""><?php echo $regions['tools']; ?></div>
        <?php endif; ?>

        <?php if ($messages): ?>
          <div id="messages"><?php echo $messages; ?></div><!-- /#messages -->
        <?php endif; ?>
        <a id="content"></a>

        <?php if ($tabs): ?>
          <div class="tabs"><?php echo render($tabs); ?></div>
        <?php endif; ?>

        <section class="mainContentSection clearfix">

          <?php echo render($title_prefix); ?>
          <?php if ($title): ?>
            <h1 class="" id="page-title">
              <?php echo $title; ?>
            </h1>
          <?php endif; ?>
          <?php echo render($title_suffix); ?>

          <div class="contentContainer">
            <a id="main-content"></a>
            <?php echo $regions['help']; ?>


            <div class="homepageContainer">

              <div class="topHPcnt">

                <div class="mainBlocks">

                  <div class="block_ourVision">
                    <?php print views_embed_view('home_d4eu', 'block_vision'); ?>
                  </div>

                  <div class="block_ideas">
                    <?php print views_embed_view('home_d4eu', 'block_ideas'); ?>
                  </div>

                  <div class="block_evidences">
                    <?php print views_embed_view('home_d4eu', 'block_evid'); ?>
                  </div>

                  <div class="block_videos">
                    <?php print views_embed_view('home_d4eu', 'block_talk'); ?>
                  </div>

                  <div class="block_joinButton">
                    <?php
                      $block = module_invoke('boxes', 'block_view', 'join_here_homepage');
                      print $block['content'];
                    ?>
                  </div>

                </div>

                <div class="socialBox">
                  <div class="socialLinks">
                    <?php
                    $block = module_invoke('boxes', 'block_view', 'social_links_homepage');
                    print $block['content'];
                    ?>
                  </div>
                  <div class="twitterBox">
                    <?php print views_embed_view('socials_home_d4eu', 'block_twitter'); ?>
                  </div>
                </div>

              </div>

              <div class="botHPcnt clearfix">
                <div class="blogPost">
                  <?php print views_embed_view('bbox_home_d4eu', 'block_blogposts'); ?>
                </div>
                <div class="polls">
                  <?php print views_embed_view('bbox_home_d4eu', 'block_pollshp'); ?>
                </div>
                <div class="events">
                  <?php print views_embed_view('bbox_home_d4eu', 'block_events'); ?>
                </div>
              </div>
            </div>
          </div>

        </section>
        <?php echo $regions['content_bottom']; ?>
      </div>

    </div><!-- /#layout-body -->
  </div><!-- /.identityContainer -->

  <footer>
    <div class="container">
      <div id="footer">
        <div class="footer">
          <?php echo $regions['footer']; ?>
        </div>
        <div class="footer_copyright">
          <?php echo render($page['footer_copyright']); ?>
        </div>
      </div>
    </div>
  </footer><!-- /footer -->

</div><!-- /.layout -->
