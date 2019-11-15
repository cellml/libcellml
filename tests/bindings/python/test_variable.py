#
# Tests the Variable class bindings
#
import unittest


class VariableTestCase(unittest.TestCase):

    def test_create_destroy(self):
        from libcellml import Variable

        x = Variable()
        del(x)

        y = Variable("nice")
        self.assertEqual("nice", y.name())
        del y

    def test_inheritance(self):
        import libcellml
        from libcellml import Variable

        x = Variable()
        self.assertIsInstance(x, libcellml.namedentity.NamedEntity)
        self.assertIsInstance(x, libcellml.entity.Entity)

        # Test access to inherited methods
        x = Variable()
        idx = 'test'
        self.assertEqual(x.id(), '')
        x.setId(idx)
        self.assertEqual(x.id(), idx)

    def test_add_equivalence(self):
        from libcellml import Variable

        # static void addEquivalence(const VariablePtr &variable1,
        #   const VariablePtr &variable2)
        v1 = Variable()
        v2 = Variable()
        Variable.addEquivalence(v1, v2)

    def test_remove_equivalence(self):
        from libcellml import Variable

        # static bool removeEquivalence(const VariablePtr &variable1,
        #   const VariablePtr &variable2)
        v1 = Variable()
        v2 = Variable()
        v3 = Variable()
        self.assertFalse(Variable.removeEquivalence(v1, v2))
        Variable.addEquivalence(v1, v2)
        self.assertFalse(Variable.removeEquivalence(v1, v3))
        self.assertFalse(Variable.removeEquivalence(v3, v2))
        self.assertTrue(Variable.removeEquivalence(v1, v2))
        self.assertFalse(Variable.removeEquivalence(v1, v2))
        Variable.addEquivalence(v1, v2)
        self.assertTrue(Variable.removeEquivalence(v2, v1))

    def test_remove_all_equivalences(self):
        from libcellml import Variable

        # void removeAllEquivalences()
        v1 = Variable()
        v2 = Variable()
        v3 = Variable()
        Variable.addEquivalence(v1, v2)
        Variable.addEquivalence(v1, v3)
        v2.removeAllEquivalences()
        self.assertFalse(Variable.removeEquivalence(v1, v2))
        self.assertTrue(Variable.removeEquivalence(v1, v3))

    def test_equivalent_variable(self):
        from libcellml import Variable

        # VariablePtr equivalentVariable(size_t index)
        v1 = Variable()
        v2 = Variable()
        v3 = Variable()
        self.assertIsNone(v1.equivalentVariable(0))
        self.assertIsNone(v1.equivalentVariable(1))
        self.assertIsNone(v1.equivalentVariable(-1))
        Variable.addEquivalence(v1, v2)
        Variable.addEquivalence(v1, v3)
        self.assertIsNone(v1.equivalentVariable(2))
        self.assertIsNone(v1.equivalentVariable(-1))
        self.assertIsNotNone(v1.equivalentVariable(0))
        self.assertIsNotNone(v1.equivalentVariable(1))

    def test_equivalent_variable_count(self):
        from libcellml import Variable

        # size_t equivalentVariableCount()
        v1 = Variable()
        v2 = Variable()
        v3 = Variable()
        self.assertEqual(v1.equivalentVariableCount(), 0)
        self.assertEqual(v2.equivalentVariableCount(), 0)
        self.assertEqual(v3.equivalentVariableCount(), 0)
        Variable.addEquivalence(v1, v2)
        Variable.addEquivalence(v2, v3)
        self.assertEqual(v1.equivalentVariableCount(), 1)
        self.assertEqual(v2.equivalentVariableCount(), 2)
        self.assertEqual(v3.equivalentVariableCount(), 1)

    def test_has_direct_equivalent_variable(self):
        from libcellml import Variable

        # bool hasEquivalentVariable(const VariablePtr &equivalentVariable)
        v1 = Variable()
        v2 = Variable()
        v3 = Variable()

        self.assertFalse(v1.hasEquivalentVariable(v1))
        self.assertFalse(v1.hasEquivalentVariable(v2))
        self.assertFalse(v1.hasEquivalentVariable(v3))

        self.assertFalse(v2.hasEquivalentVariable(v1))
        self.assertFalse(v2.hasEquivalentVariable(v2))
        self.assertFalse(v2.hasEquivalentVariable(v3))

        self.assertFalse(v3.hasEquivalentVariable(v1))
        self.assertFalse(v3.hasEquivalentVariable(v2))
        self.assertFalse(v3.hasEquivalentVariable(v3))

        Variable.addEquivalence(v1, v2)
        Variable.addEquivalence(v2, v3)

        self.assertFalse(v1.hasEquivalentVariable(v1))
        self.assertTrue(v1.hasEquivalentVariable(v2))
        self.assertFalse(v1.hasEquivalentVariable(v3))

        self.assertTrue(v2.hasEquivalentVariable(v1))
        self.assertFalse(v2.hasEquivalentVariable(v2))
        self.assertTrue(v2.hasEquivalentVariable(v3))

        self.assertFalse(v3.hasEquivalentVariable(v1))
        self.assertTrue(v3.hasEquivalentVariable(v2))
        self.assertFalse(v3.hasEquivalentVariable(v3))

    def test_has_equivalent_variable(self):
        from libcellml import Variable

        # bool hasIndirectEquivalentVariable(const VariablePtr &equivalentVariable)
        v1 = Variable()
        v2 = Variable()
        v3 = Variable()

        self.assertFalse(v1.hasIndirectEquivalentVariable(v1))
        self.assertFalse(v1.hasIndirectEquivalentVariable(v2))
        self.assertFalse(v1.hasIndirectEquivalentVariable(v3))

        self.assertFalse(v2.hasIndirectEquivalentVariable(v1))
        self.assertFalse(v2.hasIndirectEquivalentVariable(v2))
        self.assertFalse(v2.hasIndirectEquivalentVariable(v3))

        self.assertFalse(v3.hasIndirectEquivalentVariable(v1))
        self.assertFalse(v3.hasIndirectEquivalentVariable(v2))
        self.assertFalse(v3.hasIndirectEquivalentVariable(v3))

        Variable.addEquivalence(v1, v2)
        Variable.addEquivalence(v2, v3)

        self.assertFalse(v1.hasIndirectEquivalentVariable(v1))
        self.assertTrue(v1.hasIndirectEquivalentVariable(v2))
        self.assertTrue(v1.hasIndirectEquivalentVariable(v3))

        self.assertTrue(v2.hasIndirectEquivalentVariable(v1))
        self.assertFalse(v2.hasIndirectEquivalentVariable(v2))
        self.assertTrue(v2.hasIndirectEquivalentVariable(v3))

        self.assertTrue(v3.hasIndirectEquivalentVariable(v1))
        self.assertTrue(v3.hasIndirectEquivalentVariable(v2))
        self.assertFalse(v3.hasIndirectEquivalentVariable(v3))

    def test_set_units(self):
        from libcellml import Variable, Units

        # void setUnits(const std::string &name)
        v = Variable()
        v.setUnits('')
        v.setUnits('Hello')
        v.setUnits('')
        del(v)

        # void setUnits(const UnitsPtr &units)
        name = 'tiger'
        u = Units()
        u.setName(name)
        v = Variable()
        v.setUnits(u)
        self.assertEqual(v.units().name(), name)

    def test_units(self):
        from libcellml import Variable

        # std::string units()
        name = 'testo'
        v = Variable()
        self.assertEqual(v.units(), None)
        v.setUnits(name)
        self.assertEqual(v.units().name(), name)
        v.setUnits('')
        self.assertEqual(v.units().name(), '')
        del(v, name)

    def test_set_initial_value(self):
        from libcellml import Variable

        # void setInitialValue(const std::string &initialValue)
        v = Variable()
        v.setInitialValue('test')
        del(v)

        # void setInitialValue(double initialValue)
        v = Variable()
        v.setInitialValue('test')
        del(v)

        # void setInitialValue(const VariablePtr &variable)
        v1 = Variable()
        v2 = Variable()
        v1.setInitialValue(v2)
        del(v1, v2)

    def test_initial_value(self):
        from libcellml import Variable

        # std::string initialValue()
        value = '5 + x'
        v = Variable()
        self.assertEqual(v.initialValue(), '')
        v.setInitialValue(value)
        self.assertEqual(v.initialValue(), value)

    def test_interface_type(self):
        from libcellml import Variable

        # InterfaceType
        self.assertNotEqual(
            Variable.InterfaceType.NONE,
            Variable.InterfaceType.PRIVATE,
            )
        self.assertNotEqual(
            Variable.InterfaceType.PUBLIC,
            Variable.InterfaceType.PUBLIC_AND_PRIVATE,
            )

    def test_set_interface_type(self):
        from libcellml import Variable

        # void setInterfaceType(const std::string &interfaceType)
        v = Variable()
        v.setInterfaceType('special type')

        # void setInterfaceType(InterfaceType interfaceType)
        v = Variable()
        v.setInterfaceType(Variable.InterfaceType.NONE)
        v.setInterfaceType(Variable.InterfaceType.PRIVATE)
        v.setInterfaceType(Variable.InterfaceType.PUBLIC)
        v.setInterfaceType(Variable.InterfaceType.PUBLIC_AND_PRIVATE)
        self.assertRaises(
            RuntimeError, v.setInterfaceType, Variable.InterfaceType.NONE - 1)
        self.assertRaises(
            RuntimeError, v.setInterfaceType,
            Variable.InterfaceType.PUBLIC_AND_PRIVATE + 1)
        del(v)

        # void setInterfaceType(const std::string &interfaceType)
        v = Variable()
        v.setInterfaceType('not an interface type')
        del(v)

    def test_interface_type(self):
        from libcellml import Variable

        # std::string interfaceType()
        v = Variable()
        self.assertEqual(v.interfaceType(), '')
        v.setInterfaceType(Variable.InterfaceType.NONE)
        self.assertEqual(v.interfaceType(), 'none')
        v.setInterfaceType(Variable.InterfaceType.PRIVATE)
        self.assertEqual(v.interfaceType(), 'private')
        v.setInterfaceType(Variable.InterfaceType.PUBLIC)
        self.assertEqual(v.interfaceType(), 'public')
        v.setInterfaceType(Variable.InterfaceType.PUBLIC_AND_PRIVATE)
        self.assertEqual(v.interfaceType(), 'public_and_private')


if __name__ == '__main__':
    unittest.main()
