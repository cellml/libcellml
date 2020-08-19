.. _examples_get_issues:

Retrieve ``Issue`` items
========================
Selected libCellML classes contain a :code:`Logger` whose job it is to curate any issues encountered within the class, and return them to the user when asked.
The classes are:

- the :code:`Parser` class;
- the :code:`Validator` class;
- the :code:`Printer` class;
- the :code:`Importer` class; and
- the :code:`Generator` class.

**TODO** also the :code:`Analyser` class when available.

Individual issues can be retrieved from the parent class by their index, an integer between 0 and :code:`issueCount()-1`.
Each issue contains a severity level indicator, one of three levels (:code:`ERROR`, :code:`WARNING`, or :code:`HINT`):

  - :code:`ERROR` level indicates issues that must be resolved before the model is valid and runnable;
  - :code:`WARNING` level indicates a non-fatal issue, but one that may cause hidden or unintended consequences; and
  - :code:`HINT` level indicates a commonly encountered valid-but-nonsense situation.

Issues can also be retrieved from subgroups based on their severity, as shown in the examples below.

.. container:: toggle

  .. container:: header

    See C++ example

  .. code-block:: cpp

      // Iterate through all the issues in a Validator, regardless of level, and print to the terminal.
      for (size_t i = 0; i < validator->issueCount(); ++i) {
        // Retrieve the i-th issue and store it in the variable "myIssue".
        libcellml::IssuePtr myIssue = validator->issue(i);

        // Print the issue's description:
        std::cout << myIssue->description() << std::endl;

        // Print the issue's URL.  This is a URL at which more 
        // information could be found about the cause and corrections
        // are needed to avoid it.
        std::cout << myIssue->url() << std::endl;

        // Validator only: Print the issue's reference. This is 
        // the heading reference in the normative specification which 
        // relates to this issue.
        std::cout << myIssue->referenceHeading() << std::endl;
      }

      // Retrieve the second ERROR level issue from a Printer. Note indexing from 0.
      auto secondError = printer->error(1);

      // Retrieve the last WARNING level issue from a Parser.
      auto lastWarning = parser->warning(parser->warningCount()-1);

      // Iterate through all HINT level issues in a Generator.
      for (size_t h = 0; h < generator->hintCount(); ++i) {
        // Retrieve the h-th hint and store it in the variable "myHint".
        auto myHint = generator->hint(h);
      }

.. container:: toggle

  .. container:: header

    See Python example

  .. code-block:: python

      # Iterate through all the issues in a Validator, regardless of level, and print to the terminal.
      for i in range(0, validator.issueCount()):
        # Retrieve the i-th issue and store it in the variable "my_issue".
        my_issue = validator.issue(i)

        # Print the issue's description:
        print(my_issue.description())

        # Print the issue's URL.  This is a URL at which more 
        # information could be found about the cause and corrections
        # are needed to avoid it.
        print(my_issue.url())

        # Validator only: Print the issue's reference. This is 
        # the heading reference in the normative specification which 
        # relates to this issue.
        print(my_issue.referenceHeading())

      # Retrieve the second ERROR level issue from a Printer. Note indexing from 0.
      second_error = printer.error(1)

      # Retrieve the last WARNING level issue from a Parser.
      last_warning = parser.warning(parser.warningCount() - 1)

      # Iterate through all HINT level issues in a Generator.
      for h in range(0, generator.hintCount()):
        # Retrieve the h-th hint and store it in the variable "my_hint".
        my_hint = generator.hint(h)

Each :code:`Issue` also contains the following attributes:

- A description: a brief statement about the problem and how it might be fixed;
- A reference heading: a chapter number pertaining to the formal :cellml2:`CellML 2.0 Specification` document, for issues related to formatting and specification;
- A URL: a web address at which more detailed information and examples pertaining to the issue are available;
- A cause: an :code:`enum` which reports the type of item responsible for the issue.
  This is one of the enums:

  - :code:`COMPONENT`,
  - :code:`CONNECTION`,
  - :code:`ENCAPSULATION`,
  - :code:`IMPORT`,
  - :code:`MATHML`,
  - :code:`MODEL`,
  - :code:`RESET`,
  - :code:`UNDEFINED`,
  - :code:`UNITS`,
  - :code:`VARIABLE`,
  - :code:`XML`, and
  - :code:`GENERATOR`.

.. container:: toggle

  .. container:: header

    See C++ examples

      .. code-block:: cpp

        // Retrieve and print the description of the issue.
        std::cout << issue->description() << std::endl;

        // Retrieve and print the reference heading number, if related to CellML2.0 specification and format.
        std::cout << issue->referenceHeading() << std::endl;

        // Retrieve and print the URL for more help and information about the issue. **TODO** Available in #604.
        std::cout << issue->url() << std::endl;

        // Retrieve and print the cause - a libcellml::Issue::CAUSE enum - for the issue.
        std::cout << getCauseFromEnum(issue->cause()) << std::endl;

        // Retrieve and print the level - a libcellml::Issue::LEVEL enum - for the issue.
        std::cout << getIssueLevelFromEnum(issue->level()) << std::endl;

        // Retrieve the item associated with the issue **TODO**


.. container:: toggle

  .. container:: header

    See Python examples

  .. code-block:: python

    # Retrieve and print the description of the issue.
    print(issue.description())

    # Retrieve and print the reference heading number, if related to CellML2.0 specification and format.
    print(issue.referenceHeading())

    # Retrieve and print the URL for more help and information about the issue. 
    print(issue.url())

    # Retrieve and print the cause - a libcellml.Issue.CAUSE enum - for the issue.
    print(get_issue_cause_from_enum(issue.cause()))

    # Retrieve and print the level - a libcellml.Issue.LEVEL enum - for the issue.
    print(get_issue_level_from_enum(issue.level()))
