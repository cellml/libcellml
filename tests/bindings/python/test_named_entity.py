#
# Tests the NamedEntity class bindings
#
import sys
import unittest

class NamedEntityTestCase(unittest.TestCase):

    def test_named_entity(self):
        import libcellml
        from libcellml import NamedEntity
        
        # Test create/copy/destroy
        x = NamedEntity()
        del(x)
        y = NamedEntity()
        z = NamedEntity(y)
        del(y,z)

        # Test inheritance
        x = NamedEntity()
        self.assertIsInstance(x, libcellml.Entity)

        # Test access to inherited methods
        x = NamedEntity()
        idx = 'test'
        self.assertEqual(x.getId(), '')
        x.setId(idx)
        self.assertEqual(x.getId(), idx)
        
        # Test own methods
        
        # void setName(const std::string &name)
        name = 'testo'
        x = NamedEntity()
        x.setName(name)
        x.setName('')
        del(x, name)
        
        # std::string getName()
        name = 'testo'
        x = NamedEntity()
        self.assertEqual(x.getName(), '')
        x.setName(name)
        self.assertEqual(x.getName(), name)
        x.setName('')
        self.assertEqual(x.getName(), '')
        del(x, name)

if __name__ == '__main__':
    unittest.main()
