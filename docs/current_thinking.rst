.. _libCellMLCurrentThinking:

==============================
Current Thinking for libCellML
==============================

This document simply outlines some of the rationale that has an influence on how the codebase is developed.

 - Not dealing with external documents
 
  - absolves libcellml from fetching files and communicating across the internet.
  - expect to provide another layer that would perform this role as a separate thing
  - no avenue to retrieve external references
  
 - Serialise and Deserialise from a string
 - Present a useful interface not tied to XML structure
 - Validation is going to be quite a separate (you are free to make invalid CellML models)

