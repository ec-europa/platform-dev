<?php
/**
 * @file
 * Code for the NewsroomPage class.
 */

/**
 * NewsroomPage class.
 */
class NewsroomPage {

  const DATE_FORMAT = 'd/m/Y';
  const MYSQL_DATE_FORMAT = 'd-m-Y';

  protected $type = NULL;
  protected $topic = NULL;
  protected $startDate = NULL;
  protected $endDate = NULL;

  /**
   * NewsroomPage constructor.
   *
   * @param object|null $type
   *   Newsroom type.
   * @param object|null $topic
   *   Newsroom topic.
   * @param Datetime|null $start_date
   *   Start date.
   * @param Datetime|null $end_date
   *   End date.
   */
  public function __construct($type = NULL, $topic = NULL, $start_date = NULL, $end_date = NULL) {
    $this->setTopic($topic);
    $this->setType($type);
    $this->setStartDate($start_date);
    $this->setEndDate($end_date);
  }

  /**
   * Gets minimal items number per agenda page.
   *
   * @return int
   *   Number of items.
   */
  public function getItemsNumber() {
    return variable_get('newsroom_agenda_page_items_number', 10);
  }

  /**
   * Gets term URL.
   *
   * @param string $value
   *   URL part.
   *
   * @return string
   *   Term url part.
   */
  public function getTermUrl($value) {
    return !empty($value) ? pathauto_cleanstring($value) : NEXTEUROPA_NEWSROOM_ALL;
  }

  /**
   * Sets type.
   *
   * @param object|null $value
   *   Type object.
   */
  public function setType($value) {
    $this->type = $value;
  }

  /**
   * Gets type.
   *
   * @return object|null
   *   Type object.
   */
  public function getType() {
    return $this->type;
  }

  /**
   * Sets start date.
   *
   * @param DateTime|null $value
   *   Start date.
   */
  public function setStartDate($value) {
    $this->startDate = $value;
  }

  /**
   * Gets start date.
   *
   * @return DateTime|null
   *   Start date.
   */
  public function getStartDate() {
    return $this->startDate;
  }

  /**
   * Sets end date.
   *
   * @param DateTime|null $value
   *   End date.
   */
  public function setEndDate($value) {
    $this->endDate = $value;
  }

  /**
   * Gets end date.
   *
   * @return DateTime|null
   *   End date.
   */
  public function getEndDate() {
    return $this->endDate;
  }

  /**
   * Sets topic.
   *
   * @param object|null $value
   *   Topic object.
   */
  public function setTopic($value) {
    $this->topic = $value;
  }

  /**
   * Gets topic.
   *
   * @return object|null
   *   Topic object.
   */
  public function getTopic() {
    return $this->topic;
  }

  /**
   * Gets image by file ID.
   *
   * @param int $fid
   *   File ID.
   * @param string $style_name
   *   Style name.
   *
   * @return null|string
   *   Image HTML presentation.
   */
  protected function getNodeImage($fid, $style_name = 'newsroom_style') {
    $image = NULL;
    if ($fid) {
      if ($file = file_load($fid)) {
        $image = theme('image_style', array(
          'path' => $file->uri,
          'alt' => $file->title,
          'style_name' => $style_name,
        ));
      }
    }

    return $image;
  }

  /**
   * Creates formated date string.
   *
   * @param string $timestamp
   *   Timestamp.
   *
   * @return string
   *   Formated string.
   */
  protected function getFormatedDateFromTimestamp($timestamp) {
    return $timestamp ? NewsroomHelper::getFormatedDate(NewsroomPage::DATE_FORMAT, $timestamp) : NULL;
  }

