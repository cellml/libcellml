.. _libCellMLCurrentThinking:

==============================
Current Thinking for libCellML
==============================

This document simply outlines some of the current rationale that has an influence on how the codebase is developed.

- Not dealing with external documents.

  - Absolves libcellml from fetching files and communicating across the Internet.
  - Expect to provide another layer that would perform this role as a separate thing.
  - No avenue to retrieve external references.

- Serialise and deserialise from a string.
- Present a useful interface not one tied to `XML <https://www.w3.org/XML/>`_ structure.
- Validation is going to be quite separate (you are free to make invalid `CellML <https://www.cellml.org/>`_ models).
- Not creating our own `MathML <https://www.w3.org/Math/>`_ object model.

  - Treat `MathML <https://www.w3.org/Math/>`_ as a string.
  - Enables libCellML development to focus on getting core "`CellML <https://www.cellml.org/>`_" support.
  - Expect to provide another layer that would handle `MathML <https://www.w3.org/Math/>`_ as a separate thing.
