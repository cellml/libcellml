
.. _libcellml6:

  Using libCellML there are a couple of things to watch out for.  It
  will allow you import a :code:`Units` item which has a :code:`name`
  attribute that already exists in the importing model (as in this
  example), but will change the imported item's :code:`name` to avoid
  clashes.  The name will have an underscore :code:`_` added, followed
  by an unique integer.  The example would contain two :code:`Units`
  items called :code:`potOfPaint` (the locally defined one) and
  :code:`potOfPaint_1` (the imported one).

  Note that this does *not* imply that the units are equivalent, only
  that the name has been used before.  You can check whether or not two
  :code:`Units` are indeed dimensionally equivalent using the function:

  .. code-block:: cpp

    static bool dimensionallyEquivalent(const UnitsPtr &units1, const UnitsPtr &units2);

  .. code-block:: python

    %feature("docstring") libcellml::Units::scalingFactor
"Returns the scaling factor between two Units objects.";

%feature("docstring") libcellml::Units::equivalent
"Tests if two Units are equivalent.";

%feature("docstring") libcellml::Units::dimensionallyEquivalent
"Tests if two Units are dimensionally equivalent.";

    /**
     * @brief Return the scaling factor difference between two @c Units.
     *
     * This can be interpreted as factor, where units2 = (factor)*units1.  This method
     * does not check to see if the units are compatible.
     *
     * @param units1 The first units to compare.
     * @param units2 The second units to compare.
     *
     * @return The factor units1/units2.
     */
    static double scalingFactor(const UnitsPtr &units1, const UnitsPtr &units2);

    /**
     * @brief Test to determine whether two @c Units are equivalent or not.
     *
     * Two @c Units are considered to be equivalent if they share the same units,
     * independently of their dimension (e.g. volt and volt are equivalent as are
     * volt and millivolt).
     *
     * @param1 units1 The first units to compare.
     * @param2 units2 The second units to compare.
     *
     * @return @c true if the two @c Units are equivalent, @c false otherwise.
     */
    static bool equivalent(const UnitsPtr &units1, const UnitsPtr &units2);

    /**
     * @brief Test to determine whether two @c Units are dimensionally equivalent or not.
     *
     * Two @c Units are considered to be dimensionally equivalent if they share the
     * exact same units (e.g. volt and volt are dimensionally equivalent but
     * volt and millivolt are not).
     *
     * @param1 units1 The first units to compare.
     * @param2 units2 The second units to compare.
     *
     * @return @c true if the two @c Units are dimensionally equivalent, @c false
     * otherwise.
     */
    static bool dimensionallyEquivalent(const UnitsPtr &units1, const UnitsPtr &units2);
