
===========================
Submitting Code for Testing
===========================

If you wish to test some new code without having to create a pull request you can.  The Buildbot has the capacity to build a libCellML compliant repository through the use of a ForceScheduler.  To make use of this facility you will need to authenticate with the Buildbot system.  Access to this facility is granted on request to David Nickerson <d.nickerson@auckland.ac.nz>.  The Buildbot system uses MD5 encrypted passwords as created by htpasswd.  With your request to David include the output of this command::

   htpasswd -n <your-chosen-username>

The website http://www.htaccesstools.com/htpasswd-generator/ can be used if you do not have access to the htpasswd application.

When your request has been dealt with you will be able to login to the `Buildbot <http://autotest.bioeng.auckland.ac.nz/libcellml-buildbot/builders>`_ and submit code for testing.

