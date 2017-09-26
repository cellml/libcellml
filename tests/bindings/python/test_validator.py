#
# Tests the Validator class bindings
#
import sys
import unittest

class ValidatorTestCase(unittest.TestCase):

    def test_validator(self):
        import libcellml
        from libcellml import Validator
        
        # Test create/copy/destroy
        x = Validator()
        del(x)
        y = Validator()
        z = Validator(y)
        del(y,z)
          
        # Test methods
        
        # void validateModel(const ModelPtr &model)
        #TODO
        
if __name__ == '__main__':
    unittest.main()
