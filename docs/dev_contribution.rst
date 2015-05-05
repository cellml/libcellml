.. Contribution documentation for libCellML

============
Contributing
============

This document covers the process to follow for getting your changes into the :term:`prime repository`.  While there are many types of contribution, this section focuses on contributions made through GitHub and Git, or in other words assets that are managed using the version control system.  It is assumed that :doc:`Setup <dev_setup>` and :doc:`Building <dev_building>` have already been read and followed. 

.. contents::

Overview
========

For any body of work intended for the :term:`prime repository` start with a GitHub issue.  The issue can be used to discuss the topic and clarify any problems related to it.  Once progress has been made towards addressing the issue a pull request is created that references the issue.  

Reviewers provide feedback on the changes by adding comments to the pull request or associated commits. The BuildBot build/test procedure will run each time changes are pushed to the pull request's branch, and the results are displayed in the pull request view.

Once all the changes and reviews are complete, one of the :term:`prime repository` owners will merge the pull request into the prime repository, onto the develop branch.

Note that a bug is just a type of issue, and that resolving the bug should have both the implementation to fix the bug and a test that triggers the bug.

:numref:`Figure %s <libcellml-development-process>` gives a graphical overview of the developer contribution process.  For more detail see the text below.

.. _libcellml-development-process:
.. figure:: images/libCellMLProcesses-DevelopmentProcess.png
   :align: center
   :alt: Developer contribution process

   Developer contribution process

GitHub Issue
============

If an issue does not exist for the required work (e.g. implementation of a feature, fixing of a bug), then create a new one.  The issue is the place to discuss the particulars related to the issue, discussions on determining the scope of the issue or clarification of any points that are unclear.

Topic Branch
============

Create a local topic branch to complete the work required for the issue being addressed.  Before creating the topic branch pull the latest changes from the :term:`prime repository` develop branch.  It is recommended to create a topic branch for all work and keep the develop branch up-to-date with the :term:`prime repository` develop branch.  Doing this will make it easier to have multiple topic branches at once and keep them concurrent with the :term:`prime repository` develop branch.

The following Git command line commands show an example of how to create a topic branch for fixing a (hypothetical) bug described in `issue #46`::

   git fetch prime develop
   git checkout develop # Not required if already on develop branch
   git merge prime/develop
   git checkout -b iss46

Test Driven Development
=======================

Test driven development entails writing a test that covers the intended functionality (this may require a suite of tests to be written) and no more.  The tests will require some skeleton implementation so that the test(s) can compile but by definition not pass, at least not pass all the tests.  The purpose of this is two-fold: 1. Writing the test(s) first sets out the intended design which can be shared through a pull request.  2. The skeleton implementation will include the documentation clearly describing the intended purpose.  Following this contribution process allows others to comment and make corrections before time is spent on the functional code. 

It may be necessary to refactor the current desgin to enable the easiest possible way to add the new feature.  This is a good thing as the quality of the design improves this makes it easier to work with in the future.  Refactoring means improving the code without adding features, and the tests provide validation that the refactored code performs as well as before.

For simple or obvious bugs which have fallen through the testing gaps just the implementation is fine.

GitHub Pull Request
===================

Once some changes have been made and local commits committed push your changes to your GitHub libcellml repository.  From there create a pull request from your topic branch to the :term:`prime repository` develop branch.  When creating the pull request make sure to add in the comment 'addresses issue #46' (of course replace the number 46 with the actual number of the issue you are addressing), or something to that effect.  This will create a link between the issue and the pull request enabling other people to see that you are working on this issue and comment on your work.  

The following Git command line commands show an example of how to add all files, commit the changes and push them to a GitHub repository for the first time::

   git add .
   git commit -m "Appropiately descriptive message about the changes made."
   git push -u origin iss46

The 'git add' and 'git commit' commands should be obvious,  the 'git push' command sets the local branch 'iss46' to be linked with the remote branch 'iss46' in the origin (the default shorthand for your libCellML repository on GitHub) repository, this branch will be created in the origin repository if it doesn't already exist.  

To create a pull request from one GitHub repository to another follow the instructions `here <https://help.github.com/articles/creating-a-pull-request/>`_.

Satisfy Comments
================

It is important to respond to all feedback appropriately, the review process will check to make sure that all comments have been dealt with.  Feel free to respond to comments as appropriate, e.g. through code changes, posting a direct reply etc.

Review
======

It may happen that submitted work is not reviewed immediately or the work is finished before any comments have been made.  If this is the case add a comment to the pull request asking for the submission to be reviewed.  An email will be sent out to the repository owners who will respond and review the submission, please remember that everyone is busy and it may not happen right away.

Completion
==========

Once the owners of the :term:`prime repository` are satisfied that the work on the issue is complete and that the feedback has been addressed, one of the owners will post a comment on the issue notifying subscribers that they intend to merge the pull request.  If no further objections are raised the owner will merge an close the pull request as outlined in :doc:`Reveiw Process <dev_review>`.

