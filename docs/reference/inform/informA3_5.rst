.. _inform3_5:


.. container:: toggle

  .. container:: header

    See more


  .. container:: infospec

    Note that the *real number string* is distinct from the
    `basic real number string<specA_basic_real_number_string>` in that it
    includes numbers in scientific notation (also called scientific form, standard
    index form, or standard form).

    Where does not contain an exponent term, the number is interpreted as if it was
    just a basic real number string: the exponent is effectively zero.

    For example:

      - :code:`"1.234E03"` is a valid real number string.
      - :code:`"+1.234E03"` is not valid (must not contain the plus sign :code:`+` in the significand)
      - :code:`"1.234E+03"` is valid (a plus sign :code:`+` sign *is* permitted in the exponent)
      - :code:`"1.234E+3.0"` is not valid (the exponent must be an integer)
      - :code:`"123,45E03"` is not valid (the decimal signifier must be a full-stop symbol :code:`.`)
      - :code:`"123.45"` is valid, and is treated as if it were a basic real number string.
      - :code:`0x123abc` is not valid (base 10 numbers only)