  /**
   * Gets data from DB.
   */
  protected function getData() {
    $cache_key = 'page_result:' . md5($this->getUniqueCachePart());
    if ($cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE)) {
      $data = $cache->data;
    }
    else {
      $items = $this->fetchData();
      $data = array();
      if ($items) {
        foreach ($items as $item) {
          $node = node_load($item->nid);
          $type = NewsroomHelper::getNewsroomType($item->type_tid);
          $short_title = NewsroomHelper::getFieldTranslatedValue($node, 'field_newsroom_item_short_title');
          $data[] = array(
            'nid' => $item->nid,
            'start_date' => $this->getFormatedDateFromTimestamp($item->start_date),
            'end_date' => $this->getFormatedDateFromTimestamp($item->end_date),
            'title' => $short_title ? $short_title : $node->title,
            'teaser' => NewsroomHelper::getFieldTranslatedValue($node, 'field_newsroom_teaser'),
            'type_url' => NewsroomHelper::getNewsroomPageUrl(array($type ? pathauto_cleanstring($type->name) : NEXTEUROPA_NEWSROOM_ALL, NEXTEUROPA_NEWSROOM_ALL)),
            'type_title' => $type ? $type->name : NULL,
            'node_url' => url(NewsroomHelper::getNodeMainUrl($node), array('absolute' => TRUE)),
            'node_redirect_url' => url('news-redirect/' . NewsroomHelper::getFieldValue($node, 'field_newsroom_item_id'), array('absolute' => TRUE)),
            'image' => $this->getNodeImage($item->fid),
            'venue' => NewsroomHelper::getFieldTranslatedValue($node, 'field_newsroom_item_venue'),
          );
        }
      }

      cache_set($cache_key, $data, NEXTEUROPA_NEWSROOM_CACHE_TABLE, time() + variable_get('newsroom_ct_page_result', 300));
    }

