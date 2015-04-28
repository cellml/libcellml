.. libCellML Review Process::

==============
Review Process
==============

Check for the Green Tick
========================

Before accepting a tranche of work into the libCellML prime repository check that Buildbot has tested and passed the code.  The status of the code is shown in the last commit of a pushed group of commits in the pull request.  The last commit will have a red cross for a failed build or a green tick for a passed build.  Obviously make sure that the last commit has a green tick before merging.

Coding Standard
===============

Currently there is no coding standard set, but the google coding standard can be considered a baseline for the standard of code that is expected for libCellML.  See the coding standard document for deviations from this standard.

Merging
=======

When merging a pull request the reviewer should add a comment so that the corresponding issue is closed.  This can be done by adding a directive to the merge commit, like so::

   closes #2

where the numeral corresponds to the issue that needs to be closed.  You can use other directives that will achieve the same outcome, `here <https://help.github.com/articles/closing-issues-via-commit-messages/>`_ is a list of all directives that will work on GitHub.
