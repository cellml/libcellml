#
# Tests the Variable class bindings
#
import sys
import unittest

class VariableTestCase(unittest.TestCase):

    def test_variable(self):
        from libcellml.variable import Variable
        
        # Test create/copy/destroy
        x = Variable()
        del(x)
        y = Variable()
        z = Variable(y)
        del(y,z)
        
        # Test inheritance
        x = Variable()
        from libcellml.namedentity import NamedEntity
        self.assertIsInstance(x, NamedEntity)
        from libcellml.entity import Entity
        self.assertIsInstance(x, Entity)
        
        # Test access to inherited methods
        x = Variable()
        idx = 'test'
        self.assertEqual(x.getId(), '')
        x.setId(idx)
        self.assertEqual(x.getId(), idx)
        y = Variable(x)
        self.assertEqual(y.getId(), idx)
        del(x, y)
        
        # Test own methods
        #TODO
        

        
if __name__ == '__main__':
    unittest.main()
