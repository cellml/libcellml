#
# Tests the ComponentEntity class
#
import sys
import unittest


class ComponentEntityTestCase(unittest.TestCase):

    def test_component_entity(self):
        from libcellml.componententity import ComponentEntity
        
        # Test create/copy/destroy
        x = ComponentEntity()
        del(x)
        y = ComponentEntity()
        z = ComponentEntity(y)
        del(y,z)

        # Test inheritance
        x = ComponentEntity()
        from libcellml.importedentity import ImportedEntity
        self.assertIsInstance(x, ImportedEntity)
        from libcellml.namedentity import NamedEntity
        self.assertIsInstance(x, NamedEntity)
        from libcellml.entity import Entity
        self.assertIsInstance(x, Entity)
                
        # Test access to inherited methods
        idx = 'test'
        self.assertEqual(x.getId(), '')
        x.setId(idx)
        self.assertEqual(x.getId(), idx)
        y = ComponentEntity(x)
        self.assertEqual(y.getId(), idx)
        del(x, y)
        
        # Test own methods
        
        # Test removing a component
        x = ComponentEntity()
        self.assertEqual(x.componentCount(), 0)
        self.assertFalse(x.removeComponent('aaa'))
        self.assertFalse(x.removeComponent('aaa', True))
        self.assertFalse(x.removeComponent('aaa', False))
        #TODO self.assertFalse(x.removeComponent('aaa', 'hello'))
        self.assertEqual(x.componentCount(), 0)
        from libcellml.component import Component
        y = Component()
        self.assertFalse(x.removeComponent(y))
        self.assertFalse(x.removeComponent(y, True))
        self.assertFalse(x.removeComponent(y, False))
        #TODO self.assertFalse(x.removeComponent(y, 'hi'))
        self.assertEqual(x.componentCount(), 0)
        


if __name__ == '__main__':
    unittest.main()
