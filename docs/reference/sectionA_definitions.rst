.. _sectionA_definitions:

**CellML 2.0 Specification**

**Authors:**

Michael T. Cooling\*

Michael Clerx

Jonathan Cooper

David P. Nickerson

**Contributors:**

Jesús C. Fernández

David Brooks

Koray Atalag

Alan Garny

The authors also wish to acknowledge the significant contribution of the
(discontinued) draft CellML 1.2 specification, much of the text of which
was incorporated into this specification - although the semantics have
changed considerably. The CellML 1.2 specification was itself the result
of a collaborative effort by a number of researchers during 2008-2011:

Andrew K. Miller (who wrote the text reused here), Jonathan Cooper,
Justin Marsh, Alan Garny, Randall Britten, Poul Nielsen and David P.
Nickerson

\* corresponding author: mtcooling.research@gmail.com

**Preamble**

This document is the normative version of the CellML Specification,
defining the CellML syntax and the rules by which it should be used. It
is intended primarily for the developers of software tools which
directly consume CellML syntax. Users of CellML models should read the
informative version of the CellML Specification which is available here:
https://doi.org/science/1.1.1.10.


.. sectnum::

.. marker1

Terminology
===========

The keywords “MUST”, “MUST NOT”, “REQUIRED”, “SHALL”, “SHALL NOT”,
“SHOULD”, “SHOULD NOT”, “RECOMMENDED”, “MAY”, and “OPTIONAL” in this
document are to be interpreted as described in `RFC
2119 <http://www.ietf.org/rfc/rfc2119.txt>`__.

The key phrase “information item”, as well as any specific type of
information item such as an “element information item”, are to be
interpreted as described in `XML Information
Set <http://www.w3.org/TR/2004/REC-xml-infoset-20040204/>`__.

.. glossary::

   CellML infoset

      An XML information set containing a hierarchy of information items
      conforming to the rules described in this document. In this
      specification such infosets are assumed to be CellML 2.0 infosets.

   CellML model

      A mathematical model represented by a hierarchy of one or more CellML
      infosets, according to the rules described in this document. In this
      specification, the topmost CellML infoset in a hierarchy is referred
      to as the top-level CellML infoset.

   Namespace

      An XML namespace, as defined in `Namespaces in XML
      1.1 <https://www.w3.org/TR/2006/REC-xml-names11-20060816/>`__.

   CellML namespace

      The CellML 2.0 namespace.

   CellML 2.0 namespace

      The namespace http://www.cellml.org/cellml/2.0#.

   MathML namespace

      The namespace http://www.w3.org/1998/Math/MathML.

   CellML information item

      Any information item in the :term:`CellML namespace`.

   Basic Latin alphabetic character

      A Unicode character in the range
      `U+0041 <http://www.fileformat.info/info/unicode/char/0041/index.htm>`__
      to
      `U+005A <http://www.fileformat.info/info/unicode/char/005A/index.htm>`__
      or in the range
      `U+0061 <http://www.fileformat.info/info/unicode/char/0061/index.htm>`__
      to
      `U+007A <http://www.fileformat.info/info/unicode/char/007A/index.htm>`__.

   European numeral

      A Unicode character in the range
      `U+0030 <http://www.fileformat.info/info/unicode/char/0030/index.htm>`__
      to
      `U+0039 <http://www.fileformat.info/info/unicode/char/0039/index.htm>`__.

   Basic Latin alphanumeric character

      A Unicode character which is either a basic Latin alphabetic
      character or a European numeral.

   Basic Latin underscore

      The Unicode character
      `U+005F <http://www.fileformat.info/info/unicode/char/005F/index.htm>`__.

   Basic Latin plus

      The Unicode character
      `U+002B <http://www.fileformat.info/info/unicode/char/002b/index.htm>`__.

   Basic Latin minus

      The Unicode character
      `U+002D <http://www.fileformat.info/info/unicode/char/002d/index.htm>`__.

   Basic Latin full stop

      The Unicode character
      `U+002E <http://www.fileformat.info/info/unicode/char/002e/index.htm>`__.

   Whitespace character

      Any one of the Unicode characters
      `U+0020 <http://www.fileformat.info/info/unicode/char/0020/index.htm>`__,
      `U+0009 <http://www.fileformat.info/info/unicode/char/0009/index.htm>`__,
      `U+000D <http://www.fileformat.info/info/unicode/char/000D/index.htm>`__
      or
      `U+000A <http://www.fileformat.info/info/unicode/char/000A/index.htm>`__.

..  marker2

CellML information sets
=======================

CellML and XML
-------------------

#. Every CellML infoset SHALL be represented in an XML information set
   which conforms with the well-formedness requirements of `XML
   1.1 <http://www.w3.org/TR/xml11/>`__.

#. In this document, the remaining provisions relating to CellML
   infosets SHALL be interpreted as additional constraints on the XML
   information set represented by a CellML infoset.

Specific information items
-------------------------------

