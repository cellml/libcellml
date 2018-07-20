#
# Tests the Error class bindings
#
import unittest


class ErrorTestCase(unittest.TestCase):

    def test_create_destroy(self):
        from libcellml import Error

        x = Error()
        del(x)
        y = Error()
        z = Error(y)
        del(y, z)

    def test_kind_enum(self):
        from libcellml import Error

        self.assertIsInstance(Error.Kind.COMPONENT, int)
        self.assertIsInstance(Error.Kind.CONNECTION, int)
        self.assertIsInstance(Error.Kind.ENCAPSULATION, int)
        self.assertIsInstance(Error.Kind.IMPORT, int)
        self.assertIsInstance(Error.Kind.MATHML, int)
        self.assertIsInstance(Error.Kind.MODEL, int)
        self.assertIsInstance(Error.Kind.UNDEFINED, int)
        self.assertIsInstance(Error.Kind.UNITS, int)
        self.assertIsInstance(Error.Kind.VARIABLE, int)
        self.assertIsInstance(Error.Kind.XML, int)

        # Test conversion to enum
        e = Error()
        e.setKind(Error.Kind.COMPONENT)
        self.assertRaises(RuntimeError, e.setKind, Error.Kind.COMPONENT - 1)
        self.assertRaises(RuntimeError, e.setKind, Error.Kind.XML + 1)

    def test_specification_rule_enum(self):
        from libcellml import Error, SpecificationRule

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
        e = Error()
        e.setRule(SpecificationRule.UNDEFINED)
        self.assertRaises(
            RuntimeError, e.setRule, SpecificationRule.UNDEFINED - 1)
        self.assertRaises(
            RuntimeError, e.setRule,
            SpecificationRule.MAP_VARIABLES_UNIQUE + 1)
        del(e)

    def test_set_description(self):
        from libcellml import Error

        # void setDescription(const std::string &description)
        e = Error()
        e.setDescription('hello')
        e.setDescription('')

    def test_get_description(self):
        from libcellml import Error

        # std::string getDescription()
        d = 'hi'
        e = Error()
        self.assertEqual(e.getDescription(), '')
        e.setDescription(d)
        self.assertEqual(e.getDescription(), d)
        del(d, e)

    def test_set_kind(self):
        from libcellml import Error

        # void setKind(Kind kind)
        e = Error()
        e.setKind(Error.Kind.CONNECTION)

    def test_get_kind(self):
        from libcellml import Error

        # Kind getKind()
        e = Error()
        self.assertEqual(e.getKind(), Error.Kind.UNDEFINED)
        e.setKind(Error.Kind.MATHML)
        self.assertEqual(e.getKind(), Error.Kind.MATHML)

    def test_is_kind(self):
        from libcellml import Error

        # bool isKind(const Kind &kind)
        e = Error()
        self.assertTrue(e.isKind(Error.Kind.UNDEFINED))
        self.assertFalse(e.isKind(Error.Kind.MODEL))

    def test_set_rule(self):
        from libcellml import Error, SpecificationRule

        # void setRule(SpecificationRule rule)
        e = Error()
        e.setRule(SpecificationRule.MAP_VARIABLES_VARIABLE2)

    def test_get_rule(self):
        from libcellml import Error, SpecificationRule

        # SpecificationRule getRule()
        e = Error()
        self.assertEqual(e.getRule(), SpecificationRule.UNDEFINED)

    def test_get_specification_heading(self):
        from libcellml import Error

        # std::string getSpecificationHeading()
        e = Error()
        self.assertEqual('', e.getSpecificationHeading())

    def test_set_component(self):
        from libcellml import Error, Component

        # void setComponent(const ComponentPtr &component)
        e = Error()
        e.setComponent(Component())

    def test_get_component(self):
        from libcellml import Error, Component

        # ComponentPtr getComponent()
        e = Error()
        self.assertIsNone(e.getComponent())
        name = 'cellml'
        c = Component()
        c.setName(name)
        e.setComponent(c)
        self.assertIsInstance(e.getComponent(), Component)
        self.assertEqual(e.getComponent().getName(), name)

    def test_set_import_source(self):
        from libcellml import Error, ImportSource

        # void setImportSource(const ImportSourcePtr &import)
        e = Error()
        e.setImportSource(ImportSource())

    def test_get_import_source(self):
        from libcellml import Error, ImportSource

        # ImportSourcePtr getImportSource()
        e = Error()
        self.assertIsNone(e.getComponent())
        name = 'uri'
        i = ImportSource()
        i.setId(name)
        e.setImportSource(i)
        self.assertIsInstance(e.getImportSource(), ImportSource)
        self.assertEqual(e.getImportSource().getId(), name)

    def test_set_model(self):
        from libcellml import Error, Model

        # void setModel(const ModelPtr &model)
        e = Error()
        e.setModel(Model())

    def test_get_model(self):
        from libcellml import Error, Model

        # ModelPtr getModel()
        e = Error()
        self.assertIsNone(e.getModel())
        name = 'moodle'
        m = Model()
        m.setName(name)
        e.setModel(m)
        self.assertIsInstance(e.getModel(), Model)
        self.assertEqual(e.getModel().getName(), name)

    def test_set_units(self):
        from libcellml import Error, Units

        # void setUnits(const UnitsPtr &units)
        e = Error()
        e.setUnits(Units())

    def test_get_units(self):
        from libcellml import Error, Units

        # UnitsPtr getUnits()
        e = Error()
        self.assertIsNone(e.getUnits())
        name = 'furlong'
        u = Units()
        u.setName(name)
        e.setUnits(u)
        self.assertIsInstance(e.getUnits(), Units)
        self.assertEqual(e.getUnits().getName(), name)

    def test_set_variable(self):
        from libcellml import Error, Variable

        # void setVariable(const VariablePtr &variable)
        e = Error()
        e.setVariable(Variable())

    def test_get_variable(self):
        from libcellml import Error, Variable

        # VariablePtr getVariable()
        e = Error()
        self.assertIsNone(e.getVariable())
        name = 'var'
        v = Variable()
        v.setName(name)
        e.setVariable(v)
        self.assertIsInstance(e.getVariable(), Variable)
        self.assertEqual(e.getVariable().getName(), name)


if __name__ == '__main__':
    unittest.main()
