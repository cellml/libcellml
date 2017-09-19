#
# Tests the entity class bindings
#
import sys
import unittest

class EntityTestCase(unittest.TestCase):

    def test_entity(self):
        from libcellml.entity import Entity
        
        # Test create/copy/destroy
        x = Entity()
        del(x)
        y = Entity()
        z = Entity(y)
        del(y,z)
        
        # Test id
        x = Entity()
        idx = 'test'
        self.assertEqual(x.getId(), '')
        x.setId(idx)
        self.assertEqual(x.getId(), idx)
        y = Entity(x)
        self.assertEqual(y.getId(), idx)
        del(x, y)
        
        # Test parent
        x = Entity()
        self.assertIsNone(x.getParent())
        x.clearParent()
        from libcellml.model import Model
        from libcellml.component import Component
        m = Model()
        x.setParent(m)
        #TODO: This method might be moved out of entity!
        #TODO: If not, this needs a workaround!
        #self.assertIs(x.getParent(), m)
        
        name = 'p'
        c = Component()
        c.setName(name)        
        x.setParent(c)
        #TODO See above
        #self.assertEqual(x.getParent().getName(), name)
        self.assertTrue(x.hasParent(c))
        x.setParent(None)
        #TODO See above
        #self.assertIsNone(x.getParent())
        c2 = Component()
        c2.setParent(c)
        x.setParent(c2)
        self.assertTrue(x.hasParent(c))
        

if __name__ == '__main__':
    unittest.main()