#. For the purposes of this specification, a specific information item
   is one of the following (see
   https://www.w3.org/TR/xml-infoset/#infoitem for definitions):

   #. A document information item;

   #. An element information item;

   #. An attribute information item;

   #. A processing instruction information item;

   #. An unexpanded entity reference information item;

   #. A document type declaration information item;

   #. An unparsed entity information item;

   #. A notational information item.

#. Specific information items MUST NOT appear in a CellML infoset except
   where explicitly allowed by this specification, or where allowed by a
   normative specification referenced by this specification.

#. The order in which specific information items appear, as children of
   an element information item defined in this specification, SHALL NOT
   affect the semantic interpretation of the CellML model.

.. _semantic_equivalence:

Semantically equivalent CellML infosets
---------------------------------------

#. Two CellML infosets SHALL be deemed semantically equivalent if one
   can be transformed into the other by making zero or more of the
   following changes:

   #. Adding, removing, and/or modifying comment information items.

   #. Changing (inserting, removing, and/or modifying) one or more
      namespace information items, and/or modifying the prefix of one or
      more information items, without changing the namespace that any
      information item is in.

   #. The following paragraph applies only to character information
      items which are the direct child of an element information item in
      a :term:`CellML namespace`, or in the MathML namespace.

      Inserting or removing character information items that consist
      entirely of whitespace characters, changing the number of whitespace
      characters in such an information item, or changing the number of
      whitespace characters at the beginning or end of any character
      information item.


Character information items
--------------------------------

#. An element information item in the :term:`CellML namespace` MUST NOT contain any
   character information items, except for character information items
   which consist entirely of whitespace characters.

Use of namespaces
----------------------

#. Element and attribute information items in a CellML infoset MUST
   belong to one of the following namespaces, unless explicitly
   indicated otherwise:

   #. The :term:`CellML namespace`

   #. The MathML namespace

XML ID Attributes
----------------------

#. Any element information item in the :term:`CellML namespace` MAY contain an
   unprefixed attribute information item with local name :code:`id.` This
   attribute information item SHALL be treated as having attribute type
   ID, as defined in `section
   3.3.1 <http://www.w3.org/TR/xml11/#sec-attribute-types>`__ of `XML
   1.1 <http://www.w3.org/TR/xml11/>`__.

.. marker3

Data representation formats in CellML
========================================

The following data representation formats are defined for use in this
specification:

1. A CellML identifier:

   #. SHALL be a sequence of Unicode characters.

   #. SHALL NOT contain any characters except Basic Latin alphanumeric
      characters and Basic Latin underscores.

   #. SHALL contain at least one :term:`alphabetic<Basic Latin alphabetic character>` character.

   #. SHALL NOT begin with a numeral or an underscore.

   #. SHALL, when comparing two identifiers, be considered identical to
      another identifier if and only if both identifiers have identical
      sequences of characters.

.. marker3_2

2. A non-negative integer string:

   #. SHALL be a base 10 representation of a non-negative integer.

   #. SHALL consist entirely of Basic Latin numerals.

.. marker3_3

3. An integer string:

   #. SHALL be a base 10 representation of an integer.

   #. SHALL, when the integer being represented is negative, consist of
      the Basic Latin hyphen-minus character
      `U+002D <http://www.fileformat.info/info/unicode/char/002D/index.htm>`__,
      followed by the non-negative integer string representation of the
      absolute value of the integer.

   #. SHALL, when the integer being represented is non-negative, consist
      of the non-negative integer string representation of the integer.

.. marker3_4

4. A basic real number string:

   #. SHALL be a base 10 representation of a real number.

   #. SHALL, when the basic real number being represented is negative,
      begin with the Basic Latin hyphen-minus character
      `U+002D <http://www.fileformat.info/info/unicode/char/002D/index.htm>`__
      as the sign indicator.

   #. MAY contain a single decimal point separator, which SHALL be the
      Basic Latin full stop character
      `U+002E <http://www.fileformat.info/info/unicode/char/002E/index.htm>`__.

   #. SHALL, other than the sign indicator and the decimal point
      separator, consist only of Basic Latin numerals.

.. marker3_5

5. A real number string:

   #. SHALL be a base 10 representation of a real number
      *r*\ =\ *s*\ ⋅10\ *e*, where *s* is the significand, a real
      number, and *e* is the exponent, an integer.

   #. The representation of the number SHALL be the representation of
      the significand followed immediately by the representation of the
      exponent.

   #. The significand SHALL be represented as a basic real number
      string.

   #. An exponent SHALL be represented by an exponent separator
      character, followed by the integer string representation of the
      value of the exponent. Non-negative exponents MAY begin with the
      Basic Latin plus sign character
      `U+002B <http://www.fileformat.info/info/unicode/char/002B/index.htm>`__
      as the sign indicator. The exponent separator character SHALL be
      either the Basic Latin ‘E’ character
      `U+0045 <http://www.fileformat.info/info/unicode/char/0045/index.htm>`__
      or the Basic Latin ‘e’ character
      `U+0065 <http://www.fileformat.info/info/unicode/char/0065/index.htm>`__.

   #. A real number string without an exponent SHALL be a basic real
      number string.