    return $data;
  }

  /**
   * Returns the newsroom page html.
   *
   * @return string
   *   HTML.
   */
  public function getContent() {
    drupal_set_title($this->generateTitle());
    $filter_form = drupal_get_form('nexteuropa_newsroom_newsroom_page_filter_form', $this->getType(), $this->getTopic(), $this->getStartDate(), $this->getEndDate());
    $content = theme('newsroom_page', array(
      'filter_form' => drupal_render($filter_form),
      'featured_item' => $this->getTypeFeaturedItem(),
      'items' => $this->generateItems('newsroom_page_item'),
    ));
    return $content;
  }

  /**
   * Returns the newsroom page html.
   *
   * @return string
   *   HTML.
   */
  public function getRssContent() {
    $namespaces = array();
    if (function_exists('rdf_get_namespaces')) {
      // Merge RDF namespaces in the XML namespaces in case they are used
      // further in the RSS content.
      $xml_rdf_namespaces = array();
      foreach (rdf_get_namespaces() as $prefix => $uri) {
        $xml_rdf_namespaces['xmlns:' . $prefix] = $uri;
      }
      $namespaces += $xml_rdf_namespaces;
    }

    $content = theme('newsroom_page_rss', array(
      'title' => $this->generateTitle(),
      'link' => url($this->getNavigationUrl(TRUE), array('absolute' => TRUE)),
      'namespaces' => drupal_attributes($namespaces),
      'description' => NULL,
      'items' => $this->generateItems('newsroom_page_rss_item'),
    ));
    return $content;
  }

  /**
   * Generates title based on incoming parameters.
   *
   * @return null|string
   *   Page title.
   */
  protected function generateTitle() {
    $page_title = t('Newsroom');
    if ($this->getType()) {
      $page_title = $this->getType()->name;
    }
    if ($this->getTopic()) {
      $page_title .= ' ' . t('about !topic_title', array('!topic_title' => $this->getTopic()->name));
    }
    return $page_title;
  }

  /**
   * Prepares page items for presenation.
   *
   * @param string $template_name
   *   Template name.
   *
   * @return string
   *   Output string.
   */
  protected function generateItems($template_name) {
    $output = NULL;
    foreach ($this->getData() as $item) {
      $output .= theme($template_name, $item);
    }
    return $output;
  }

  /**
   * Gets the unique part for cache value.
   *
   * @return string
   *   Cache key unique value.
   */
  protected function getUniqueCachePart() {
    $type_id = $this->getType() ? $this->getType()->tid : NULL;
    $topic_id = $this->getTopic() ? $this->getTopic()->tid : NULL;
    $start_date = $this->getStartDate() ? $this->getStartDate()->getTimestamp() : NULL;
    $end_date = $this->getEndDate() ? $this->getEndDate()->getTimestamp() : NULL;
    $page = isset($_GET['page']) ? $_GET['page'] : NULL;

    return $type_id . $topic_id . $start_date . $end_date . $page;
  }

  /**
   * Fetchs the data from DB.
   */
  public function fetchData() {
    $query = db_select('node', 'n');
    $query->distinct();
    $query->fields('n', array('nid', 'created'));
    $query->addField('type_field', 'field_newsroom_item_type_tid', 'type_tid');
    $query->addField('d', 'field_newsroom_item_date_value', 'start_date');
    $query->addField('d', 'field_newsroom_item_date_value2', 'end_date');
    $query->addField('image', 'field_newsroom_illustrative_img_fid', 'fid');

    $query->leftJoin('field_data_field_newsroom_item_type', 'type_field', 'type_field.entity_id = n.nid');
    $query->leftJoin('field_data_field_newsroom_topics', 'topic_field', 'topic_field.entity_id = n.nid');
    $query->leftJoin('field_data_field_newsroom_illustrative_img', 'image', 'image.entity_id = n.nid');
    $query->leftJoin('field_data_field_newsroom_item_date', 'd', 'd.entity_id = n.nid');

    $query->condition('n.status', 1);
    $query->condition('n.type', NEXTEUROPA_NEWSROOM_CONTENT_TYPE);
    $query->orderBy('d.field_newsroom_item_date_value', 'DESC');
    $query->orderBy('d.field_newsroom_item_date_value2', 'DESC');

    if ($this->getType()) {
      $query->condition('type_field.field_newsroom_item_type_tid', $this->getType()->tid);
    }

    if ($this->getTopic()) {
      $query->condition('topic_field.field_newsroom_topics_tid', $this->getTopic()->tid);
    }

    if ($this->getStartDate()) {
      $query->condition('n.created', $this->getStartDate()->getTimestamp(), '>=');
    }

    if ($this->getEndDate()) {
      $query->condition('n.created', $this->getEndDate()->getTimestamp(), '<=');
    }

    return $query->extend('PagerDefault')->limit($this->getItemsNumber())->execute()->fetchAll();
  }

  /**
   * Returns navigation link based on URL.
   *
   * @param bool $is_rss
   *   Is url for RSS feed or not.
   *
   * @return string|null
   *   HTML link.
   */
  public function getNavigationUrl($is_rss = FALSE) {
    $url_parts = array();
    $url_parts[] = $this->getTermUrl($this->getType() ? $this->getType()->name : NULL);
    $url_parts[] = $this->getTermUrl($this->getTopic() ? $this->getTopic()->name : NULL);
    if ($this->getStartDate()) {
      $url_parts[] = $this->getStartDate()->format(NewsroomPage::MYSQL_DATE_FORMAT);
    }
    if ($this->getEndDate()) {
      $url_parts[] = $this->getEndDate()->format(NewsroomPage::MYSQL_DATE_FORMAT);
    }

    return $is_rss ? NewsroomHelper::getNewsroomRssUrl($url_parts) : NewsroomHelper::getNewsroomPageUrl($url_parts);
  }

  /**
   * Gets type featured item.
   *
   * @return null|string
   *   Featured item content.
   */
  protected function getTypeFeaturedItem() {
    $content = NULL;
    if ($featured_item_id = NewsroomHelper::getFieldValue($this->getType(), 'field_featured_item', 'target_id')) {
      $cache_key = 'type_featured_item:' . $this->getType()->tid;

      if ($cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE)) {
        $content = $cache->data;
      }
      else {

        if ($featured_node = node_load($featured_item_id)) {

          $type = NewsroomHelper::getNewsroomType(NewsroomHelper::getFieldValue($featured_node, 'field_newsroom_item_type', 'tid'));

          $style_name = 'large';
          $image = $this->getNodeImage(NewsroomHelper::getFieldValue($featured_node, 'field_newsroom_illustrative_img', 'fid'), $style_name);
          if (empty($image)) {
            $image = $this->getNodeImage(NewsroomHelper::getFieldValue($featured_node, 'field_newsroom_private_img', 'fid'), $style_name);
          }

          $topic_url = $this->getTermUrl($this->getTopic() ? $this->getTopic()->name : NULL);

          $content = theme('newsroom_page_featured_item', array(
            'type' => $type ? l($type->name, NewsroomHelper::getNewsroomPageUrl(array($this->getTermUrl($type->name), $topic_url))) : NULL,
            'title' => l($featured_node->title, 'node/' . $featured_node->nid),
            'image' => $image,
            'created' => NewsroomHelper::getFormatedDate(NewsroomPage::DATE_FORMAT, $featured_node->created),
            'teaser' => NewsroomHelper::getFieldTranslatedValue($featured_node, 'field_newsroom_teaser'),
          ));
        }

        cache_set($cache_key, $content, NEXTEUROPA_NEWSROOM_CACHE_TABLE, time() + variable_get('newsroom_ct_type_featured_item', 300));

      }
    }

    return $content;
  }

}
