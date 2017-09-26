#
# Tests the Parser class bindings
#
import sys
import unittest

class ParserTestCase(unittest.TestCase):

    def test_parser(self):
        import libcellml
        from libcellml import Parser
        
        # Test create/copy/destroy
        x = Parser(libcellml.Format.XML)
        del(x)
        y = Parser(libcellml.Format.XML)
        z = Parser(y)
        del(y, z)
        
        # Test inheritance
        x = Parser(libcellml.Format.XML)
        self.assertIsInstance(x, libcellml.Logger)

        # Test access to inherited methods
        idx = 'test'
        self.assertIsNone(x.getError(0))
        self.assertIsNone(x.getError(-1))
        self.assertEqual(x.errorCount(), 0)
        x.addError(libcellml.Error())
        self.assertEqual(x.errorCount(), 1)
        del(x, idx)
        
        # Test own methods
        
        # ModelPtr parseModel(const std::string &input)
        #TODO
        
if __name__ == '__main__':
    unittest.main()
