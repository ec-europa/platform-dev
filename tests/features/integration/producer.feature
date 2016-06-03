@api @integration
Feature: Producer

  Background:
    Given the following languages are available:
      | languages |
      | en        |
      | fr        |
      | de        |
      | it        |

#    Given the module is enabled
#      | modules                |
#      | nexteuropa_integration |
#      | integration_producer   |

    Given a "page" resource schema:
      | title | Title |
      | body  | Body  |

    And a "memory" backend:
      | plugin          | memory_backend |
      | resource_schema | page           |

  Scenario: Site can produce valid documents

    Given I create the following multilingual "page" content:
      | language | title                        |
      | en       | This title is in English     |
      | fr       | Ce titre est en Français     |
      | de       | Dieser Titel ist auf Deutsch |

    And a "page" producer:
      | plugin           | node_producer |
      | bundle           | page          |
      | backend          | memory        |
      | resource_schema  | page          |

    And the following mapping for the "page" producer:
      | title | title |
      | body  | body  |

    Then a document build by the "page" producer for "page" content with title "This title is in English" should have:
      | fields.title.en | This title is in English     |
      | fields.title.fr | Ce titre est en Français     |
      | fields.title.de | Dieser Titel ist auf Deutsch |


