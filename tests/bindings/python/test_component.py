#
# Tests the Component class bindings
#
import sys
import unittest

class ComponentTestCase(unittest.TestCase):

    def test_component(self):
        from libcellml.component import Component
        
        # Test create/copy/destroy
        x = Component()
        del(x)
        y = Component()
        z = Component(y)
        del(y,z)
        
        # Test inheritance
        x = Component()
        from libcellml.componententity import ComponentEntity
        self.assertIsInstance(x, ComponentEntity)
        from libcellml.importedentity import ImportedEntity
        self.assertIsInstance(x, ImportedEntity)
        from libcellml.namedentity import NamedEntity
        self.assertIsInstance(x, NamedEntity)
        from libcellml.entity import Entity
        self.assertIsInstance(x, Entity)
        
        # Test access to inherited methods
        x = Component()
        idx = 'test'
        self.assertEqual(x.getId(), '')
        x.setId(idx)
        self.assertEqual(x.getId(), idx)
        y = Component(x)
        self.assertEqual(y.getId(), idx)
        del(x, y)
        
        # Test own methods

        # void setSourceComponent(const ImportPtr& imp,
        #   const std::string &name)
        from libcellml.importsource import Import
        x = Component()
        i = Import()
        i.setSource('bonjour')
        x.setSourceComponent(i, 'camembert')
        self.assertEqual(x.getImport().getSource(), 'bonjour')
        self.assertEqual(x.getImportReference(), 'camembert')
        del(x, i)

        # appendMath(const std::string &math)
        x = Component()
        x.appendMath('More maths')
        x.appendMath(' please!')
        
        # std::string getMath()
        self.assertEqual(x.getMath(), 'More maths please!')
        x = Component()
        self.assertEqual(x.getMath(), '')
        
        # void setMath(const std::string &math)
        x.setMath('bonjour')
        self.assertEqual(x.getMath(), 'bonjour')
        x.setMath('hola')
        self.assertEqual(x.getMath(), 'hola')
        del(x)

        # void addVariable(const VariablePtr &v)
        from libcellml.variable import Variable
        c = Component()
        v = Variable()
        c.addVariable(v)
        del(c, v)

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
        
        #TODO: bool removeVariable(size_t index)
        
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
        del(c, v1, v2)
        
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
        del(c, v1, v2)
                
        # VariablePtr getVariable(size_t index)
        c = Component()
        v = Variable()
        name = 'green'
        v.setName(name)
        self.assertIsNone(c.getVariable(0))
        c.addVariable(v)
        self.assertIsNone(c.getVariable(1))
        self.assertIsNotNone(c.getVariable(0))
        self.assertEqual(c.getVariable(0).getName(), name)
        del(c, v, name)
                
        # VariablePtr getVariable(const std::string &name)
        c = Component()
        v = Variable()
        name = 'green'
        v.setName(name)
        self.assertIsNone(c.getVariable(name))
        c.addVariable(v)
        self.assertIsNone(c.getVariable('red'))
        self.assertIsNotNone(c.getVariable(name))
        self.assertEqual(c.getVariable(name).getName(), name)
        del(c, v, name)
        
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
        del(c)

if __name__ == '__main__':
    unittest.main()
