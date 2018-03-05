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
        del(y, z)
        
        # Test methods
        
        # void addError(const ErrorPtr error)
        from libcellml import Error
        x = Logger()
        x.addError(Error())
        del(x)

        # size_t errorCount()
        x = Logger()
        self.assertEqual(x.errorCount(), 0)
        x.addError(Error())
        self.assertEqual(x.errorCount(), 1)
        x.addError(Error())
        self.assertEqual(x.errorCount(), 2)
        del(x)
        
        # ErrorPtr getError(size_t index)
        x = Logger()
        self.assertIsNone(x.getError(0))
        self.assertIsNone(x.getError(1))
        self.assertIsNone(x.getError(-1))
        e = Error()
        e.setKind(Error.Kind.MODEL)
        x.addError(e)
        self.assertIsNotNone(x.getError(0))
        self.assertIsNone(x.getError(1))
        self.assertEqual(x.getError(0).getKind(), Error.Kind.MODEL)
        del(x, e)
        
        # void clearErrors()
        x = Logger()
        self.assertEqual(x.errorCount(), 0)
        x.addError(Error())
        x.addError(Error())
        self.assertEqual(x.errorCount(), 2)
        x.clearErrors()
        self.assertEqual(x.errorCount(), 0)
        del(x)

if __name__ == '__main__':
    unittest.main()
