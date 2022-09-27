.. _release_process:

===============================
Release process for *libCellML*
===============================

This document details the process for making a release of *libCellML*.
Releases are made using builders from the Buildbot Continuous Integration (CI).
There are four steps in making a release.

1. `Step 1 - Setting the version number`_
2. `Step 2 - Preparing the release`_
3. `Step 3 - Creating the release`_
4. `Step 4 - Finalising the Release`_

Each section has further details on what actions are required for a particular step.
Each step must be done in order from step 1 through to step 4.

For all the steps in creating a release, you must be logged in to the Buildbot CI and be in the *admin* group.
If you are neither of these you will not be able to perform any of these actions.

.. note::

  Merging in pull requests when a release is underway is not recommended and more importantly has not been tested.
  To determine if a release is underway check the repository for the presence of a branch named *version_change* or *release_staging_<version number>*.

Step 1 - Setting the version number
===================================

The version number for the project can be set using the *Set version Builder* (:numref:`libcellml_release_process_set_version_builder`).
The *Set version Builder* sets the version that is entered into the interface, it does not increment the version.
The version that you set in the interface will be applied as is to the codebase.

.. figure:: ./images/release_process/set_version_builder.png
   :align: center
   :alt: Buildbot set version builder.
   :name: libcellml_release_process_set_version_builder

   Set version builder on Buildbot.

libCellML uses semantic versioning as a versioning system, see `Semantic versioning <https://semver.org/>`_ for further information.
As such, each part of the version number carries a specific meaning and when setting a version number you need to make sure you are following semantic versioning rules.
There are no checks to determine if semantic versioning is being followed.
To version number is split into two parts the core version, made up of the major, minor, and patch version identifiers, and the developer version.
An official release is created by leaving the developer version input empty.
The main difference between an official release and a developer release is the assets built by the release process are not uploaded or published to public registries or attached to an associated GitHub release.

.. figure:: ./images/release_process/set_version_builder_interface.png
   :align: center
   :alt: Buildbot set version builder interface.
   :name: libcellml_release_process_set_version_builder_interface

   Set version builder interface.

When the *Start Build* button is pressed (:numref:`libcellml_release_process_set_version_builder_interface`) Buildbot will create an internal pull request on the `cellml/libcellml <https://github.com/cellml/libcellml>`__ GitHub repository.
The pull request will be made from the *version_change* branch to the *main* branch.
The creation of the pull request will trigger a CI build, wait for the CI to finish its checks before merging the pull request.
If, for some reason, the CI checks fail changes may be required.
Changes can be made directly to the *vesion_change* branch but quite likely any such changes will need to be propagated to the CI for a permanent fix.
How changes are propagated to the CI is outside the scope of this document.
When merging the pull request the *version_change* branch will be automatically deleted.

.. note::

  The merging of a *version_change* pull request created by the CI system is exempt from the 'two reviews' required rule.

When the version number has been set in the *main* branch the preparation of the release can start.

Step 2 - Preparing the release
==============================

A release is prepared using the *Prepare Release Builder* (:numref:`libcellml_release_process_prepare_release`).
The *Prepare Release Builder* will create a new branch named *release_staging_<version number>* (where <version number> is an actual semantic version number set in the first step) and generate a changelog.

.. figure:: ./images/release_process/prepare_release_builder.png
   :align: center
   :alt: Buildbot prepare release builder interface.
   :name: libcellml_release_process_prepare_release

   Prepare release builder on Buildbot.

The changelog for a release is generated from information found in merged pull requests between the current release under preparation and the previous release.

.. note::

  The changelog creation is unlikely to be accurate when creating a bug fix/hot fix release on a previously released official version.
  At this time, that means some manual editing of the changelog will need to happen when creating a bug fix/hot fix release.

.. figure:: ./images/release_process/prepare_release_builder_interface.png
   :align: center
   :alt: Buildbot prepare release interface.
   :name: libcellml_release_process_prepare_release_builder_interface

   Prepare release interface.

There are no options for the prepare release builder, there is only one place you can prepare a release from, there is only one place a release is going to be created.
The only thing you can do is start a build, (:numref:`libcellml_release_process_prepare_release_builder_interface`).

The prepare release builder will kick off a round of unit tests as part of the preparation process.

When the release has been prepared the *release_staging_<version number>* branch will have been created and a changelog and table of contents entries for the changelog will have been created.
The changes made for the new changelog should be the only changes from the current *main* branch.

Step 3 - Creating the release
=============================

A release is created using the *Create Release Builder* (:numref:`libcellml_release_process_create_release`).

.. figure:: ./images/release_process/create_release_builder.png
   :align: center
   :alt: Buildbot create release builder interface.
   :name: libcellml_release_process_create_release

   Create release builder on Buildbot.

A release can only be created from a *release_staging_<version number>* branch.
The create release builder interface interrogates `cellml/libcellml <https://github.com/cellml/libcellml>`__ for potential release branches.
Select the release preparation branch (there should only ever be one), to create the release from, and start the build with the *Start Build* button, :numref:`libcellml_release_process_create_release_builder_interface`.

.. figure:: ./images/release_process/create_release_builder_interface.png
   :align: center
   :alt: Buildbot create release interface.
   :name: libcellml_release_process_create_release_builder_interface

   Create release interface showing the branch a release can be created from.

The create release build creates a release on GitHub and adds tags to identify where the release was created from.
The current status for the *release_staging_<version number>* branch will be applied to the *release* branch.
The tagged *release* branch is where the GitHub release will be created from.
When the release is created GitHub actions will take over to build all the assets.
The assets here are the binaries (installers, archives) from: Windows; macOS; Ubuntu; the Python wheels; and, the Javascript package.

.. note::

  **Do not** start the finalise release builder until the GitHub actions have finished.
  This normally takes between 11 - 15 minutes.

Step 4 - Finalising the Release
===============================

The release is finalised using the *Finalise Release Builder* (:numref:`libcellml_release_process_finalise_release`).

.. figure:: ./images/release_process/finalise_release_builder.png
   :align: center
   :alt: Buildbot finalise release builder interface.
   :name: libcellml_release_process_finalise_release

   Finalise release builder on Buildbot.

The finalise release builder interface interrogates `cellml/libcellml <https://github.com/cellml/libcellml>`__ for release branches, and `end-to-end testing framework <https://github.com/libcellml/end-to-end-testing>`__, and `end-to-end testing database <https://github.com/libcellml/end-to-end-test-database>`__ for tags.
Choose the values for finalising the release in the finalise release interface, :numref:`libcellml_release_process_finalise_release_builder_interface`.

.. figure:: ./images/release_process/finalise_release_builder_interface.png
   :align: center
   :alt: Buildbot finalise release interface.
   :name: libcellml_release_process_finalise_release_builder_interface

   Finalise release interface.

The finalise release builder will update the libCellML staging website with the API documentation and the developer documentation.
The user documentation will only be udpated for the release if the end-to-end testing passes.
To this end, it is important to choose the appropriate end-to-end testing tag and end-to-end testing database tag.
If the end-to-end testing passes, the specifics of the versions that the release was tested with will be saved and surfaced on the website.

The last thing that the finalises the release is the merging of the *release_staging_<version number>* into the *main* branch and the deletion of the *release_staging_<version number>* branch.
