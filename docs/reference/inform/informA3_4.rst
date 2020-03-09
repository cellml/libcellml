.. _inform3_4:


.. container:: toggle

  .. container:: header

    See more

  .. container:: infospec

    Note that the *basic* real number string is distinct from the
    :ref:`real number string<specA_real_number>`
    in that it does not include real numbers in scientific notation (also called scientific
    form, standard index form, or standard form).

    For example:

      - :code:`"-123.4567"` is a valid basic real number string,
      - :code:`"-1.234567E03"` is not (it's a real number string),
      - :code:`"+123.4567"` is not valid (must not contain the plus sign :code:`+`),
      - :code:`"1234567"` is valid (it's ok to not have a decimal point :code:`.`),
      - :code:`"123,4567"` is not valid (the decimal signifier must be a full-stop symbol :code:`.`),
      - :code:`"12.34.56"` is not valid (maximum of one decimal point :code:`.` is permitted), and
      - :code:`0x123abc` is not valid (base 10 numbers only).
