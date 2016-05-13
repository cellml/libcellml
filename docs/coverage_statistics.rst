
===================
Coverage Statistics
===================

The output from the coverage testing using gcov is available `here <coverage/index.html>`_.

.. note::

   The coverage testing pages are **not** currently available on `readthedocs <http://libcellml.readthedocs.io/en/latest/>`_.
   The coverage test sometimes (this behaviour has been observed on OS X using clang) reports single lines containing only a closing curly brace as not covered.  This is currently being treated as a false positive.  This can be seen in the 'Missing' column of the test report where only single lines are reported, for the case discussed here the reported line should only contain a single closing curly brace.  In this situation we will accept the missed coverage report.

