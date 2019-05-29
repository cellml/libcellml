===========================
Testing libCellML
===========================

If you wish to test some new code without having to create a pull request you can.
`Buildbot <https://buildbot.net/>`_ has the capacity to build a libCellML compliant repository through the use of a `ForceScheduler <http://docs.buildbot.net/latest/developer/cls-forcesched.html>`_.
To make use of this facility, you will need to authenticate with the `Buildbot <https://buildbot.net/>`_ system.
Access to this facility is granted on request to `David Nickerson <d.nickerson@auckland.ac.nz>`_.
The `Buildbot <https://buildbot.net/>`_ system uses MD5 encrypted passwords as created by `htpasswd <https://httpd.apache.org/docs/current/programs/htpasswd.html>`_.
With your request to David include the output of this command::

   htpasswd -n <your-chosen-username>

The website http://www.htaccesstools.com/htpasswd-generator/ can be used if you do not have access to the `htpasswd <https://httpd.apache.org/docs/current/programs/htpasswd.html>`_ application.

When your request has been dealt with, you will be able to login to `Buildbot <http://autotest.bioeng.auckland.ac.nz/libcellml-buildbot/builders>`_ and submit code for testing.
