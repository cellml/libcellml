#
# Tests the Error class bindings
#
import sys
import unittest

class LoggerTestCase(unittest.TestCase):

    def test_logger(self):
        import libcellml
        from libcellml import Logger
        
        # Test create/copy/destroy
        x = Logger()
        del(x)
        y = Logger()
        z = Logger(y)
        del(y,z)
        
        # Test methods
        #TODO
        
        # void clearErrors()

        # void addError(const ErrorPtr error)

        # size_t errorCount()

        # ErrorPtr getError(size_t index)

if __name__ == '__main__':
    unittest.main()
