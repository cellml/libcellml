#
# Tests the ImportSource class bindings.
#
import unittest


class ImportSourceTestCase(unittest.TestCase):

    def test_import_source(self):
        from libcellml import ImportSource

        # Test create/copy/destroy
        x = ImportSource()
        y = ImportSource()
        z = ImportSource(y)
        del(x, y, z)

    def test_inheritance(self):
        import libcellml
        from libcellml import ImportSource

        x = ImportSource()
        self.assertIsInstance(x, libcellml.Entity)

    def test_set_source(self):
        from libcellml import ImportSource

        # void setSource(const std::string &reference)
        x = ImportSource()
        x.setSource('')
        x.setSource('hello')
        x.setSource('')

    def test_get_source(self):
        from libcellml import ImportSource

        # std::string getSource()
        source = 'cheers'
        x = ImportSource()
        self.assertEqual(x.getSource(), '')
        x.setSource(source)
        self.assertEqual(x.getSource(), source)
        x.setSource('')
        self.assertEqual(x.getSource(), '')


if __name__ == '__main__':
    unittest.main()
