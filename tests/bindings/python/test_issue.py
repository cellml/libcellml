#
# Tests the Issue class bindings
#
import unittest


class IssueTestCase(unittest.TestCase):

    def test_create_destroy(self):
        from libcellml import Component
        from libcellml import Issue
        from libcellml import ImportSource
        from libcellml import Model
        from libcellml import Reset
        from libcellml import Units
        from libcellml import Variable

        e1 = Issue()
        del(e1)

        c = Component()
        e2 = Issue(c)
        del(e2)

        i = ImportSource()
        e3 = Issue(i)
        del(e3)

        m = Model()
        e4 = Issue(m)
        del(e4)

        r = Reset()
        e5 = Issue(r)
        del(e5)

        u = Units()
        e6 = Issue(u)
        del(e6)

        v = Variable()
        e7 = Issue(v)
        del(e7)

    def test_cause_enum(self):
        import libcellml
        from libcellml import Issue
        from libcellml import ItemType

        self.assertIsInstance(ItemType.COMPONENT, int)
        self.assertIsInstance(ItemType.COMPONENT_REF, int)
        self.assertIsInstance(ItemType.CONNECTION, int)
        self.assertIsInstance(ItemType.ENCAPSULATION, int)
        self.assertIsInstance(ItemType.IMPORT, int)
        self.assertIsInstance(ItemType.MAP_VARIABLES, int)
        self.assertIsInstance(ItemType.MATHML, int)
        self.assertIsInstance(ItemType.MODEL, int)
        self.assertIsInstance(ItemType.UNDEFINED, int)
        self.assertIsInstance(ItemType.UNITS, int)
        self.assertIsInstance(ItemType.UNIT, int)
        self.assertIsInstance(ItemType.VARIABLE, int)
        self.assertIsInstance(ItemType.XML, int)

        # Test conversion to enum
        e = Issue()
        e.setCause(ItemType.COMPONENT)
        self.assertRaises(RuntimeError, e.setCause, ItemType.COMPONENT - 1)
        self.assertRaises(RuntimeError, e.setCause, ItemType.XML + 1)

    def test_reference_rule_enum(self):
        from libcellml import Issue

        self.assertIsInstance(Issue.ReferenceRule.UNDEFINED, int)
        self.assertIsInstance(
            Issue.ReferenceRule.DATA_REPR_IDENTIFIER_UNICODE, int)
        self.assertIsInstance(
            Issue.ReferenceRule.DATA_REPR_IDENTIFIER_LATIN_ALPHANUM, int)
        self.assertIsInstance(
            Issue.ReferenceRule.DATA_REPR_IDENTIFIER_AT_LEAST_ONE_ALPHANUM, int)
        self.assertIsInstance(
            Issue.ReferenceRule.DATA_REPR_IDENTIFIER_BEGIN_EURO_NUM, int)
        self.assertIsInstance(
            Issue.ReferenceRule.DATA_REPR_IDENTIFIER_IDENTICAL, int)
        self.assertIsInstance(Issue.ReferenceRule.DATA_REPR_INT_BASE10, int)
        self.assertIsInstance(Issue.ReferenceRule.DATA_REPR_INT_SIGN, int)
        self.assertIsInstance(Issue.ReferenceRule.DATA_REPR_INT_DIGIT, int)
        self.assertIsInstance(
            Issue.ReferenceRule.DATA_REPR_BASIC_REAL_BASE10, int)
        self.assertIsInstance(
            Issue.ReferenceRule.DATA_REPR_BASIC_REAL_SIGN, int)
        self.assertIsInstance(
            Issue.ReferenceRule.DATA_REPR_BASIC_REAL_DECIMAL, int)
        self.assertIsInstance(
            Issue.ReferenceRule.DATA_REPR_BASIC_REAL_DIGIT, int)
        self.assertIsInstance(Issue.ReferenceRule.DATA_REPR_REAL_BASE10, int)
        self.assertIsInstance(
            Issue.ReferenceRule.DATA_REPR_REAL_SIGNIFICAND, int)
        self.assertIsInstance(Issue.ReferenceRule.DATA_REPR_REAL_EXPONENT, int)
        self.assertIsInstance(Issue.ReferenceRule.MODEL_ELEMENT, int)
        self.assertIsInstance(Issue.ReferenceRule.MODEL_NAME, int)
        self.assertIsInstance(Issue.ReferenceRule.MODEL_CHILD, int)
        self.assertIsInstance(
            Issue.ReferenceRule.MODEL_MORE_THAN_ONE_ENCAPSULATION, int)
        self.assertIsInstance(Issue.ReferenceRule.IMPORT_HREF, int)
        self.assertIsInstance(Issue.ReferenceRule.IMPORT_CHILD, int)
        self.assertIsInstance(Issue.ReferenceRule.IMPORT_EQUIVALENT, int)
        self.assertIsInstance(Issue.ReferenceRule.IMPORT_UNITS_NAME, int)
        self.assertIsInstance(
            Issue.ReferenceRule.IMPORT_UNITS_NAME_UNIQUE, int)
        self.assertIsInstance(Issue.ReferenceRule.IMPORT_UNITS_REF, int)
        self.assertIsInstance(Issue.ReferenceRule.IMPORT_COMPONENT_NAME, int)
        self.assertIsInstance(
            Issue.ReferenceRule.IMPORT_COMPONENT_NAME_UNIQUE, int)
        self.assertIsInstance(
            Issue.ReferenceRule.IMPORT_COMPONENT_COMPONENT_REF, int)
        self.assertIsInstance(Issue.ReferenceRule.UNITS_NAME, int)
        self.assertIsInstance(Issue.ReferenceRule.UNITS_NAME_UNIQUE, int)
        self.assertIsInstance(Issue.ReferenceRule.UNITS_STANDARD, int)
        self.assertIsInstance(Issue.ReferenceRule.UNITS_CHILD, int)
        self.assertIsInstance(Issue.ReferenceRule.UNIT_UNITS_REF, int)
        self.assertIsInstance(Issue.ReferenceRule.UNIT_CIRCULAR_REF, int)
        self.assertIsInstance(Issue.ReferenceRule.UNIT_OPTIONAL_ATTRIBUTE, int)
        self.assertIsInstance(Issue.ReferenceRule.UNIT_PREFIX, int)
        self.assertIsInstance(Issue.ReferenceRule.UNIT_MULTIPLIER, int)
        self.assertIsInstance(Issue.ReferenceRule.UNIT_EXPONENT, int)
        self.assertIsInstance(Issue.ReferenceRule.COMPONENT_NAME, int)
        self.assertIsInstance(Issue.ReferenceRule.COMPONENT_NAME_UNIQUE, int)
        self.assertIsInstance(Issue.ReferenceRule.COMPONENT_CHILD, int)
        self.assertIsInstance(Issue.ReferenceRule.VARIABLE_NAME, int)
        self.assertIsInstance(Issue.ReferenceRule.VARIABLE_NAME_UNIQUE, int)
        self.assertIsInstance(Issue.ReferenceRule.VARIABLE_UNITS, int)
        self.assertIsInstance(Issue.ReferenceRule.VARIABLE_INTERFACE, int)
        self.assertIsInstance(Issue.ReferenceRule.VARIABLE_INITIAL_VALUE, int)
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
        self.assertIsInstance(Issue.ReferenceRule.ENCAPSULATION_CHILD, int)
        self.assertIsInstance(Issue.ReferenceRule.COMPONENT_REF_COMPONENT, int)
        self.assertIsInstance(Issue.ReferenceRule.COMPONENT_REF_CHILD, int)
        self.assertIsInstance(Issue.ReferenceRule.CONNECTION_COMPONENT1, int)
        self.assertIsInstance(Issue.ReferenceRule.CONNECTION_COMPONENT2, int)
        self.assertIsInstance(Issue.ReferenceRule.CONNECTION_EXCLUDE_SELF, int)
        self.assertIsInstance(Issue.ReferenceRule.CONNECTION_UNIQUE, int)
        self.assertIsInstance(Issue.ReferenceRule.CONNECTION_CHILD, int)
        self.assertIsInstance(Issue.ReferenceRule.MAP_VARIABLES_VARIABLE1, int)
        self.assertIsInstance(Issue.ReferenceRule.MAP_VARIABLES_VARIABLE2, int)
        self.assertIsInstance(Issue.ReferenceRule.MAP_VARIABLES_UNIQUE, int)
        self.assertIsInstance(
            Issue.ReferenceRule.MAP_VARIABLES_IDENTICAL_UNIT_REDUCTION, int)

        # Test conversion to enum
        e = Issue()
        e.setReferenceRule(Issue.ReferenceRule.UNDEFINED)
        self.assertRaises(RuntimeError, e.setReferenceRule,
                          Issue.ReferenceRule.UNDEFINED - 1)
        self.assertRaises(RuntimeError, e.setReferenceRule,
                          Issue.ReferenceRule.MAP_VARIABLES_IDENTICAL_UNIT_REDUCTION + 1)
        del(e)

    def test_set_description(self):
        from libcellml import Issue

        # void setDescription(const std::string &description)
        e = Issue()
        e.setDescription('hello')
        e.setDescription('')

    def test_description(self):
        from libcellml import Issue

        # std::string description()
        d = 'hi'
        e = Issue()
        self.assertEqual(e.description(), '')
        e.setDescription(d)
        self.assertEqual(e.description(), d)
        del(d, e)

    def test_set_cause(self):
        from libcellml import Issue
        from libcellml import ItemType

        # void setCause(Cause cause)
        e = Issue()
        e.setCause(ItemType.CONNECTION)

    def test_cause(self):
        from libcellml import Issue
        from libcellml import ItemType
        # Cause cause()
        e = Issue()
        self.assertEqual(e.cause(), ItemType.UNDEFINED)
        e.setCause(ItemType.MATHML)
        self.assertEqual(e.cause(), ItemType.MATHML)

    def test_set_rule(self):
        from libcellml import Issue

        # void setReferenceRule(ReferenceRule rule)
        e = Issue()
        e.setReferenceRule(Issue.ReferenceRule.MAP_VARIABLES_VARIABLE2)

    def test_rule(self):
        from libcellml import Issue

        # ReferenceRule referenceRule()
        e = Issue()
        self.assertEqual(e.referenceRule(), Issue.ReferenceRule.UNDEFINED)

    def test_reference_heading(self):
        from libcellml import Issue

        # std::string referenceHeading()
        e = Issue()
        self.assertEqual('', e.referenceHeading())

    def test_set_component(self):
        from libcellml import Issue, Component

        # void setComponent(const ComponentPtr &component)
        e = Issue()
        e.setComponent(Component())

    def test_component(self):
        from libcellml import Issue, Component

        # ComponentPtr component()
        e = Issue()
        self.assertIsNone(e.component())
        name = 'cellml'
        c = Component()
        c.setName(name)
        e.setComponent(c)
        self.assertIsInstance(e.component(), Component)
        self.assertEqual(e.component().name(), name)

    def test_set_import_source(self):
        from libcellml import Issue, ImportSource

        # void setImportSource(const ImportSourcePtr &import)
        e = Issue()
        e.setImportSource(ImportSource())

    def test_import_source(self):
        from libcellml import Issue, ImportSource

        # ImportSourcePtr importSource()
        e = Issue()
        self.assertIsNone(e.component())
        name = 'uri'
        i = ImportSource()
        i.setId(name)
        e.setImportSource(i)
        self.assertIsInstance(e.importSource(), ImportSource)
        self.assertEqual(e.importSource().id(), name)

    def test_set_model(self):
        from libcellml import Issue, Model

        # void setModel(const ModelPtr &model)
        e = Issue()
        e.setModel(Model())

    def test_model(self):
        from libcellml import Issue, Model

        # ModelPtr model()
        e = Issue()
        self.assertIsNone(e.model())
        name = 'moodle'
        m = Model()
        m.setName(name)
        e.setModel(m)
        self.assertIsInstance(e.model(), Model)
        self.assertEqual(e.model().name(), name)

    def test_set_units(self):
        from libcellml import Issue, Units

        # void setUnits(const UnitsPtr &units)
        e = Issue()
        e.setUnits(Units())

    def test_units(self):
        from libcellml import Issue, Units

        # UnitsPtr units()
        e = Issue()
        self.assertIsNone(e.units())
        name = 'furlong'
        u = Units()
        u.setName(name)
        e.setUnits(u)
        self.assertIsInstance(e.units(), Units)
        self.assertEqual(e.units().name(), name)

    def test_set_variable(self):
        from libcellml import Issue, Variable

        # void setVariable(const VariablePtr &variable)
        e = Issue()
        e.setVariable(Variable())

    def test_variable(self):
        from libcellml import Issue, Variable

        # VariablePtr variable()
        e = Issue()
        self.assertIsNone(e.variable())
        name = 'var'
        v = Variable()
        v.setName(name)
        e.setVariable(v)
        self.assertIsInstance(e.variable(), Variable)
        self.assertEqual(e.variable().name(), name)

    def test_set_reset(self):
        from libcellml import Issue, Reset

        # void setReset(const ResetPtr &reset);
        e = Issue()
        e.setReset(Reset())

    def test_reset(self):
        from libcellml import Issue, Reset

        # ResetPtr reset() const;
        e = Issue()
        self.assertIsNone(e.reset())
        name = 'res'
        r = Reset()
        r.setId(name)
        e.setReset(r)
        self.assertIsInstance(e.reset(), Reset)
        self.assertEqual(e.reset().id(), name)

    def test_url(self):
        from libcellml import Issue

        i = Issue()
        self.assertEqual('', i.url())

    def test_level(self):
        from libcellml import Issue, Reset

        # ResetPtr reset() const;
        e = Issue()
        self.assertEqual(Issue.Level.ERROR, e.level())

        e.setLevel(Issue.Level.HINT)
        self.assertEqual(Issue.Level.HINT, e.level())


if __name__ == '__main__':
    unittest.main()
