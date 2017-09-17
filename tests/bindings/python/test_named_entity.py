#
# Tests the NamedEntity class
#
import sys
import unittest


class NamedEntityTestCase(unittest.TestCase):

    def test_named_entity(self):
        from libcellml.namedentity import NamedEntity
        
        # Test create/copy/destroy
        x = NamedEntity()
        del(x)
        y = NamedEntity()
        z = NamedEntity(y)
        del(y,z)

        # Test inheritance
        x = NamedEntity()
        from libcellml.entity import Entity
        self.assertIsInstance(x, Entity)

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


def suite():
    #import ImportTestCase
    tests = unittest.TestSuite()
    tests.addTests(unittest.TestLoader().loadTestsFromTestCase(NamedEntityTestCase))
    return tests


if __name__ == '__main__':
    success = unittest.TextTestRunner().run(suite()).wasSuccessful()
    sys.exit(not success)
