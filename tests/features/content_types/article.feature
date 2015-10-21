Feature: Article content type
  In order to manage articles on the website
  As an editor
  I want to be able to create, edit and delete articles

  @api
  Scenario: Create an article
    Given I am viewing an "article" content:
      | title            | EC decides tax advantages for Fiat and Starbucks are illegal                                                                     |
      | body             | Commissioner Margrethe Vestager stated that tax rulings that reduce a company's tax burden are not in line with state aid rules. |
      | tags             | State aid, Corporate tax law, Luxembourg, The Netherlands                                                                        |
      | moderation state | Published                                                                                                                        |
    Then I break
