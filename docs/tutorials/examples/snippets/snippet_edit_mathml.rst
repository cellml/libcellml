.. _snippet_edit_mathml:

.. container:: toggle

  .. container:: header-left

    Edit MathML in a component

  MathML is stored as a single string within a component.
  Retrieving it is simple enough using the :code:`math()` function, but any manipulation (change units used, changing variable names, adding additional relationships, etc) are a little more complicated.

  ..

    TODO: Need more examples of useful mathml manipulation. Variable names? Need to remove whitespace first?

  .. tabs::

    .. code-tab:: c++

      void switchUnitsInMaths(std::string &maths, std::string in, std::string out)
      {
          //  Note that this function will replace any and all occurrences of the "in"
          //  string within the "maths" string with the "out" string.  It's worth noting that
          //  in order to be sure that only full name matches for units are replaced, we exploit
          //  the fact that the units names in the MathML string will be in quotation marks, and include
          //  these quotation marks on either side of the in and out strings for safety.

          std::string::size_type n = 0;
          std::string in_with_quotes = "\"" + in + "\"";
          std::string out_with_quotes = "\"" + out + "\"";

          while ((n = maths.find(in_with_quotes, n)) != std::string::npos) {
              maths.replace(n, in_with_quotes.size(), out_with_quotes);
              n += out_with_quotes.size();
          }

          std::cout << "Switched units '" << in << "' for units '" << out << "'" << std::endl;
      }

    .. code-tab:: py

      def switch_units_in_maths(maths, units_in, units_out):
      #   Note that this function will replace any and all occurrences of the "units_in"
      #   string within the "maths" string with the "units_out" string.  It's worth noting that
      #   in order to be sure that only full name matches for units are replaced, we exploit
      #   the fact that the units names in the MathML string will be in quotation marks, and include
      #   these quotation marks on either side of the in and out strings for safety.

      in_with_quotes = "\"" + units_in + "\""
      out_with_quotes = "\"" + units_out + "\""

      new_maths = maths.replace(in_with_quotes, out_with_quotes)

      return new_maths
