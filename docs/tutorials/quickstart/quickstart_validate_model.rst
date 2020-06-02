.. _quickstart_validate_model:

Validate a ``Model``
++++++++++++++++++++
The :code:`Validator` class is used to check your final model for issues before export or code generation.
The issue descriptions should give enough information to allow you to find and fix any problems related to the CellML specification and its requirements from your model, as well as supplying a URL and heading number referring to the section in :ref:`formal CellML2.0 description<formal_specification>` related to the issue.

In C++:

.. code-block:: cpp

    // Create a Validator instance and pass it the model for checking.
    libcellml::ValidatorPtr validator = libcellml::Validator::create();
    validator->validateModel(model);

    for (size_t e = 0; e < validator->issueCount(); ++e) {
      libcellml::IssuePtr issue = validator->issue(e);

      // Retrieve and print the description of the issue.
      std::cout << issue->description() << std::endl;

      // Retrieve and print the reference heading number, if related to CellML2.0 specification and format.
      std::cout << issue->referenceHeading() << std::endl;

      // Retrieve and print the URL for more help and information about the issue.
      std::cout << issue->url() << std::endl;

      // Retrieve and print the cause - a libcellml::Issue::CAUSE enum - for the issue.
      std::cout << getCauseFromEnum(issue->cause()) << std::endl;

      // Retrieve and print the level - a libcellml::Issue::LEVEL enum - for the issue.
      std::cout << getIssueLevelFromEnum(issue->level()) << std::endl;

      // Retrieve the item associated with the issue **TODO**
    }

In Python:

.. code-block:: python

    from libcellml import Validator

    # Create a Validator instance and pass it the model for checking
    validator = Validator()
    validator.validateModel(model)

    # Check the validator for issues
    for e in range(0, validator.issueCount()):
        print(validator.issue(e).description())
        print(validator.issue(e).referenceHeading())
