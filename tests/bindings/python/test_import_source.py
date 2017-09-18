#
# Tests the Import class. #TODO Will be renamed
#
import sys
import unittest

class ImportTestCase(unittest.TestCase):

    def test_import(self):
        from libcellml.importsource import Import

        # Test create/copy/destroy
        x = Import()
        del(x)
        y = Import()
        z = Import(y)
        del(y,z)
        
        # Test inheritance
        x = Import()
        from libcellml.entity import Entity
        self.assertIsInstance(x, Entity)

        # Test methods
        source = 'the-source'
        x = Import()
        self.assertEqual(x.getSource(), '') #TODO Should be None?
        x.setSource(source)
        self.assertEqual(x.getSource(), source)
        x.setSource('') #TODO Should be None?
        self.assertEqual(x.getSource(), '')

if __name__ == '__main__':
    unittest.main()
