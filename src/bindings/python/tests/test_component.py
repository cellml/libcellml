#
# Tests the Component class
#
import unittest
class TestComponent(unittest.TestCase):

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
        #TODO Models, components etc.
    

        
        
        
