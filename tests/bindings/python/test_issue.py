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

        # Test conversion to enum
        e = Issue()
        e.setCause(ItemType.COMPONENT)
        self.assertRaises(RuntimeError, e.setCause, ItemType.COMPONENT - 1)
        self.assertRaises(RuntimeError, e.setCause, ItemType.VARIABLE + 1)

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
        from libcellml import Issue, Variable
        from libcellml.issue import VariablePair

        e = Issue()
        self.assertIsNone(e.connection()[0])
        v1 = Variable("v1")
        v2 = Variable("v2")

        e.setConnection(VariablePair(v1, v2))
        p = e.connection()
        self.assertIsInstance(p[0], Variable)
        self.assertEqual(p[0].name(), "v1")
        self.assertEqual(p[1].name(), "v2")

    def test_map_variables(self):
        from libcellml import Issue, Variable
        from libcellml.issue import VariablePair

        e = Issue()
        self.assertIsNone(e.mapVariables()[0])
        v1 = Variable("v1")
        v2 = Variable("v2")

        e.setMapVariables(VariablePair(v1, v2))
        p = e.mapVariables()
        self.assertIsInstance(p[0], Variable)
        self.assertEqual(p[0].name(), "v1")
        self.assertEqual(p[1].name(), "v2")

    def test_unit_item(self):
        from libcellml import Issue, Units
        from libcellml.issue import UnitItem

        e = Issue()
        self.assertIsNone(e.unit()[0])
        u = Units("my_units")

        e.setUnit(UnitItem(u, 3))
        ui = e.unit()
        self.assertIsInstance(ui[0], Units)
        self.assertEqual(ui[0].name(), "my_units")
        self.assertEqual(ui[1], 3)

    def test_item(self):
        from libcellml import Component, Issue, ImportSource, Model
        from libcellml import Reset, Units, Variable, ItemType
        from libcellml.issue import UnitItem, VariablePair

        i = Issue()

        item = i.item()
        self.assertEqual(ItemType.UNDEFINED, item[0])
        self.assertIsNone(item[1])

        i.setItem(ItemType.VARIABLE, Variable("v"))
        vItem = i.item()
        self.assertEqual(ItemType.VARIABLE, vItem[0])
        self.assertEqual("v", vItem[1].name())

        i.setItem(ItemType.UNITS, Units("u"))
        uItem = i.item()
        self.assertEqual(ItemType.UNITS, uItem[0])
        self.assertEqual("u", uItem[1].name())

        i.setItem(ItemType.UNIT, UnitItem(Units("ui"), 2))
        uiItem = i.item()
        self.assertEqual(ItemType.UNIT, uiItem[0])
        self.assertEqual("ui", uiItem[1][0].name())
        self.assertEqual(2, uiItem[1][1])

        i.setItem(ItemType.CONNECTION, VariablePair(Variable("v1"), Variable("v2")))
        vpItem = i.item()
        self.assertEqual(ItemType.CONNECTION, vpItem[0])
        self.assertEqual("v1", vpItem[1].first.name())
        self.assertEqual("v2", vpItem[1].second.name())

        i.setItem(ItemType.MAP_VARIABLES, VariablePair(Variable("v3"), Variable("v4")))
        vpItem = i.item()
        self.assertEqual(ItemType.MAP_VARIABLES, vpItem[0])
        self.assertEqual("v3", vpItem[1].first.name())
        self.assertEqual("v4", vpItem[1].second.name())

        r = Reset()
        r.setId("r")
        i.setItem(ItemType.RESET, r)
        rItem = i.item()
        self.assertEqual(ItemType.RESET, rItem[0])
        self.assertEqual("r", rItem[1].id())

        r.setId("r1")
        i.setItem(ItemType.RESET_VALUE, r)
        rItem = i.item()
        self.assertEqual(ItemType.RESET_VALUE, rItem[0])
        self.assertEqual("r1", rItem[1].id())

        r.setId("r2")
        i.setItem(ItemType.TEST_VALUE, r)
        rItem = i.item()
        self.assertEqual(ItemType.TEST_VALUE, rItem[0])
        self.assertEqual("r2", rItem[1].id())

        i.setItem(ItemType.MODEL, Model("m"))
        mItem = i.item()
        self.assertEqual(ItemType.MODEL, mItem[0])
        self.assertEqual("m", mItem[1].name())

        i.setItem(ItemType.ENCAPSULATION, Model("e"))
        mItem = i.item()
        self.assertEqual(ItemType.ENCAPSULATION, mItem[0])
        self.assertEqual("e", mItem[1].name())

        iS  = ImportSource()
        iS.setId("is")
        i.setItem(ItemType.IMPORT, iS)
        isItem = i.item()
        self.assertEqual(ItemType.IMPORT, isItem[0])
        self.assertEqual("is", isItem[1].id())

        i.setItem(ItemType.COMPONENT, Component("c"))
        cItem = i.item()
        self.assertEqual(ItemType.COMPONENT, cItem[0])
        self.assertEqual("c", cItem[1].name())

        i.setItem(ItemType.COMPONENT_REF, Component("c1"))
        cItem = i.item()
        self.assertEqual(ItemType.COMPONENT_REF, cItem[0])
        self.assertEqual("c1", cItem[1].name())

    def test_item_bad_input(self):
        from libcellml import Issue, Variable, ItemType

        i = Issue()
        self.assertRaises(TypeError, i.setItem, ItemType.COMPONENT_REF, Variable("v1"))
        cItem = i.item()
        self.assertEqual(ItemType.UNDEFINED, cItem[0])
        self.assertIsNone(cItem[1])

    def test_clear(self):
        from libcellml import Issue, Variable, ItemType

        i = Issue()
        i.clear()
        self.assertEqual(ItemType.UNDEFINED, i.itemType())

        v1 = Variable("v1")
        i.setVariable(v1)

        self.assertEqual(ItemType.VARIABLE, i.itemType())

        i.clear()
        self.assertEqual(ItemType.UNDEFINED, i.itemType())

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
        from libcellml import Units
        from libcellml.issue import UnitItem
        #from libcellml.types import UnitItem

        u = Units("bob")
        u_i = UnitItem()
        self.assertEqual(2, len(u_i))
        self.assertEqual("(None, 0)", str(u_i))
        u_i[0] = u
        u_i[1] = 4
        self.assertEqual("bob", u_i.first.name())
        self.assertEqual(4, u_i.second)

    def test_variable_pair_coverage(self):
        from libcellml import Variable
        from libcellml.issue import VariablePair
        #from libcellml.types import UnitItem

        v1 = Variable("ray")
        v2 = Variable("charles")
        v_p = VariablePair()
        self.assertEqual(2, len(v_p))
        self.assertEqual("(None, None)", str(v_p))
        v_p[0] = v1
        v_p[1] = v2
        self.assertEqual("ray", v_p.first.name())
        self.assertEqual("charles", v_p.second.name())


if __name__ == '__main__':
    unittest.main()
