#
# Tests the NamedEntity class bindings
#
import unittest


class NamedEntityTestCase(unittest.TestCase):

    def test_create_destroy(self):
        from libcellml import NamedEntity

        # Test create/copy/destroy
        x = NamedEntity()
        del(x)
        y = NamedEntity()
        z = NamedEntity(y)
        del(y, z)

    def test_inheritance(self):
        import libcellml
        from libcellml import NamedEntity

        x = NamedEntity()
        self.assertIsInstance(x, libcellml.Entity)

        # Test access to inherited methods
        x = NamedEntity()
        idx = 'test'
        self.assertEqual(x.id(), '')
        x.setId(idx)
        self.assertEqual(x.id(), idx)

    def test_set_name(self):
        from libcellml import NamedEntity

        # void setName(const std::string &name)
        name = 'testo'
        x = NamedEntity()
        x.setName(name)
        x.setName('')

    def test_name(self):
        from libcellml import NamedEntity

        # std::string name()
        name = 'testo'
        x = NamedEntity()
        self.assertEqual(x.name(), '')
        x.setName(name)
        self.assertEqual(x.name(), name)
        x.setName('')
        self.assertEqual(x.name(), '')


if __name__ == '__main__':
    unittest.main()
