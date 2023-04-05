
#pragma once


// Version 2.9.11 of LibXml2 reports the following errors,
// used on macOS 13 machines.
const std::vector<std::string> expectedLibXml2Issues = {
    "LibXml2 error: Opening and ending tag mismatch: ci line 6 and apply.",
    "LibXml2 error: Opening and ending tag mismatch: ci line 6 and math.",
    "LibXml2 error: Opening and ending tag mismatch: apply line 3 and math_wrap_as_single_root_element.",
    "LibXml2 error: Premature end of data in tag math line 2.",
    "LibXml2 error: Premature end of data in tag math_wrap_as_single_root_element line 1.",
};

