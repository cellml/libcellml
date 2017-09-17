#
# Tests the entity class
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
        
        #TODO Models and components        


if __name__ == '__main__':
    unittest.main()
