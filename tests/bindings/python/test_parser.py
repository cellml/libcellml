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
        x = Parser()
        del(x)
        y = Parser()
        z = Parser(y)
        del(y,z)
          
        # Test methods
        
        # ModelPtr parseModel(const std::string &input)
        #TODO
        
if __name__ == '__main__':
    unittest.main()
