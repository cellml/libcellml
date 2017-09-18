#
# Tests the Model class
#
import sys
import unittest

class ModelTestCase(unittest.TestCase):

    def test_model(self):
        from libcellml.model import Model
        
        # Test create/copy/destroy
        x = Model()
        del(x)
        y = Model()
        z = Model(y)
        del(y,z)
        
        # Test inheritance
        x = Model()
        from libcellml.componententity import ComponentEntity
        self.assertIsInstance(x, ComponentEntity)
        from libcellml.importedentity import ImportedEntity
        self.assertIsInstance(x, ImportedEntity)
        from libcellml.namedentity import NamedEntity
        self.assertIsInstance(x, NamedEntity)
        from libcellml.entity import Entity
        self.assertIsInstance(x, Entity)
        
        # Test access to inherited methods
        x = Model()
        idx = 'test'
        self.assertEqual(x.getId(), '')
        x.setId(idx)
        self.assertEqual(x.getId(), idx)
        y = Model(x)
        self.assertEqual(y.getId(), idx)
        del(x, y)
        
        # Test own methods
        #TODO Models, components etc.
        

if __name__ == '__main__':
    unittest.main()
