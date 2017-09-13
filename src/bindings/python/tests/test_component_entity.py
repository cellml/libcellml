#
# Tests the ComponentEntity class
#
import unittest
class TestComponentEntity(unittest.TestCase):

    def test_component_entity(self):
    
        from libcellml.componententity import ComponentEntity
        
        # Test create/copy/destroy
        x = ComponentEntity()
        del(x)
        y = ComponentEntity()
        z = ComponentEntity(y)
        del(y,z)
        
        # Test entity basics
        x = ComponentEntity()
        idx = 'test'
        self.assertEqual(x.getId(), '')
        x.setId(idx)
        self.assertEqual(x.getId(), idx)
        y = ComponentEntity(x)
        self.assertEqual(y.getId(), idx)
        del(x, y)
        
        # Test own methods
        #TODO Components etc.
    

        
        
        
