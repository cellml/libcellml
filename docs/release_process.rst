.. _release_process:

===============================
Release process for *libCellML*
===============================

The purpose of this document is to describe the process for preparing, reviewing, creating, and finalising releases of *libCellML* using GitHub Actions Continuous Integration (CI).

The target audience of this document are the developers of *libCellML* who have write authority to the `cellml/libcellml <https://github.com/cellml/libcellml>`_ repository.

Releases are made using GitHub Actions CI and consist of four steps:

1. `Step 1 - Preparing the release`_
2. `Step 2 - Checking the release`_
3. `Step 3 - Make the release`_
4. `Step 4 - Finalising the Release`_

Each step must be performed in order. Later steps assume that all previous steps have completed successfully.

Prerequisites
=============

For all steps in the release process, you must:

- Be a maintainer (have write access) of the *cellml/libcellml* GitHub repository.
- Be familiar with semantic versioning.
- Ensure that no other release is currently in progress.

.. note::

  Merging pull requests while a release is under way is not recommended and has not been tested.
  Before starting a new release, check the repository for the presence of a branch named *release-staging-v<version number>*.
  The presence of such a branch indicates that a release is already in progress.

Branch model overview
=====================

The *main* branch is the primary development branch where normal feature development occurs.
The *release* branch represents the base for all released versions of *libCellML*.
Release staging branches, named *release-staging-v<version number>*, are temporary branches used to assemble, review, and validate a candidate release before it is finalised.

Step 1 - Preparing the release
==============================

The *Prepare Release* GitHub Actions workflow prepares a release candidate using information supplied when the workflow is triggered.

This workflow performs the following tasks:

- Collects all changes that will make up the release from a specified source branch.
- Generates a changelog summarising the merged pull requests included in the release.
- Updates version numbers throughout the codebase.

These changes are separated into multiple commits (for example, content changes, changelog generation, and version updates) to make reviewing the release easier.

The workflow creates a staging branch in the repository that contains all proposed release changes.
The source branch is typically the *main* branch (which is the default), but it may be any branch or tag in the repository.
The staging branch is named *release-staging-v<version number>*, where <version number> is the version number specified when triggering the workflow.

The workflow can be triggered from the *Actions* tab of the `cellml/libcellml <https://github.com/cellml/libcellml/actions/workflows/release-prepare.yml>`__ repository.

This workflow is manually triggered and requires a version number to be provided using the GitHub Actions user interface.

.. figure:: ./images/release_process/prepare_release_interface.png
   :align: center
   :alt: GitHub Actions prepare release workflow interface.
   :name: libcellml_release_process_prepare_release_interface

   *Prepare Release* interface on GitHub.

Version numbers must follow semantic versioning rules. See `Semantic Versioning <https://semver.org/>`_ for further information.
Examples of valid version numbers include:

- 1.0.0
- 1.0.0-alpha
- 1.0.0-alpha.1
- 1.0.0-beta
- 1.0.0-beta.2
- 1.0.0-rc.1
- 1.0.0-rc.1+build.1
- 1.0.0-post.1

There are no explicit checks to ensure that version numbers strictly follow semantic versioning conventions; however, the workflow will fail if the supplied version number cannot be parsed as a semantic version.

The version number is split into two components: a core version (major, minor, and patch numbers) and an optional developer suffix.
An official release is created by omitting the developer suffix.
Developer releases include a suffix and differ from official releases in that the resulting assets are not published to public registries or attached to a GitHub release.

On successful completion, this workflow creates a pull request on the `cellml/libcellml <https://github.com/cellml/libcellml>`_ repository with *release* as the base branch and the newly created staging branch as the head branch.

If the workflow fails, the pull request will not be created. Depending on how far the workflow progressed before failure, the staging branch may still exist and may need to be cleaned up manually or reused after resolving the issue.

Next Step
---------

Once the pull request has been created, the checking of the release can begin (see `Step 2 - Checking the release`_).

Step 2 - Checking the release
=============================

The *Check Release* GitHub Actions workflow validates the staged release candidate created in `Step 1 - Preparing the release`_.
It ensures that the code builds correctly and that automated tests have been executed before proceeding with the release.

Procedure
---------

1. Navigate to the *Check Release* workflow in the GitHub Actions tab of the `cellml/libcellml <https://github.com/cellml/libcellml>`_ repository.
2. Optionally adjust the configuration parameters for the end-to-end tests using the GitHub Actions interface.
3. Manually trigger the workflow.
4. Review the results published as comments on the staging pull request.

.. figure:: ./images/release_process/check_release_interface.png
   :align: center
   :width: 25%
   :alt: GitHub Action check release manual trigger interface.
   :name: libcellml_release_process_check_release_interface

   *Check Release Builder* interface from GitHub Action.

Tasks performed
---------------

The workflow performs the following tasks on the staged release code:

- Builds the codebase.
- Runs all unit tests.
- Reports on status of unit tests.
- Runs end-to-end tests.
- Reports on status of end-to-end tests along with the metadata used for running the tests.

Results
-------

Results from the workflow are published as comments on the staging pull request:

- **Unit test results**: A summary indicating whether all tests passed.
- **End-to-end test results**: A summary of the outcome along with the metadata used during test execution.

.. figure:: ./images/release_process/check_release_unit_test_comment.png
   :align: center
   :alt: GitHub Action check release unit test passing comment.
   :name: libcellml_release_process_check_release_unit_test_comment

   Example of the comment left by the *Check Release Builder* showing the unit tests have passed.

