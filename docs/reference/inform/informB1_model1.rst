.. _inform4_1:

.. container:: toggle

  .. container:: header

    See more

  .. container:: infospec

    The :code:`model` is the highest level in the CellML file, not including the
    opening :code:`xml` tags.  And, just like the Highlander, there can be only one.

    These are valid CellML name attributes:

      - :code:`myValidName` is valid (both cases are permitted)
      - :code:`my_other_valid_name` is valid (underscores are permitted)
      - :code:`this1too` is valid (numerals 0-9 are permitted)

    These are not valid CellML name attributes:

      - :code:`my invalid name` is not valid (spaces are not permitted)
      - :code:`thisIsInvalidToo!` is not valid (special characters other
        than the underscore :code:`_` are not permitted)
      - :code:`1amNotValidEither` is not valid (must not begin with a number)
      - :code:`" "` empty string is not valid (a name must be present).
