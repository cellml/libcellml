.. _informB8:

.. container:: toggle

  .. container:: header

    See more

  .. container:: infospec

    In addition to the standard :code:`name` attribute, each :code:`variable`
    must also define a :code:`units` attribute too.

    Reusing the example from :ref:`The component item<spec_component>` we
    can give the three variables their fuller definitions:

    .. code-block:: xml

      <component name="mass_into_energy">
          <math>
            ...
          </math>
          <variable name="E" units="joule"/>
          <variable name="m" units="kilogram"/>
          <variable name="c" units="metre_per_second"/>
      </component>

    Extra attributes that can be used as needed include the :code:`initial_value`,
    which will either set a constant value for a variable, or set its initial
    conditions if it's being solved for.  More information about initialisation
    can be found in the
    :ref:`Interpretation of initial values<spec_initial_values>` section.

    Finally, where one :code:`variable` has been mapped to another in a different
    component, the :code:`interface` attribute must be specified.  This
    determines the relative position in the encapsulation that the mapped
    component must have in order to access this variable.  This is outlined in
    more detail in :ref:`The encapsulation item<spec_encapsulation>`.

    For examples and further explanation of components and their encapsulation,
    please refer to
    :ref:`section 3 of the Sodium Channel theory<theory_sodiumchannel_interpretation>`.
