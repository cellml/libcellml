#
# Tests the Component class bindings
#
import unittest


class ComponentTestCase(unittest.TestCase):

    def test_create_destroy(self):
        from libcellml import Component

        # Test create/copy/destroy
        x = Component()
        del(x)
        y = Component()
        z = Component(y)
        del(y, z)

    def test_inheritance(self):
        import libcellml
        from libcellml import Component

        x = Component()
        self.assertIsInstance(x, libcellml.ComponentEntity)
        self.assertIsInstance(x, libcellml.ImportedEntity)
        self.assertIsInstance(x, libcellml.NamedEntity)
        self.assertIsInstance(x, libcellml.Entity)

    def test_inherited_methods(self):
        from libcellml import Component

        x = Component()
        idx = 'test'
        self.assertEqual(x.id(), '')
        x.setId(idx)
        self.assertEqual(x.id(), idx)
        y = Component(x)
        self.assertEqual(y.id(), idx)

    def test_set_source(self):
        from libcellml import Component, ImportSource

        x = Component()
        i = ImportSource()
        i.setUrl('bonjour')
        x.setSourceComponent(i, 'camembert')
        self.assertEqual(x.importSource().url(), 'bonjour')
        self.assertEqual(x.importReference(), 'camembert')

    def test_math(self):
        from libcellml import Component

        # appendMath(const std::string &math)
        x = Component()
        x.appendMath('More maths')
        x.appendMath(' please!')

        # std::string math()
        self.assertEqual(x.math(), 'More maths please!')
        x = Component()
        self.assertEqual(x.math(), '')

        # void setMath(const std::string &math)
        x.setMath('bonjour')
        self.assertEqual(x.math(), 'bonjour')
        x.setMath('hola')
        self.assertEqual(x.math(), 'hola')

    def test_add_variable(self):
        from libcellml import Component, Variable

        c = Component()
        v = Variable()
        c.addVariable(v)

    def test_has_variable(self):
        from libcellml import Component, Variable

        # bool hasVariable(const VariablePtr &variable)
        c = Component()
        v = Variable()
        self.assertFalse(c.hasVariable(v))
        c.addVariable(v)
        self.assertTrue(c.hasVariable(v))
        self.assertFalse(c.hasVariable(Variable()))
        del(c, v)

        # bool hasVariable(const std::string &name)
        c = Component()
        self.assertFalse(c.hasVariable(''))
        v1 = Variable()
        c.addVariable(v1)
        self.assertFalse(c.hasVariable('blue'))
        self.assertTrue(c.hasVariable(''))
        name = 'yellow'
        v2 = Variable()
        v2.setName(name)
        c.addVariable(v2)
        self.assertTrue(c.hasVariable(name))
        del(c, v1, v2, name)

    def test_remove_variable(self):
        from libcellml import Component, Variable

        # bool removeVariable(size_t index)
        c = Component()
        self.assertFalse(c.removeVariable(0))
        self.assertFalse(c.removeVariable(-1))
        self.assertFalse(c.removeVariable(1))
        c.addVariable(Variable())
        self.assertFalse(c.removeVariable(-1))
        self.assertFalse(c.removeVariable(1))
        self.assertTrue(c.removeVariable(0))
        self.assertFalse(c.removeVariable(0))
        del(c)

        # bool removeVariable(const std::string &name)
        c = Component()
        self.assertFalse(c.removeVariable(''))
        v1 = Variable()
        c.addVariable(v1)
        self.assertTrue(c.removeVariable(''))
        self.assertFalse(c.removeVariable(''))
        name = 'blue'
        v1.setName(name)
        self.assertFalse(c.removeVariable(name))
        c.addVariable(v1)
        self.assertTrue(c.removeVariable(name))
        self.assertFalse(c.removeVariable(name))
        del(c, v1, name)

        # bool removeVariable(const VariablePtr &variable)
        c = Component()
        v1 = Variable()
        v2 = Variable()
        self.assertFalse(c.removeVariable(v1))
        c.addVariable(v1)
        self.assertFalse(c.removeVariable(v2))
        self.assertTrue(c.removeVariable(v1))
        self.assertFalse(c.removeVariable(v1))

    def test_remove_all_variables(self):
        from libcellml import Component, Variable

        # void removeAllVariables()
        c = Component()
        v1 = Variable()
        v2 = Variable()
        c.addVariable(v1)
        c.addVariable(v2)
        self.assertTrue(c.hasVariable(v1))
        self.assertTrue(c.hasVariable(v2))
        c.removeAllVariables()
        self.assertFalse(c.hasVariable(v1))
        self.assertFalse(c.hasVariable(v2))

    def test_variable(self):
        from libcellml import Component, Variable

        # VariablePtr variable(size_t index)
        c = Component()
        v = Variable()
        name = 'green'
        v.setName(name)
        self.assertIsNone(c.variable(0))
        self.assertIsNone(c.variable(1))
        self.assertIsNone(c.variable(-1))
        c.addVariable(v)
        self.assertIsNone(c.variable(1))
        self.assertIsNone(c.variable(-1))
        self.assertIsNotNone(c.variable(0))
        self.assertEqual(c.variable(0).name(), name)
        del(c, v, name)

        # VariablePtr variable(const std::string &name)
        c = Component()
        v = Variable()
        name = 'green'
        v.setName(name)
        self.assertIsNone(c.variable(name))
        c.addVariable(v)
        self.assertIsNone(c.variable('red'))
        self.assertIsNotNone(c.variable(name))
        self.assertEqual(c.variable(name).name(), name)

    def test_variable_count(self):
        from libcellml import Component, Variable

        # size_t variableCount()
        c = Component()
        self.assertEqual(c.variableCount(), 0)
        c.addVariable(Variable())
        self.assertEqual(c.variableCount(), 1)
        c.addVariable(Variable())
        self.assertEqual(c.variableCount(), 2)
        c.removeVariable('')
        self.assertEqual(c.variableCount(), 1)
        c.removeVariable('')
        self.assertEqual(c.variableCount(), 0)


if __name__ == '__main__':
    unittest.main()
