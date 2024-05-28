#pragma once

#include "string"
#include "vector"

// Version 2.12(.7) of LibXml2 reports the following errors,
// used on Windows CI machines.
const std::vector<std::string> expectedLibXml2Issues = {
    "LibXml2 error: Opening and ending tag mismatch: ci line 6 and apply.",
    "LibXml2 error: Opening and ending tag mismatch: ci line 6 and math.",
    "LibXml2 error: Opening and ending tag mismatch: apply line 3 and math_wrap_as_single_root_element.",
};
