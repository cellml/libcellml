#
# Tests the Error class bindings
#
import unittest


class LoggerTestCase(unittest.TestCase):

    def test_create_destroy(self):
        from libcellml import Logger

        # Test create/copy/destroy
        x = Logger()
        del(x)
        y = Logger()
        z = Logger(y)
        del(y, z)

    def test_add_error(self):
        from libcellml import Logger, Error

        # void addError(const ErrorPtr error)
        x = Logger()
        x.addError(Error())

    def test_error_count(self):
        from libcellml import Logger, Error

        # size_t errorCount()
        x = Logger()
        self.assertEqual(x.errorCount(), 0)
        x.addError(Error())
        self.assertEqual(x.errorCount(), 1)
        x.addError(Error())
        self.assertEqual(x.errorCount(), 2)

    def test_error(self):
        from libcellml import Logger, Error

        # ErrorPtr error(size_t index)
        x = Logger()
        self.assertIsNone(x.error(0))
        self.assertIsNone(x.error(1))
        self.assertIsNone(x.error(-1))
        e = Error()
        e.setKind(Error.Kind.MODEL)
        x.addError(e)
        self.assertIsNotNone(x.error(0))
        self.assertIsNone(x.error(1))
        self.assertEqual(x.error(0).kind(), Error.Kind.MODEL)

    def test_clear_errors(self):
        from libcellml import Logger, Error

        # void clearErrors()
        x = Logger()
        self.assertEqual(x.errorCount(), 0)
        x.addError(Error())
        x.addError(Error())
        self.assertEqual(x.errorCount(), 2)
        x.clearErrors()
        self.assertEqual(x.errorCount(), 0)


if __name__ == '__main__':
    unittest.main()
