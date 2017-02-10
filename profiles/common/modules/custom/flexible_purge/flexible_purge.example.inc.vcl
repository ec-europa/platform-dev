# Handle PURGE requests emitted by the "Flexible Purge" Drupal module.
sub handle_flexible_purge_requests {
    call check_invalidate_headers;
    if (req.http.X-Invalidate-Type == "full") {
        if (req.http.X-Invalidate-Tag) {
            ban("obj.http.X-Application-Tag == " + req.http.X-Invalidate-Tag);
            error 200 "OK";
        }
        elseif (req.http.X-Invalidate-Host && req.http.X-Invalidate-Base-Path) {
            ban("obj.http.X-Host == " + req.http.X-Invalidate-Host + " && obj.http.X-Url ~ ^" + req.http.X-Invalidate-Base-Path);
            error 200 "OK";
        }
    }
    elseif (req.http.X-Invalidate-Type ~ "^(wildcard|regexp-(multiple|single))$") {
        if (req.http.X-Invalidate-Regexp) {
            if (req.http.X-Invalidate-Tag) {
                ban("obj.http.X-Application-Tag == " + req.http.X-Invalidate-Tag + " && obj.http.X-Url ~ " + req.http.X-Invalidate-Regexp);
                error 200 "OK";
            }
            else if (req.http.X-Invalidate-Host) {
                ban("obj.http.X-Host == " + req.http.X-Invalidate-Host + " && obj.http.X-Url ~ " + req.http.X-Invalidate-Regexp);
                error 200 "OK";
            }
        }
    }
    error 400 "Bad request";
}

# Sanitize known headers with the intent of using them to compose ban
# statements.
# Ban statements generated from VCL code do not need to have their arguments
# surrounded with double quotes (this makes sense only when working with CLI
# tools such as varnishadm).
# Still, we must prevent ban injections by refusing to include HTTP headers
# containing " && " into the ban statement as they are very likely to be an
# injection attempt.
sub check_invalidate_headers {
    if (req.http.X-Invalidate-Tag ~ " && ") {
        error 400 "Bad request";
    }
    if (req.http.X-Invalidate-Host ~ " && ") {
        error 400 "Bad request";
    }
    if (req.http.X-Invalidate-Base-Path ~ " && ") {
        error 400 "Bad request";
    }
    if (req.http.X-Invalidate-Regexp ~ " && ") {
        error 400 "Bad request";
    }
}
