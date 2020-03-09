.. _inform3_4:


.. container:: toggle

  .. container:: header

    See more

  .. container:: infospec

    A basic real number string is a decimal representation of a floating point number.
    It must be in base 10 (no binary numbers, no hexadecimal numbers), and is a string
    containing only the numerals 0-9, an optional decimal point, and/or a negative sign.

    Note that the *basic* real number string is distinct from the
    :ref:`real number string<specA_real_number_string>` (see below)
    in that it does not include real numbers in scientific notation (also called scientific
    form, standard index form, or standard form).

    For example:

      - :code:`"-123.4567"` is a basic real number string.
      - :code:`"-1.234567E03"` is not (it's a real number string).
      - :code:`"+123.4567"` is not valid (must not contain the plus sign :code:`+`)
      - :code:`"1234567"` is valid (it's ok to not have a decimal point :code:`.`)
      - :code:`"123,4567"` is not valid (the decimal signifyer must be a full-stop symbol :code:`.`)
