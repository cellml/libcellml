.. _libCellMLCurrentThinking:

==============================
Current Thinking for libCellML
==============================

This document simply outlines some of the current rationale that has an influence on how the codebase is developed.

- Not dealing with external documents.

  - Absolves libcellml from fetching files and communicating across the internet.
  - Expect to provide another layer that would perform this role as a separate thing.
  - No avenue to retrieve external references.

- Serialise and deserialise from a string.
- Present a useful interface not one tied to XML structure.
- Validation is going to be quite separate (you are free to make invalid CellML models).
- Not creating our own MathML object model

  - Treat MathML as a string.
  - Enables libCellML development to focus on getting core "CellML" support.
  - Expect to provide another layer that would handle MathML as a separate thing.
