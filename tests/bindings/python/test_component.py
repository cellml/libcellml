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

        # void addVariable(const VariablePtr &v)
        #TODO
        
        # bool removeVariable(const std::string &name)
        #TODO
        
        # bool removeVariable(const VariablePtr &variable)
        #TODO
        
        # void removeAllVariables()
        #TODO
        
        # VariablePtr getVariable(size_t index)
        #TODO
        
        # VariablePtr getVariable(const std::string &name)
        #TODO
        
        # size_t variableCount()
        #TODO
        
        # bool hasVariable(const VariablePtr &variable)
        #TODO
        
        # bool hasVariable(const std::string &name)
        #TODO
        
if __name__ == '__main__':
    unittest.main()

if __name__ == '__main__':
    unittest.main()
