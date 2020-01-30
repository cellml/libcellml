.. _libcellml6:


.. container:: libcellml_usage

  Using libCellML there are a couple of things to watch out for.  It
  will allow you import a :code:`Units` item which has a :code:`name`
  attribute that already exists in the importing model (as in this
  example), but will change the imported item's :code:`name` to avoid
  clashes.  The name will have an underscore :code:`_` added, followed
  by an unique integer.  The example would contain two :code:`Units`
  items called :code:`potOfPaint` (the locally defined one) and
  :code:`potOfPaint_1` (the imported one).

  Note that this does *not* imply that the units are equivalent, only
  that the name has been used before.  You can compare two :code:`Units`
  items using these functions:

  .. code-block:: cpp

    // This function will return "true" only when the two Units match exactly.  That is,
    // dimensionallyEquivalent(kilometre, thousand_metres) is true,
    // dimensionallyEquivalent(kilometre, metre) is false (scaling factor difference),
    // dimensionallyEquivalent(kilometre, apple) is false (base unit difference).

    static bool dimensionallyEquivalent(const UnitsPtr &units1, const UnitsPtr &units2);

    // This function will return "true" when the two Units base units match.  That is,
    // equivalent(kilometre, thousand_metres) is true,
    // equivalent(kilometre, metre) is true (scaling factor difference is ignored),
    // equivalent(kilometre, apple) is false (base unit difference).

    static bool equivalent(const UnitsPtr &units1, const UnitsPtr &units2);

    // This function simply returns the scaling factor between two Units
    // such that: units2 = units1*scalingFactor. where the base
    // units match.  Where they don't, it returns 0.
    // scalingFactor(metre, kilometre) returns 1000.0
    // scalingFactor(kilometre, apple) returns 0

    static double scalingFactor(const UnitsPtr &units1, const UnitsPtr &units2);
