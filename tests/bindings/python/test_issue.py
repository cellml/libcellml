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
        from libcellml import Unit
        from libcellml import Units
        from libcellml import Variable
        from libcellml import VariablePair

        e1 = Issue()
        del e1

        c = Component()
        e2 = Issue(c)
        del e2

        i = ImportSource()
        e3 = Issue(i)
        del e3

        m = Model()
        e4 = Issue(m)
        del e4

        r = Reset()
        e5 = Issue(r)
        del e5

        u = Units()
        e6 = Issue(u)
        del e6

        v = Variable()
        e7 = Issue(v)
        del e7

        v1 = Variable("v1")
        v2 = Variable("v2")
        vp = VariablePair(v1, v2)
        e8 = Issue(vp)
        del e8

        ui = Unit(u, 0)
        e9 = Issue(ui)
        del e9

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
        self.assertIsInstance(Issue.ReferenceRule.IMPORT_ATTRIBUTE, int)
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
        self.assertIsInstance(
            Issue.ReferenceRule.MAP_VARIABLES_IDENTICAL_UNIT_REDUCTION, int)
        self.assertIsInstance(
            Issue.ReferenceRule.UNSPECIFIED, int)

        # Test conversion to enum
        e = Issue()
        e.setReferenceRule(Issue.ReferenceRule.UNDEFINED)
        self.assertRaises(RuntimeError, e.setReferenceRule,
                          Issue.ReferenceRule.UNDEFINED - 1)
        self.assertRaises(RuntimeError, e.setReferenceRule,
                          Issue.ReferenceRule.MAP_VARIABLES_IDENTICAL_UNIT_REDUCTION + 1)
        del e

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
        del [d, e]

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

        e = Issue()
        self.assertIsNone(e.variable())
        name = 'var'
        v = Variable()
        v.setName(name)
        e.setVariable(v)
        self.assertIsInstance(e.variable(), Variable)
        self.assertEqual(e.variable().name(), name)

    def test_math(self):
        from libcellml import Issue, Component

        e = Issue()
        self.assertIsNone(e.math())
        c = Component("comp")
        e.setMath(c)
        self.assertIsInstance(e.math(), Component)
        self.assertEqual(e.math().name(), "comp")

    def test_component_ref(self):
        from libcellml import Issue, Component

        e = Issue()
        self.assertIsNone(e.math())
        c = Component("comp")
        e.setComponentRef(c)
        self.assertIsInstance(e.componentRef(), Component)
        self.assertEqual(e.componentRef().name(), "comp")

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

    def test_reset_value(self):
        from libcellml import Issue, Reset

        # ResetPtr reset() const;
        e = Issue()
        self.assertIsNone(e.reset())
        name = 'res'
        r = Reset()
        r.setId(name)
        e.setResetValue(r)
        self.assertIsInstance(e.resetValue(), Reset)
        self.assertEqual(e.resetValue().id(), name)

    def test_test_value(self):
        from libcellml import Issue, Reset

        # ResetPtr reset() const;
        e = Issue()
        self.assertIsNone(e.reset())
        name = 'res'
        r = Reset()
        r.setId(name)
        e.setTestValue(r)
        self.assertIsInstance(e.testValue(), Reset)
        self.assertEqual(e.testValue().id(), name)

    def test_encapsulation(self):
        from libcellml import Issue, Model

        e = Issue()
        self.assertIsNone(e.model())
        name = 'moodle'
        m = Model()
        m.setName(name)
        e.setEncapsulation(m)
        self.assertIsInstance(e.encapsulation(), Model)
        self.assertEqual(e.encapsulation().name(), name)

    def test_connection(self):
        from libcellml import Issue, Variable, VariablePair

        e = Issue()
        self.assertIsNone(e.connection())
        v1 = Variable("v1")
        v2 = Variable("v2")
        e.setConnection(VariablePair(v1, v2))
        p = e.connection()
        self.assertIsInstance(p.variable1(), Variable)
        self.assertEqual(p.variable1().name(), "v1")
        self.assertEqual(p.variable2().name(), "v2")

    def test_map_variables(self):
        from libcellml import Issue, Variable, VariablePair

        e = Issue()
        self.assertIsNone(e.mapVariables())
        v1 = Variable("v1")
        v2 = Variable("v2")

        e.setMapVariables(VariablePair(v1, v2))
        p = e.mapVariables()
        self.assertIsInstance(p.variable1(), Variable)
        self.assertEqual(p.variable1().name(), "v1")
        self.assertEqual(p.variable2().name(), "v2")

    def test_unit_item(self):
        from libcellml import Issue, Units, Unit

        e = Issue()
        self.assertIsNone(e.unit())

        u = Units("my_units")
        u.addUnit("volt")
        u.addUnit("second")
        u.addUnit("kelvin")
        u.addUnit("metre")
        e.setUnit(Unit(u, 3))
        ui = e.unit()
        self.assertIsInstance(ui.units(), Units)
        self.assertEqual(ui.units().name(), "my_units")
        self.assertEqual(ui.index(), 3)

    def test_item(self):
        from libcellml import Component, Issue, ImportSource, Model, Unit
        from libcellml import Reset, Units, Variable, CellmlElementType, VariablePair

        i = Issue()

        item = i.item()
        self.assertEqual(CellmlElementType.UNDEFINED, item[0])
        self.assertIsNone(item[1])

        i.setItem(CellmlElementType.VARIABLE, Variable("v"))
        vItem = i.item()
        self.assertEqual(CellmlElementType.VARIABLE, vItem[0])
        self.assertEqual("v", vItem[1].name())

        i.setItem(CellmlElementType.UNITS, Units("u"))
        uItem = i.item()
        self.assertEqual(CellmlElementType.UNITS, uItem[0])
        self.assertEqual("u", uItem[1].name())

        u = Units("ui")
        u.addUnit("volt")
        u.addUnit("second")
        u.addUnit("metre")
        i.setItem(CellmlElementType.UNIT, Unit(u, 2))
        uiItem = i.item()
        self.assertEqual(CellmlElementType.UNIT, uiItem[0])
        self.assertEqual("ui", uiItem[1].units().name())
        self.assertEqual(2, uiItem[1].index())

        v1 = Variable("v1")
        v2 = Variable("v2")
        i.setItem(CellmlElementType.CONNECTION, VariablePair(v1, v2))
        vpItem = i.item()
        self.assertEqual(CellmlElementType.CONNECTION, vpItem[0])
        self.assertEqual("v1", vpItem[1].variable1().name())
        self.assertEqual("v2", vpItem[1].variable2().name())

        v3 = Variable("v3")
        v4 = Variable("v4")
        i.setItem(CellmlElementType.MAP_VARIABLES, VariablePair(v3, v4))
        vpItem = i.item()
        self.assertEqual(CellmlElementType.MAP_VARIABLES, vpItem[0])
        self.assertEqual("v3", vpItem[1].variable1().name())
        self.assertEqual("v4", vpItem[1].variable2().name())

        r = Reset()
        r.setId("r")
        i.setItem(CellmlElementType.RESET, r)
        rItem = i.item()
        self.assertEqual(CellmlElementType.RESET, rItem[0])
        self.assertEqual("r", rItem[1].id())

        r.setId("r1")
        i.setItem(CellmlElementType.RESET_VALUE, r)
        rItem = i.item()
        self.assertEqual(CellmlElementType.RESET_VALUE, rItem[0])
        self.assertEqual("r1", rItem[1].id())

        r.setId("r2")
        i.setItem(CellmlElementType.TEST_VALUE, r)
        rItem = i.item()
        self.assertEqual(CellmlElementType.TEST_VALUE, rItem[0])
        self.assertEqual("r2", rItem[1].id())

        i.setItem(CellmlElementType.MODEL, Model("m"))
        mItem = i.item()
        self.assertEqual(CellmlElementType.MODEL, mItem[0])
        self.assertEqual("m", mItem[1].name())

        i.setItem(CellmlElementType.ENCAPSULATION, Model("e"))
        mItem = i.item()
        self.assertEqual(CellmlElementType.ENCAPSULATION, mItem[0])
        self.assertEqual("e", mItem[1].name())

        iS  = ImportSource()
        iS.setId("is")
        i.setItem(CellmlElementType.IMPORT, iS)
        isItem = i.item()
        self.assertEqual(CellmlElementType.IMPORT, isItem[0])
        self.assertEqual("is", isItem[1].id())

        i.setItem(CellmlElementType.COMPONENT, Component("c"))
        cItem = i.item()
        self.assertEqual(CellmlElementType.COMPONENT, cItem[0])
        self.assertEqual("c", cItem[1].name())

        i.setItem(CellmlElementType.COMPONENT_REF, Component("c1"))
        cItem = i.item()
        self.assertEqual(CellmlElementType.COMPONENT_REF, cItem[0])
        self.assertEqual("c1", cItem[1].name())

    def test_item_bad_input(self):
        from libcellml import Issue, Variable, CellmlElementType

        i = Issue()
        self.assertRaises(TypeError, i.setItem, CellmlElementType.COMPONENT_REF, Variable("v1"))
        cItem = i.item()
        self.assertEqual(CellmlElementType.UNDEFINED, cItem[0])
        self.assertIsNone(cItem[1])

    def test_clear(self):
        from libcellml import Issue, Variable, CellmlElementType

        i = Issue()
        i.clear()
        self.assertEqual(CellmlElementType.UNDEFINED, i.itemType())

        v1 = Variable("v1")
        i.setVariable(v1)

        self.assertEqual(CellmlElementType.VARIABLE, i.itemType())

        i.clear()
        self.assertEqual(CellmlElementType.UNDEFINED, i.itemType())

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

    def test_unit_item_coverage(self):
        from libcellml import Units, Unit

        u = Units("bob")
        ui = Unit(u, 0)
        self.assertFalse(ui.isValid())

    def test_variable_pair_coverage(self):
        from libcellml import Variable, VariablePair

        v1 = Variable("ray")
        v2 = Variable("charles")
        vp = VariablePair(v1, v2)

        self.assertTrue(vp.isValid())


if __name__ == '__main__':
    unittest.main()
