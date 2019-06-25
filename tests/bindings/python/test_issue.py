#
# Tests the Issue class bindings
#
import unittest


class IssueTestCase(unittest.TestCase):

    def test_create_destroy(self):
        from libcellml import Issue

        x = Issue()
        del(x)
        y = Issue()
        z = Issue(y)
        del(y, z)

    def test_kind_enum(self):
        from libcellml import Issue

        self.assertIsInstance(Issue.Kind.COMPONENT, int)
        self.assertIsInstance(Issue.Kind.CONNECTION, int)
        self.assertIsInstance(Issue.Kind.ENCAPSULATION, int)
        self.assertIsInstance(Issue.Kind.IMPORT, int)
        self.assertIsInstance(Issue.Kind.MATHML, int)
        self.assertIsInstance(Issue.Kind.MODEL, int)
        self.assertIsInstance(Issue.Kind.UNDEFINED, int)
        self.assertIsInstance(Issue.Kind.UNITS, int)
        self.assertIsInstance(Issue.Kind.VARIABLE, int)
        self.assertIsInstance(Issue.Kind.XML, int)

        # Test conversion to enum
        e = Issue()
        e.setKind(Issue.Kind.COMPONENT)
        self.assertRaises(RuntimeError, e.setKind, Issue.Kind.COMPONENT - 1)
        self.assertRaises(RuntimeError, e.setKind, Issue.Kind.XML + 1)

    def test_specification_rule_enum(self):
        from libcellml import Issue, SpecificationRule

        self.assertIsInstance(SpecificationRule.UNDEFINED, int)
        self.assertIsInstance(SpecificationRule.DATA_REPR_IDENTIFIER_UNICODE, int)
        self.assertIsInstance(SpecificationRule.DATA_REPR_IDENTIFIER_LATIN_ALPHANUM, int)
        self.assertIsInstance(SpecificationRule.DATA_REPR_IDENTIFIER_AT_LEAST_ONE_ALPHANUM, int)
        self.assertIsInstance(SpecificationRule.DATA_REPR_IDENTIFIER_BEGIN_EURO_NUM, int)
        self.assertIsInstance(SpecificationRule.DATA_REPR_IDENTIFIER_IDENTICAL, int)
        self.assertIsInstance(SpecificationRule.DATA_REPR_NNEG_INT_BASE10, int)
        self.assertIsInstance(SpecificationRule.DATA_REPR_NNEG_INT_EURO_NUM, int)
        self.assertIsInstance(SpecificationRule.MODEL_ELEMENT, int)
        self.assertIsInstance(SpecificationRule.MODEL_NAME, int)
        self.assertIsInstance(SpecificationRule.MODEL_CHILD, int)
        self.assertIsInstance(SpecificationRule.MODEL_MORE_THAN_ONE_ENCAPSULATION, int)
        self.assertIsInstance(SpecificationRule.IMPORT_HREF, int)
        self.assertIsInstance(SpecificationRule.IMPORT_CHILD, int)
        self.assertIsInstance(SpecificationRule.IMPORT_CIRCULAR, int)
        self.assertIsInstance(SpecificationRule.IMPORT_UNITS_NAME, int)
        self.assertIsInstance(SpecificationRule.IMPORT_UNITS_REF, int)
        self.assertIsInstance(SpecificationRule.IMPORT_COMPONENT_NAME, int)
        self.assertIsInstance(SpecificationRule.IMPORT_COMPONENT_REF, int)
        self.assertIsInstance(SpecificationRule.UNITS_NAME, int)
        self.assertIsInstance(SpecificationRule.UNITS_NAME_UNIQUE, int)
        self.assertIsInstance(SpecificationRule.UNITS_STANDARD, int)
        self.assertIsInstance(SpecificationRule.UNITS_CHILD, int)
        self.assertIsInstance(SpecificationRule.UNIT_UNITS_REF, int)
        self.assertIsInstance(SpecificationRule.UNIT_DIGRAPH, int)
        self.assertIsInstance(SpecificationRule.UNIT_CIRCULAR_REF, int)
        self.assertIsInstance(SpecificationRule.UNIT_OPTIONAL_ATTRIBUTE, int)
        self.assertIsInstance(SpecificationRule.UNIT_PREFIX, int)
        self.assertIsInstance(SpecificationRule.UNIT_MULTIPLIER, int)
        self.assertIsInstance(SpecificationRule.UNIT_EXPONENT, int)
        self.assertIsInstance(SpecificationRule.COMPONENT_NAME, int)
        self.assertIsInstance(SpecificationRule.COMPONENT_CHILD, int)
        self.assertIsInstance(SpecificationRule.VARIABLE_NAME, int)
        self.assertIsInstance(SpecificationRule.VARIABLE_UNITS, int)
        self.assertIsInstance(SpecificationRule.VARIABLE_INTERFACE, int)
        self.assertIsInstance(SpecificationRule.VARIABLE_INITIAL_VALUE, int)
        self.assertIsInstance(SpecificationRule.RESET_VARIABLE_REFERENCE, int)
        self.assertIsInstance(SpecificationRule.RESET_ORDER, int)
        self.assertIsInstance(SpecificationRule.RESET_CHILD, int)
        self.assertIsInstance(SpecificationRule.WHEN_ORDER, int)
        self.assertIsInstance(SpecificationRule.WHEN_CHILD, int)
        self.assertIsInstance(SpecificationRule.MATH_MATHML, int)
        self.assertIsInstance(SpecificationRule.MATH_CHILD, int)
        self.assertIsInstance(SpecificationRule.MATH_CI_VARIABLE_REFERENCE, int)
        self.assertIsInstance(SpecificationRule.MATH_CN_UNITS_ATTRIBUTE, int)
        self.assertIsInstance(SpecificationRule.ENCAPSULATION_COMPONENT_REF, int)
        self.assertIsInstance(SpecificationRule.COMPONENT_REF_COMPONENT_ATTRIBUTE, int)
        self.assertIsInstance(SpecificationRule.COMPONENT_REF_CHILD, int)
        self.assertIsInstance(SpecificationRule.COMPONENT_REF_ENCAPSULATION, int)
        self.assertIsInstance(SpecificationRule.CONNECTION_COMPONENT1, int)
        self.assertIsInstance(SpecificationRule.CONNECTION_COMPONENT2, int)
        self.assertIsInstance(SpecificationRule.CONNECTION_UNIQUE_TRANSITIVE, int)
        self.assertIsInstance(SpecificationRule.CONNECTION_MAP_VARIABLES, int)
        self.assertIsInstance(SpecificationRule.MAP_VARIABLES_VARIABLE1, int)
        self.assertIsInstance(SpecificationRule.MAP_VARIABLES_VARIABLE2, int)
        self.assertIsInstance(SpecificationRule.MAP_VARIABLES_UNIQUE, int)

        # Test conversion to enum
        e = Issue()
        e.setRule(SpecificationRule.UNDEFINED)
        self.assertRaises(
            RuntimeError, e.setRule, SpecificationRule.UNDEFINED - 1)
        self.assertRaises(
            RuntimeError, e.setRule,
            SpecificationRule.MAP_VARIABLES_UNIQUE + 1)
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

    def test_set_kind(self):
        from libcellml import Issue

        # void setKind(Kind kind)
        e = Issue()
        e.setKind(Issue.Kind.CONNECTION)

    def test_kind(self):
        from libcellml import Issue

        # Kind kind()
        e = Issue()
        self.assertEqual(e.kind(), Issue.Kind.UNDEFINED)
        e.setKind(Issue.Kind.MATHML)
        self.assertEqual(e.kind(), Issue.Kind.MATHML)

    def test_is_kind(self):
        from libcellml import Issue

        # bool isKind(const Kind &kind)
        e = Issue()
        self.assertTrue(e.isKind(Issue.Kind.UNDEFINED))
        self.assertFalse(e.isKind(Issue.Kind.MODEL))

    def test_set_rule(self):
        from libcellml import Issue, SpecificationRule

        # void setRule(SpecificationRule rule)
        e = Issue()
        e.setRule(SpecificationRule.MAP_VARIABLES_VARIABLE2)

    def test_rule(self):
        from libcellml import Issue, SpecificationRule

        # SpecificationRule rule()
        e = Issue()
        self.assertEqual(e.rule(), SpecificationRule.UNDEFINED)

    def test_specification_heading(self):
        from libcellml import Issue

        # std::string specificationHeading()
        e = Issue()
        self.assertEqual('', e.specificationHeading())

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

    def test_set_when(self):
        from libcellml import Issue, When

        # void setWhen(const WhenPtr &when);
        e = Issue()
        e.setWhen(When())

    def test_when(self):
        from libcellml import Issue, When

        # WhenPtr when() const;
        e = Issue()
        self.assertIsNone(e.when())
        name = 'var'
        w = When()
        w.setId(name)
        e.setWhen(w)
        self.assertIsInstance(e.when(), When)
        self.assertEqual(e.when().id(), name)


if __name__ == '__main__':
    unittest.main()
