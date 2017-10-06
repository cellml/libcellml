#
# Tests the entity class bindings
#
import sys
import unittest

class EntityTestCase(unittest.TestCase):

    def test_entity(self):
        from libcellml import Entity
        
        # Test create/copy/destroy
        x = Entity()
        del(x)
        y = Entity()
        z = Entity(y)
        del(y, z)
        
        # Test own methods

        # std::string getId()
        x = Entity()
        self.assertEqual(x.getId(), '')

        # void setId(const std::string &id)        
        idx = 'test'
        x.setId(idx)
        self.assertEqual(x.getId(), idx)
        
        # copy constructor
        y = Entity(x)
        self.assertEqual(y.getId(), idx)
        del(x, y, idx)
        
        # void* getParent
        #TODO: This method might be moved out of entity!
        #TODO: If not, this needs a workaround!
        x = Entity()
        self.assertIsNone(x.getParent())
        del(x)
        
        # void setParent(Model *parent)
        from libcellml import Model
        m = Model()
        x = Entity()
        x.setParent(m)
        self.assertIsNotNone(x.getParent())
        #TODO: Check equivalence
        del(x, m)
        
        # void setParent(Component *parent)
        from libcellml import Component
        c = Component()
        x = Entity()
        x.setParent(c)
        self.assertIsNotNone(x.getParent())
        #TODO: Check equivalence
        del(x, c)
        
        # void clearParent()
        x = Entity()
        self.assertIsNone(x.getParent())
        x.setParent(Model())
        self.assertIsNotNone(x.getParent())
        x.clearParent()
        self.assertIsNone(x.getParent())
        x.setParent(Component())
        self.assertIsNotNone(x.getParent())
        x.clearParent()
        self.assertIsNone(x.getParent())
        del(x)

        # bool hasParent(Component* c)
        x = Entity()
        c = Component()
        self.assertFalse(x.hasParent(c))
        x.setParent(c)
        self.assertTrue(x.hasParent(c))
        x.clearParent()
        self.assertFalse(x.hasParent(c))
        d = Component()
        d.setParent(c)
        x.setParent(d)
        self.assertTrue(x.hasParent(d))
        self.assertTrue(x.hasParent(c))

if __name__ == '__main__':
    unittest.main()
