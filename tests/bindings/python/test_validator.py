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
        del(y, z)
        
        # Test inheritance
        x = Validator()
        self.assertIsInstance(x, libcellml.Logger)

        # Test access to inherited methods
        idx = 'test'
        self.assertIsNone(x.getError(0))
        self.assertEqual(x.errorCount(), 0)
        x.addError(libcellml.Error())
        self.assertEqual(x.errorCount(), 1)
        del(x, idx)
        
        # Test own methods
        
        # void validateModel(const ModelPtr &model)
        #TODO
        
if __name__ == '__main__':
    unittest.main()
