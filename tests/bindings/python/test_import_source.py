#
# Tests the ImportSource class bindings.
#
import sys
import unittest

class ImportSourceTestCase(unittest.TestCase):

    def test_import_source(self):
        import libcellml
        from libcellml import ImportSource

        # Test create/copy/destroy
        x = ImportSource()
        del(x)
        y = ImportSource()
        z = ImportSource(y)
        del(y, z)
        
        # Test inheritance
        x = ImportSource()
        self.assertIsInstance(x, libcellml.Entity)

        # Test own methods
        
        # void setSource(const std::string &reference)
        x = ImportSource()
        x.setSource('')
        x.setSource('hello')
        x.setSource('')
        del(x)
        
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