.. figure:: ./images/release_process/check_release_end_to_end_comment.png
   :align: center
   :alt: GitHub Action check release end-to-end passing comment.
   :name: libcellml_release_process_check_release_end_to_end_comment

   Example of the comment left by the *Check Release Builder* showing the unit tests have passed.

These comments must be reviewed before proceeding to the next step.

Success criteria
----------------

A release candidate is considered valid when:

- ✅ All unit tests pass (**required**).
- ⚠️ End-to-end tests may fail, but this has consequences.

If end-to-end tests fail:

- The release **may still proceed**, however:
  - The user documentation will **not** be updated as part of the release process.
  - The metadata recorded in the workflow comment will be used by subsequent workflows to finalise documentation updates on the libcellml.org website.

Failure handling
----------------

- If **unit tests fail**:
  - The release **must not proceed**.
  - The staged release should be removed and fixes applied to the source branch before starting the release process again.

- If **end-to-end tests fail**, either:
  - Continue with the release, understanding that the user documentation will not be updated.
  - Or, fix the issues stemming from the end-to-end testing and re-run the workflow.

Next step
---------

Once all required checks have passed and the results have been reviewed, the release process can continue with `Step 3 - Make the release`_.

Step 3 - Make the release
=========================

A release is created using the *Create Release Builder* (:numref:`libcellml_release_process_create_release`).

.. figure:: ./images/release_process/create_release_builder.png
   :align: center
   :alt: Buildbot create release builder interface.
   :name: libcellml_release_process_create_release

   *Create Release Builder* on Buildbot.

A release can only be created from a *release_staging_<version number>* branch.
The *Create Release Builder* interface interrogates `cellml/libcellml <https://github.com/cellml/libcellml>`__ for potential release branches.
Select the release preparation branch (there should only ever be one), to create the release from, and start the build with the *Start Build* button, :numref:`libcellml_release_process_create_release_builder_interface`.

.. figure:: ./images/release_process/create_release_builder_interface.png
   :align: center
   :alt: Buildbot create release interface.
   :name: libcellml_release_process_create_release_builder_interface

   *Create Release Builder* interface showing the branch a release can be created from.

The *Create Release Builder* creates a release on GitHub and adds tags to identify where the release was created from.
The current status for the *release_staging_<version number>* branch will be applied to the *release* branch.
The tagged *release* branch is where the GitHub release will be created from.
When the release is created GitHub actions will take over to build all the assets.
The assets here are the binaries: installers and archives from Windows, macOS, and Ubuntu; Python wheels; and, the Javascript package.

.. note::

  **Do not** start the *Finalise Release Builder* until the deploy libCellML GitHub action has finished.
  The GitHub action for deploying libCellML is currently taking between 11 and 15 minutes to complete.

Step 4 - Finalising the Release
===============================

The release is finalised using the *Finalise Release Builder* (:numref:`libcellml_release_process_finalise_release`).

.. figure:: ./images/release_process/finalise_release_builder.png
   :align: center
   :alt: Buildbot finalise release builder interface.
   :name: libcellml_release_process_finalise_release

   *Finalise Release Builder* on Buildbot.

The *Finalise Release Builder* interface interrogates `cellml/libcellml <https://github.com/cellml/libcellml>`__ for release branches, and `end-to-end testing framework <https://github.com/libcellml/end-to-end-testing>`__, and `end-to-end testing database <https://github.com/libcellml/end-to-end-test-database>`__ for tags.
Choose the values for finalising the release in the finalise release interface, :numref:`libcellml_release_process_finalise_release_builder_interface`.
The branch input in the interface should be set to the *release_staging_<version number>* branch (again, there should be only one), :numref:`libcellml_release_process_release_branch_chooser_example`.
The end-to-end testing tag is the tag that specifies the version of the testing framework to use for running the tests, :numref:`libcellml_release_process_end_to_end_framework_tag_chooser_example`.
The end-to-end testing database is the tag that specifies the version of the database that describes the tests to run, :numref:`libcellml_release_process_end_to_end_database_tag_chooser_example`.

.. figure:: ./images/release_process/finalise_release_builder_interface.png
   :align: center
   :alt: Buildbot finalise release interface.
   :name: libcellml_release_process_finalise_release_builder_interface

   *Finalise Release Builder* interface.

.. figure:: ./images/release_process/release_branch_chooser_example.png
   :align: center
   :width: 50%
   :alt: Buildbot finalise release interface showing example of choosing an available branch.
   :name: libcellml_release_process_release_branch_chooser_example

   Example of choosing a release branch.

.. figure:: ./images/release_process/end_to_end_framework_tag_chooser_example.png
   :align: center
   :width: 50%
   :alt: Buildbot finalise release interface showing example of choosing an end-to-end testing tag.
   :name: libcellml_release_process_end_to_end_framework_tag_chooser_example

   Example of choosing a tag for the end-to-end testing framework.

.. figure:: ./images/release_process/end_to_end_database_tag_chooser_example.png
   :align: center
   :width: 50%
   :alt: Buildbot finalise release interface showing example of choosing an end-to-end database tag.
   :name: libcellml_release_process_end_to_end_database_tag_chooser_example

   Example of choosing a tag for the end-to-end testing database.

The *Finalise Release Builder* will update the libCellML staging website with the API documentation and the developer documentation.
The user documentation will only be updated for the release, if the end-to-end testing passes.
To this end, it is important to choose the appropriate end-to-end testing tag and end-to-end testing database tag.
If the end-to-end testing passes, the specifics of the versions that the release was tested with will be saved and surfaced on the website.

The last thing that the *Finalise Release Builder* does is the merging of the *release_staging_<version number>* into the *main* branch and the deletion of the *release_staging_<version number>* branch.
