
.. _coverage_statistics:

===================
Coverage Statistics
===================

The output from the coverage testing using :code:`gcov` is available `here <coverage/index.html>`_.
**TODO** is it gcov or gcovr??

.. note::

   The coverage testing pages are **not** currently available on `Read the Docs <http://libcellml.readthedocs.io/en/latest/>`_.
   The coverage test sometimes (this behaviour has been observed on `macOS <https://en.wikipedia.org/wiki/MacOS>`_ using `Clang <https://clang.llvm.org/>`_) reports single lines containing only a closing curly brace as not covered.
   This is currently being treated as a false positive.
   This can be seen in the 'Missing' column of the test report where only single lines are reported.
   For the case discussed here, the reported line should only contain a single closing curly brace.
   In this situation, we will accept the missed coverage report.
