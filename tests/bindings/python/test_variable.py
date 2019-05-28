#
# Tests the Variable class bindings
#
import unittest


class VariableTestCase(unittest.TestCase):

    def test_create_destroy(self):
        from libcellml import Variable

        x = Variable()
        del(x)
        y = Variable()
        z = Variable(y)
        del(y, z)

    def test_inheritance(self):
        import libcellml
        from libcellml import Variable

        x = Variable()
        self.assertIsInstance(x, libcellml.NamedEntity)
        self.assertIsInstance(x, libcellml.Entity)

        # Test access to inherited methods
        x = Variable()
        idx = 'test'
        self.assertEqual(x.getId(), '')
        x.setId(idx)
        self.assertEqual(x.getId(), idx)
        y = Variable(x)
        self.assertEqual(y.getId(), idx)

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

    def test_get_equivalent_variable(self):
        from libcellml import Variable

        # VariablePtr getEquivalentVariable(size_t index)
        v1 = Variable()
        v2 = Variable()
        v3 = Variable()
        self.assertIsNone(v1.getEquivalentVariable(0))
        self.assertIsNone(v1.getEquivalentVariable(1))
        self.assertIsNone(v1.getEquivalentVariable(-1))
        Variable.addEquivalence(v1, v2)
        Variable.addEquivalence(v1, v3)
        self.assertIsNone(v1.getEquivalentVariable(2))
        self.assertIsNone(v1.getEquivalentVariable(-1))
        self.assertIsNotNone(v1.getEquivalentVariable(0))
        self.assertIsNotNone(v1.getEquivalentVariable(1))

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

    def test_has_equivalent_variable(self):
        from libcellml import Variable

        # bool hasEquivalentVariable(const VariablePtr &equivalentVariable)
        v1 = Variable()
        v2 = Variable()
        v3 = Variable()
        self.assertFalse(v1.hasEquivalentVariable(v1))
        self.assertFalse(v1.hasEquivalentVariable(v2))
        self.assertFalse(v1.hasEquivalentVariable(v3))
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
        self.assertEqual(v.getUnits(), name)

    def test_get_units(self):
        from libcellml import Variable

        # std::string getUnits()
        name = 'testo'
        v = Variable()
        self.assertEqual(v.getUnits(), '')
        v.setUnits(name)
        self.assertEqual(v.getUnits(), name)
        v.setUnits('')
        self.assertEqual(v.getUnits(), '')
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

    def test_get_initial_value(self):
        from libcellml import Variable

        # std::string getInitialValue()
        value = '5 + x'
        v = Variable()
        self.assertEqual(v.getInitialValue(), '')
        v.setInitialValue(value)
        self.assertEqual(v.getInitialValue(), value)

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

    def test_get_interface_type(self):
        from libcellml import Variable

        # std::string getInterfaceType()
        v = Variable()
        self.assertEqual(v.getInterfaceType(), '')
        v.setInterfaceType(Variable.InterfaceType.NONE)
        self.assertEqual(v.getInterfaceType(), 'none')
        v.setInterfaceType(Variable.InterfaceType.PRIVATE)
        self.assertEqual(v.getInterfaceType(), 'private')
        v.setInterfaceType(Variable.InterfaceType.PUBLIC)
        self.assertEqual(v.getInterfaceType(), 'public')
        v.setInterfaceType(Variable.InterfaceType.PUBLIC_AND_PRIVATE)
        self.assertEqual(v.getInterfaceType(), 'public_and_private')


if __name__ == '__main__':
    unittest.main()
