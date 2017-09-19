#
# Tests the Import class bindings. #TODO Will be renamed
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

        # Test own methods
        
        # void setSource(const std::string &reference)
        x = Import()
        x.setSource('')
        x.setSource('hello')
        x.setSource('')
        del(x)
        
        # std::string getSource()
        source = 'cheers'
        x = Import()
        self.assertEqual(x.getSource(), '')
        x.setSource(source)
        self.assertEqual(x.getSource(), source)
        x.setSource('')        
        self.assertEqual(x.getSource(), '')
        
if __name__ == '__main__':
    unittest.main()
