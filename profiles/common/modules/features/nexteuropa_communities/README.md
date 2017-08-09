NextEuropa communities
======================

The 'Communities' features supplies default settings and permissions for group management.

## Features

- Group content type 'community'
- Node alias pattern for group and group post
- Og context negotiation
- Context for communities
- Community's menu
- Private area management for the community part.

## Installation

Enable the nexteuropa_communities feature.

## Configuration

- Feature configuration page on "admin/config/nexteuropa_communities".

  - The first setting *Url Keyword* defines the word in the url triggering the detection of a community context. By default *community* is used in all community content.
  - *Community group content types* is defined to avoid issue if the OG module is used outside of the *nexteuropa_communities* feature.

- Private member area can be configured at "admin/config/nexteuropa_communities/nexteuropa_private_area".

  - The private area is used to define restricted access to a site communities. When this setting is to true, you can use the "access private area" permission to filter the access communities. 

## Testing

The behat test is located in the file "tests/features/nexteuropa_communities.feature"
