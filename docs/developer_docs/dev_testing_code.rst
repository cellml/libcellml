.. _dev_testing_code:

===========================
Submitting Code for Testing
===========================

If you wish to test some new code without having to create a pull request you
can. :buildbot:`Buildbot <>` has the capacity to build a libCellML-compliant
repository through the use of a
`ForceScheduler <http://docs.buildbot.net/latest/developer/cls-forcesched.html>`_.
To make use of this facility, you will need to authenticate with the Buildbot
system.
Access to this facility is granted on request to
`David Nickerson <d.nickerson@auckland.ac.nz>`_.
The Buildbot system uses MD5 encrypted passwords as created by
`htpasswd <https://httpd.apache.org/docs/current/programs/htpasswd.html>`_.

Along with your request to David please include the output of this command::

   htpasswd -n <your-chosen-username>

Alternatively, the online version at
`http://www.htaccesstools.com/htpasswd-generator/ <http://www.htaccesstools.com/htpasswd-generator/>`_
can be used if you do not have access to the :code:`htpasswd` application.

When your request has been dealt with, you will be able to login to the
Buildbot instance at this address:

`http://autotest.bioeng.auckland.ac.nz/libcellml-buildbot/builders <http://autotest.bioeng.auckland.ac.nz/libcellml-buildbot/builders>`_ 

to submit code for testing.
