#
# Tests the Issue class bindings
#
import unittest


class IssueTestCase(unittest.TestCase):

    def test_item_type_enum(self):
        from libcellml import CellmlElementType

        self.assertIsInstance(CellmlElementType.COMPONENT, int)
        self.assertIsInstance(CellmlElementType.COMPONENT_REF, int)
        self.assertIsInstance(CellmlElementType.CONNECTION, int)
        self.assertIsInstance(CellmlElementType.ENCAPSULATION, int)
        self.assertIsInstance(CellmlElementType.IMPORT, int)
        self.assertIsInstance(CellmlElementType.MAP_VARIABLES, int)
        self.assertIsInstance(CellmlElementType.MATH, int)
        self.assertIsInstance(CellmlElementType.MODEL, int)
        self.assertIsInstance(CellmlElementType.UNDEFINED, int)
        self.assertIsInstance(CellmlElementType.UNITS, int)
        self.assertIsInstance(CellmlElementType.UNIT, int)
        self.assertIsInstance(CellmlElementType.VARIABLE, int)

    def test_reference_rule_enum(self):
        from libcellml import Issue

        self.assertIsInstance(Issue.ReferenceRule.UNDEFINED, int)
        self.assertIsInstance(Issue.ReferenceRule.XML, int)
        self.assertIsInstance(Issue.ReferenceRule.DATA_REPR_IDENTIFIER_UNICODE, int)
        self.assertIsInstance(Issue.ReferenceRule.DATA_REPR_IDENTIFIER_LATIN_ALPHANUM, int)
        self.assertIsInstance(Issue.ReferenceRule.DATA_REPR_IDENTIFIER_AT_LEAST_ONE_ALPHANUM, int)
        self.assertIsInstance(Issue.ReferenceRule.DATA_REPR_IDENTIFIER_BEGIN_EURO_NUM, int)
        self.assertIsInstance(Issue.ReferenceRule.DATA_REPR_IDENTIFIER_IDENTICAL, int)
        self.assertIsInstance(Issue.ReferenceRule.DATA_REPR_INT_BASE10, int)
        self.assertIsInstance(Issue.ReferenceRule.DATA_REPR_INT_SIGN, int)
        self.assertIsInstance(Issue.ReferenceRule.DATA_REPR_INT_DIGIT, int)
        self.assertIsInstance(Issue.ReferenceRule.DATA_REPR_BASIC_REAL_BASE10, int)
        self.assertIsInstance(Issue.ReferenceRule.DATA_REPR_BASIC_REAL_SIGN, int)
        self.assertIsInstance(Issue.ReferenceRule.DATA_REPR_BASIC_REAL_DECIMAL, int)
        self.assertIsInstance(Issue.ReferenceRule.DATA_REPR_BASIC_REAL_DIGIT, int)
        self.assertIsInstance(Issue.ReferenceRule.DATA_REPR_REAL_BASE10, int)
        self.assertIsInstance(Issue.ReferenceRule.DATA_REPR_REAL_SIGNIFICAND, int)
        self.assertIsInstance(Issue.ReferenceRule.DATA_REPR_REAL_EXPONENT, int)
        self.assertIsInstance(Issue.ReferenceRule.MODEL_ELEMENT, int)
        self.assertIsInstance(Issue.ReferenceRule.MODEL_NAME, int)
        self.assertIsInstance(Issue.ReferenceRule.MODEL_CHILD, int)
        self.assertIsInstance(Issue.ReferenceRule.MODEL_MORE_THAN_ONE_ENCAPSULATION, int)
        self.assertIsInstance(Issue.ReferenceRule.IMPORT_ATTRIBUTE, int)
        self.assertIsInstance(Issue.ReferenceRule.IMPORT_HREF, int)
        self.assertIsInstance(Issue.ReferenceRule.IMPORT_CHILD, int)
        self.assertIsInstance(Issue.ReferenceRule.IMPORT_EQUIVALENT, int)
        self.assertIsInstance(Issue.ReferenceRule.IMPORT_UNITS_NAME, int)
        self.assertIsInstance(Issue.ReferenceRule.IMPORT_UNITS_NAME_UNIQUE, int)
        self.assertIsInstance(Issue.ReferenceRule.IMPORT_UNITS_REF, int)
        self.assertIsInstance(Issue.ReferenceRule.IMPORT_COMPONENT_NAME, int)
        self.assertIsInstance(Issue.ReferenceRule.IMPORT_COMPONENT_NAME_UNIQUE, int)
        self.assertIsInstance(Issue.ReferenceRule.IMPORT_COMPONENT_COMPONENT_REF, int)
        self.assertIsInstance(Issue.ReferenceRule.UNITS_ATTRIBUTE, int)
        self.assertIsInstance(Issue.ReferenceRule.UNITS_NAME, int)
        self.assertIsInstance(Issue.ReferenceRule.UNITS_NAME_UNIQUE, int)
        self.assertIsInstance(Issue.ReferenceRule.UNITS_STANDARD, int)
        self.assertIsInstance(Issue.ReferenceRule.UNITS_CHILD, int)
        self.assertIsInstance(Issue.ReferenceRule.UNIT_ATTRIBUTE, int)
        self.assertIsInstance(Issue.ReferenceRule.UNIT_UNITS_REF, int)
        self.assertIsInstance(Issue.ReferenceRule.UNIT_CIRCULAR_REF, int)
        self.assertIsInstance(Issue.ReferenceRule.UNIT_OPTIONAL_ATTRIBUTE, int)
        self.assertIsInstance(Issue.ReferenceRule.UNIT_PREFIX, int)
        self.assertIsInstance(Issue.ReferenceRule.UNIT_MULTIPLIER, int)
        self.assertIsInstance(Issue.ReferenceRule.UNIT_EXPONENT, int)
        self.assertIsInstance(Issue.ReferenceRule.COMPONENT_ATTRIBUTE, int)
        self.assertIsInstance(Issue.ReferenceRule.COMPONENT_NAME, int)
        self.assertIsInstance(Issue.ReferenceRule.COMPONENT_NAME_UNIQUE, int)
        self.assertIsInstance(Issue.ReferenceRule.COMPONENT_CHILD, int)
        self.assertIsInstance(Issue.ReferenceRule.VARIABLE_ATTRIBUTE, int)
        self.assertIsInstance(Issue.ReferenceRule.VARIABLE_CHILD, int)
        self.assertIsInstance(Issue.ReferenceRule.VARIABLE_NAME, int)
        self.assertIsInstance(Issue.ReferenceRule.VARIABLE_NAME_UNIQUE, int)
        self.assertIsInstance(Issue.ReferenceRule.VARIABLE_UNITS, int)
        self.assertIsInstance(Issue.ReferenceRule.VARIABLE_INTERFACE, int)
        self.assertIsInstance(Issue.ReferenceRule.VARIABLE_INITIAL_VALUE, int)
        self.assertIsInstance(Issue.ReferenceRule.RESET_ATTRIBUTE, int)
        self.assertIsInstance(Issue.ReferenceRule.RESET_VARIABLE_REF, int)
        self.assertIsInstance(Issue.ReferenceRule.RESET_TEST_VARIABLE_REF, int)
        self.assertIsInstance(Issue.ReferenceRule.RESET_ORDER, int)
        self.assertIsInstance(Issue.ReferenceRule.RESET_CHILD, int)
        self.assertIsInstance(Issue.ReferenceRule.RESET_TEST_VALUE, int)
        self.assertIsInstance(Issue.ReferenceRule.RESET_RESET_VALUE, int)
        self.assertIsInstance(Issue.ReferenceRule.MATH_MATHML, int)
        self.assertIsInstance(Issue.ReferenceRule.MATH_CHILD, int)
        self.assertIsInstance(Issue.ReferenceRule.MATH_CI_VARIABLE_REF, int)
        self.assertIsInstance(Issue.ReferenceRule.MATH_CN_UNITS, int)
        self.assertIsInstance(Issue.ReferenceRule.MATH_CN_BASE10, int)
        self.assertIsInstance(Issue.ReferenceRule.MATH_CN_FORMAT, int)
        self.assertIsInstance(Issue.ReferenceRule.ENCAPSULATION_ATTRIBUTE, int)
        self.assertIsInstance(Issue.ReferenceRule.ENCAPSULATION_CHILD, int)
        self.assertIsInstance(Issue.ReferenceRule.COMPONENT_REF_COMPONENT, int)
        self.assertIsInstance(Issue.ReferenceRule.COMPONENT_REF_CHILD, int)
        self.assertIsInstance(Issue.ReferenceRule.CONNECTION_ATTRIBUTE, int)
        self.assertIsInstance(Issue.ReferenceRule.CONNECTION_COMPONENT1, int)
        self.assertIsInstance(Issue.ReferenceRule.CONNECTION_COMPONENT2, int)
        self.assertIsInstance(Issue.ReferenceRule.CONNECTION_EXCLUDE_SELF, int)
        self.assertIsInstance(Issue.ReferenceRule.CONNECTION_UNIQUE, int)
        self.assertIsInstance(Issue.ReferenceRule.CONNECTION_CHILD, int)
        self.assertIsInstance(Issue.ReferenceRule.MAP_VARIABLES_ATTRIBUTE, int)
        self.assertIsInstance(Issue.ReferenceRule.MAP_VARIABLES_VARIABLE1, int)
        self.assertIsInstance(Issue.ReferenceRule.MAP_VARIABLES_VARIABLE2, int)
        self.assertIsInstance(Issue.ReferenceRule.MAP_VARIABLES_UNIQUE, int)
        self.assertIsInstance(Issue.ReferenceRule.MAP_VARIABLES_IDENTICAL_UNIT_REDUCTION, int)
        self.assertIsInstance(Issue.ReferenceRule.UNSPECIFIED, int)

    def test_coverage(self):
        from libcellml import Issue
        from libcellml import Parser
        from test_resources import file_contents

        self.assertRaises(AttributeError, Issue)

        p = Parser()
        p.parseModel(file_contents('invalid_cellml_2.0.xml'))

        self.assertEqual(2, p.issueCount())

        i = p.issue(0)

        self.assertEqual(Issue.Level.ERROR, i.level())
        self.assertNotEqual(None, i.item())
        self.assertEqual("1.2.1", i.referenceHeading())
        self.assertEqual(1, i.referenceRule())
        self.assertEqual(
            "https://cellml-specification.readthedocs.io/en/latest/reference/formal_and_informative/specA02.html?issue=XML",
            i.url())

        p.removeAllIssues()

        self.assertEqual(0, p.issueCount())
        self.assertEqual(0, p.errorCount())
        self.assertEqual(None, p.error(0))
        self.assertEqual(0, p.warningCount())
        self.assertEqual(None, p.warning(0))
        self.assertEqual(0, p.messageCount())
        self.assertEqual(None, p.message(0))
        self.assertFalse(p.removeError(3))
        self.assertFalse(p.removeIssue(0))
        self.assertFalse(p.removeWarning(2))
        self.assertFalse(p.removeMessage(0))


if __name__ == '__main__':
    unittest.main()
