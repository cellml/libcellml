.. _inform8:

.. container:: infospec

    There are two items related to units in CellML, and their naming can be
    confusing, so we'll start with an example first.  Imagine that you need
    to create units that represent a volume flowrate, so :math:`cm^3/s`
    perhaps.

    The :code:`units` item - as with everything else - needs a unique name
    within its scope, and because :code:`units` can only exist as a child of
    a :code:`model`, they must therefore be unique.

    .. code-block:: xml

        <units name="cm3_per_second">
        ...
        </units>

    Now that we've named it, we also need to define it.  In the example, we'll
    need to use two of the *built-in* base units - :code:`metre` and
    :code:`second`, and manipulate them accordingly.  This is done by including
    child :code:`unit` items (these are explained in detail in
    :ref:`the next section<spec9>`).


.. container:: infospec

    Issues related to :code:`units` items
    -------------------------------------

    **TODO** Put list of common errors reported to do with units here.
