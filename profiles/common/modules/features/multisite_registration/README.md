# Installation

- `multisite_registration_standard` should be enabled only on sites running on standard Multisite profile. 
- `multisite_registration_og` should be enabled only on sites running on community Multisite profile.

**Attention**: the `registration_views` module, which is required by both modules above, has a quite an unorthodox way
of exposing relation Views plugins: in order for its relation Views handlers not to be displayed as broken or missing on
Views UI it requires at least one field of type `registration` to be added to at least one content type. 

Site builders should add at least one `registration` field in order for the Multisite Registration modules to work
correctly.
