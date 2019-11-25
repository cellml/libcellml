..  _builtinunits:

--------------
Built-in units
--------------

The libCellML library includes a set of irreducible units, as well as a
convenience set of their most common combinations.  These built-in units,
and their formation from the irreducible units, are shown in the table below:
the columns indicate the irreducible units, the values shown indicate the
exponent, and the final column contains the multiplier (if used).

Note that there are three effectively dimensionless units:

- the :code:`dimensionless` irreducible unit itself
- the :code:`radian` unit should really be :code:`metre` per :code:`metre`
- the :code:`steradian` unit should really be
  :code:`metre` squared per :code:`metre` squared

.. csv-table::
    :align: right
    :widths: auto

    ,ampere,candela,dimensionless,kelvin,kilogram,metre,mole,second,multiplier
    ampere,1,,,,,,,,
    becquerel,,,,,,,,-1,
    candela,,1,,,,,,,
    coulomb,-1,,,,,,,1,
    dimensionless,,,1,,,,,,
    farad,2,,,,-1,-2,,-4,
    gram,,,,,1,,,,0.001
    gray,,,,,,2,,-2,
    henry,-2,,,,1,2,,-2,
    hertz,,,,,,,,-1,
    joule,,,,,1,2,,-2,
    katal,,,,,,,1,-1,
    kelvin,,,,1,,,,,
    kilogram,,,,,1,,,,
    litre,,,,,,3,,,0.001
    lumen,,1,,,,,,,
    lux,,1,,,,-2,,,
    metre,,,,,,1,,,
    mole,,,,,,,1,,
    newton,,,,,1,1,,-2,
    ohm,-2,,,,1,2,,-3,
    pascal,,,,,1,-1,,-2,
    radian,,,1,,,,,,
    second,,,,,,,,1,
    siemens,2,,,,-1,-2,,3,
    sievert,,,,,,2,,-2,
    steradian,,,1,,,,,,
    tesla,-1,,,,1,,,-2,
    volt,-1,,,,1,2,,-3,
    watt,,,,,1,2,,-3,
    weber,-1,,,,1,2,,-2,
