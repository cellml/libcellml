#
# Tests the Issue class bindings
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
        from libcellml import Logger, Issue

        # void addError(const IssuePtr error)
        x = Logger()
        x.addError(Issue())

    def test_error_count(self):
        from libcellml import Logger, Issue

        # size_t errorCount()
        x = Logger()
        self.assertEqual(x.errorCount(), 0)
        x.addError(Issue())
        self.assertEqual(x.errorCount(), 1)
        x.addError(Issue())
        self.assertEqual(x.errorCount(), 2)

    def test_error(self):
        from libcellml import Logger, Issue

        # IssuePtr error(size_t index)
        x = Logger()
        self.assertIsNone(x.error(0))
        self.assertIsNone(x.error(1))
        self.assertIsNone(x.error(-1))
        e = Issue()
        e.setKind(Issue.Kind.MODEL)
        x.addError(e)
        self.assertIsNotNone(x.error(0))
        self.assertIsNone(x.error(1))
        self.assertEqual(x.error(0).kind(), Issue.Kind.MODEL)

    def test_clear_errors(self):
        from libcellml import Logger, Issue

        # void clearErrors()
        x = Logger()
        self.assertEqual(x.errorCount(), 0)
        x.addError(Issue())
        x.addError(Issue())
        self.assertEqual(x.errorCount(), 2)
        x.clearErrors()
        self.assertEqual(x.errorCount(), 0)


if __name__ == '__main__':
    unittest.main()
