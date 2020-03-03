.. _informB2_3:

.. _inform_import3:

.. container:: toggle

  .. container:: header

    See more

  .. container:: infospec

    The intention behind this restriction is to prevent circular import
    definitions from occurring.  Models *are* able to import twins, that is,
    :code:`component` or :code:`units` items which are identical in content
    but under different names.  Models may *not* import themselves, because
    this would create an infinite loop of dependence.

    For example, the first Olsen twins model below is permitted: the same
    component is imported twice under different names.

    .. code-block:: xml

      <model name="olsen_twins">
        <import xlink:href="twin_sister.cellml">
          <component name="mary_kate" component_ref="sister"/>
        </import>
        <import xlink:href="twin_sister.cellml">
          <component name="ashley" component_ref="sister"/>
        </import>
      <model>

    This recursive import is not permitted because a component cannot import itself:

    .. code-block:: xml

      <!-- in a file called "multiplicity.cellml" -->
      <model name="multiplicity">
        <import xlink:href="multiplicity.cellml">
         <component name="doug" component_ref="doug"/>
        </import>
      <model>

    The sames applies for "indirect" imports, where recursion is created over
    several files:

    .. code-block:: xml

      <!-- in a file called "multiplicity.cellml" -->
      <model name="multiplicity">
        <import xlink:href="clone.cellml">
          <component name="doug" component_ref="clone"/>
        </import>
      <model>

      <!-- in a file called "clone.cellml" -->
      <model name="first_clone">
        <import xlink:href="clone_of_clone.cellml">
          <component name="clone" component_ref="another_clone"/>
        </import>
      </model>

      <!-- in a file called "clone_of_clone.cellml" -->
      <model name="repeating_cloning">
        <import xlink:href="multiplicity.cellml">
          <component name="another_clone" component_ref="doug"/>
        </import>
      </model>
