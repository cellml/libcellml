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

        # void setUrl(const std::string &reference)
        x = ImportSource()
        x.setUrl('')
        x.setUrl('hello')
        x.setUrl('')

    def test_get_source(self):
        from libcellml import ImportSource

        # std::string getSource()
        source = 'cheers'
        x = ImportSource()
        self.assertEqual(x.getUrl(), '')
        x.setUrl(source)
        self.assertEqual(x.getUrl(), source)
        x.setUrl('')
        self.assertEqual(x.getUrl(), '')


if __name__ == '__main__':
    unittest.main()
