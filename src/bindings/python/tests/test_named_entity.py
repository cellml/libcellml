#
# Tests the NamedEntity class
#
import unittest
class TestNamedEntity(unittest.TestCase):

    def test_named_entity(self):
    
        from libcellml.namedentity import NamedEntity
        
        # Test create/copy/destroy
        x = NamedEntity()
        del(x)
        y = NamedEntity()
        z = NamedEntity(y)
        del(y,z)
        
        # Test access to inherited methods
        x = NamedEntity()
        idx = 'test'
        self.assertEqual(x.getId(), '')
        x.setId(idx)
        self.assertEqual(x.getId(), idx)
        
        # Test name
        name = 'testo'
        x = NamedEntity()
        self.assertEqual(x.getName(), '')
        x.setName(name)
        self.assertEqual(x.getName(), name)
        y = NamedEntity(x)
        self.assertEqual(y.getName(), name)
        
