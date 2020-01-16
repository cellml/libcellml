.. _4_model_formal:

4. The model element information item
=====================================

4.1. Top-level of CellML infosets
---------------------------------

The top-level element information item in a CellML infoset MUST be an
element information item in the CellML namespace with a local name equal
to :code:`model`. In this specification, the top-level element information
item is referred to as the :code:`model` element.

.. _specific-information-items-1:

4.2. Specific information items
-------------------------------

1. Every :code:`model` element MUST contain an unprefixed :code:`name`
   attribute. The value of the :code:`name` attribute MUST be a valid CellML
   identifier.

2. A :code:`model` element MAY contain one or more additional specific
   information item children, each of which MUST be of one of the
   following types:

   1. A :code:`component` element; or

   2. A :code:`connection` element; or

   3. An :code:`encapsulation` element; or

   4. An :code:`import` element; or

   5. A :code:`units` element;

3. A :code:`model` element MUST NOT contain more than one :code:`encapsulation`
   element.
