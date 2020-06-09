..container:: heading3

    Understanding units


Some basic units have been defined and built into libCellML, others you can define by combining the built-in ones using scaling factors and exponents, or you can define your own from scratch if need be.

There are four different kinds of units used here: irreducible units, built-in units, derived or combination units, and custom irreducible units.

Irreducible units
-----------------
The first are called *irreducible* because they represent the physical base quantities which cannot be further simplified:

- length (:code:`metre`)
- time (:code:`second`)
- amount of a substance (:code:`mole`)
- temperature (:code:`kelvin`)
- mass (:code:`kilogram`)
- electrical current (:code:`ampere`)
- luminous intensity (:code:`candela`)
- non-dimensional (:code:`dimensionless`)

These *irreducible* units can be used to create all other physically-based units by combining them using different exponents, multipliers, and prefixes.

Built-in units
--------------
Some of these combinations form our second type of units, the *built-in units*, these being common relationships which have been constructed from combinations of the irreducible units.
The combinations can involve:

- A scaling factor (the units :code:`millisecond` is equivalent to
  :code:`second` and a factor of 0.001);
- A combination of units (a :code:`coulomb` is a :code:`second` multiplied by
  an :code:`ampere`);
- Powers of units (a :code:`Hertz` has a base of :code:`second` with an
  exponent of -1); and
- Any combination of the above.

A list of pre-existing *built-in* convenience units is shown in the :ref:`Built-in Units page<builtinunits>`, along with their relationships to the irreducible units.

Combination or derived units
----------------------------
The third type of units are those *combinations* which users can define for themselves based on the built-in units, the irreducible units, any other units already created, or (see below) their own custom irreducible units.

For example, let's say that you want to simulate the time variable, :math:`t`, in units of milliseconds.
This isn't one of the built-in units, so you'll need to define it, but it's easy to see that it's based on the built-in :code:`second`, but needs a scaling factor.

For convenience libCellML gives a variety of options for defining such scaling factors:

-  Either through the use of named prefixes which are listed on the :ref:`Prefix page<prefixes>`, eg: :code:`millisecond` is :code:`second` with :code:`prefix="milli"`;
-  By defining an integer or integer string as a prefix which represents the :math:`log_{10}` of the scaling factor, eg: :code:`millisecond` is :code:`second` with :code:`prefix=-3` gives a scaling factor of :math:`10^{-3}=0.001`.
   NB: using an integer string like :code:`prefix="-3"` gives the same result; and
-  By defining the scaling factor directly, as a multiplier, eg: :code:`millisecond` is :code:`second` with :code:`multiplier=0.001`.

The overloaded argument option list is shown below for each language:

.. code-block:: cpp

    **TODO** Check that this is correct ... ??!!

    void addUnit(const std::string &reference, const std::string &prefix, double exponent = 1.0,
                 double multiplier = 1.0, const std::string &id = "");

    void addUnit(const std::string &reference, Prefix prefix, double exponent = 1.0,
                 double multiplier = 1.0, const std::string &id = "");

    void addUnit(const std::string &reference, int prefix, double exponent,
                 double multiplier = 1.0, const std::string &id = "");

    void addUnit(const std::string &reference, double exponent, const std::string &id = "");

    void addUnit(const std::string &reference);

.. code-block:: python

    addUnit(reference, prefix, exponent=1, multiplier=1)
    addUnit(reference, exponent)
    addUnit(reference)

Note that :code:`reference` can be another unit name string or a :code:`StandardUnits` enum, and :code:`prefix` can be a string or an integer.

To create a :code:`Units` item you need will follow the same basic steps as other entities: declare it, name it, define it, and then add it in.
For example:

.. code-block:: cpp

    // Declare, name, and define a "millisecond" unit pointer.
    auto ms = libcellml::Units::create("millisecond");

    // The manner of specification here is agnostic: all three definitions are identical.
    ms->addUnit("second", "milli");  // reference unit and built-in prefix
    // OR
    ms->addUnit("second", 1.0, -3);  // reference unit, multiplier, exponent
    // OR
    ms->addUnit("second", 1.0, 0, 0.001);  // reference unit, multiplier, exponent

.. code-block:: python

    from libcellml import Units

    # Declare, name, and define a "millisecond" unit pointer.
    ms = Units("millisecond")

    # The manner of specification here is agnostic: all three definitions are identical.
    ms.addUnit("second", "milli")          # reference unit and built-in prefix
    # OR
    ms.addUnit("second", -3, 0.001)        # reference unit, exponent, multiplier
    # OR
    ms.addUnit("second", 1, 1.0, 0.01)     # reference unit, prefix, exponent, multiplier

Units can be defined based on one another as well.
For example, after defining our :code:`millisecond` units, we could then use this definition to define the :code:`per_millisecond` units by simply including it with an exponent of -1:

.. code-block:: cpp

    // Define a per_millisecond unit based on millisecond^-1:
    per_ms->addUnit(ms, -1.0);

.. code-block:: python

    # Defining a per_millisecond unit based on millisecond^-1.
    per_ms.addUnit(ms, -1.0)  # reference unit, exponent

Custom irreducible units
------------------------
The final type of unit is a custom irreducible unit.
While this is not common in purely physical models (all of the seven physical attributes are already included), for times when you're modelling something non-physical (such as our numbers of sharks or fishes), you're able to define your own.
Here's an example.

.. code-block:: cpp

    // Create a custom irreducible unit named "banana".
    auto uBanana = libcellml::Units::create("banana");

    // Note that when a UnitsPtr is defined with a name only (that is, without any
    // calls to the addUnit(...) function), it is effectively irreducible.

    // Create a new compound unit based on the "banana" unit above.
    auto uBunchOfBananas = libcellml::Units::create("bunch_of_bananas");
    u2->addUnit("banana", 5.0);  // include bananas^5 in the bunch_of_bananas unit

.. code-block:: python

    from libcellml import Units

    # Create a custom irreducible unit named "banana".
    uBanana = Units("banana")

    # Note that when a Units is defined with a name only, it is effectively irreducible.

    # Create a new compound unit based on the "banana" unit above.
    uBunchOfBananas = Units("bunch_of_bananas")
    uBunchOfBananas.addUnit("banana", 5.0)  # include bananas^5 in the bunch_of_bananas unit
