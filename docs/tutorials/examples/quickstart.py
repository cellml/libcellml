"""
 *  QUICKSTART: Summary of commonly used functionality
 *
 *
"""

from libcellml import Generator, GeneratorProfile, Parser, Printer, Validator

from tutorial_utilities import print_errors_to_terminal, print_model_to_terminal, get_issue_level_from_enum, \
    get_issue_cause_from_enum

if __name__ == "__main__":

    # ----------------------------------------------------------------------------
    #  STEP 1:   Deserialise a CellML Model from the contents of a CellML file

    #  1.a   Open the file and read its contents into a buffer stream
    read_file1 = open("../resources/tutorial2.cellml", "r")

    #  1.b   Create a libCellML Parser, and use it to parse the inFileContents
    #        stream and return it as a ModelPtr instance
    parser = Parser()
    model = parser.parseModel(read_file1.read())

    #  1.c   Print to the terminal to see the model contents
    print_model_to_terminal(model)

    # ----------------------------------------------------------------------------
    #  STEP 2:   Validate the contents of a model

    #  2.a   Create a Validator instance and pass it the model pointer for
    #        checking
    validator = Validator()
    validator.validateModel(model)

    #  2.b   Retrieve the errors from the validator and access their
    #        specificiation reference and description
    print_errors_to_terminal(validator)

    for e in range(0, validator.issueCount()):
        issue = validator.issue(e)

        # Retrieve and print the description of the issue.
        print(issue.description())

        # Retrieve and print the reference heading number, if related to CellML2.0 specification and format.
        print(issue.referenceHeading())

        # Retrieve and print the URL for more help and information about the issue. **TODO** after #604
        print(issue.url())

        # Retrieve and print the cause - a libcellml::Issue::CAUSE enum - for the issue.
        print(get_issue_cause_from_enum(issue.cause()))

        # Retrieve and print the level - a libcellml::Issue::LEVEL enum - for the issue.
        print(get_issue_level_from_enum(issue.level()))
