.. _index_reference:

==========================================
Normative specification for CellML2.0
==========================================

The first section here includes the normative specification documentation for
the CellML format.  This is the "official" statement and rules about what must
and must not be included in order for a model to be valid CellML.

In libCellML the :code:`Valdiator` functionality tests *only* against this
formal specification, and therefore gives no feedback on whether the given
CellML model can be run, or represents a meaningful simulation.

Additional information to the user is given through those parts of libCellML
which are not directly concerned with the CellML format; namely, the
:code:`Generator` class.  The rules and guidelines for this functionality are
therefore defined separately in the second part of this section.

It should be noted that all messages returned from libCellML should contain a
reference number.  This number will point to the section of the formal
specification and/or guidelines to which it relates.


Section A: Preamble and definitions
===================================

.. toctree::
    :maxdepth: 2
    :numbered:
    :glob:

    sectionA*

Section B: Element information items
====================================

.. toctree::
    :maxdepth: 2
    :numbered:
    :glob:

    sectionB*

Section C: Interpretation of CellML models
==========================================

.. toctree::
    :maxdepth: 2
    :numbered:
    :glob:

    sectionC*

Section D: References
=====================

.. toctree::
    :maxdepth: 2
    :numbered:
    :glob:

    sectionD*




Additional references for libCellML
-----------------------------------

.. toctree::
    :maxdepth: 2
    :titlesonly:
    :glob:

    ref*
