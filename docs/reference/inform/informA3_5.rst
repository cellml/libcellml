.. _inform3_5:


.. container:: toggle

  .. container:: header

    See more


  .. container:: infospec

    Note that the *real number string* is distinct from the
    :ref:`basic real number string<specA_basic_real_number_string>` in that it
    includes numbers in scientific notation (also called scientific form, standard
    index form, or standard form).

    Where it does not contain an exponent term, the number is interpreted as if it was
    a basic real number string: the exponent term is effectively zero.

    For example:

      - :code:`"1.234E03"` is a valid real number string.
      - :code:`"+1.234E03"` is not valid (must not contain the plus sign :code:`+` in the significand)
      - :code:`"1.234E+03"` is valid (a plus sign :code:`+` sign *is* permitted in the exponent)
      - :code:`"1.234E+3.0"` is not valid (the exponent must be an integer)
      - :code:`"1.234e3"` is valid (either case of `E` or `e` is permitted)
      - :code:`"123,45E03"` is not valid (the decimal signifier must be a full-stop symbol :code:`.`)
      - :code:`"123.45"` is valid, and is treated as if it were a basic real number string.
      - :code:`"123.45E"` is not valid (if the exponent is present it may not be blank)
      - :code:`0x123abc` is not valid (base 10 numbers only)
