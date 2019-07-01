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

        # void addIssue(const IssuePtr error)
        x = Logger()
        x.addIssue(Issue())

    def test_error_count(self):
        from libcellml import Logger, Issue

        # size_t issueCount()
        x = Logger()
        self.assertEqual(x.issueCount(), 0)
        x.addIssue(Issue())
        self.assertEqual(x.issueCount(), 1)
        x.addIssue(Issue())
        self.assertEqual(x.issueCount(), 2)

    def test_error(self):
        from libcellml import Logger, Issue

        # IssuePtr error(size_t index)
        x = Logger()
        self.assertIsNone(x.issue(0))
        self.assertIsNone(x.issue(1))
        # self.assertIsNone(x.issue(-1))  # TODO Removed as negatives are not allowed as indices ... do they need to be ints intead of size_t?
        e = Issue()
        e.setCause(Issue.Cause.MODEL)
        x.addIssue(e)
        self.assertIsNotNone(x.issue(0))
        self.assertIsNone(x.issue(1))
        self.assertEqual(x.issue(0).cause(), Issue.Cause.MODEL)

    def test_clear_errors(self):
        from libcellml import Logger, Issue

        # void clearIssues()
        x = Logger()
        self.assertEqual(x.issueCount(), 0)
        x.addIssue(Issue())
        x.addIssue(Issue())
        self.assertEqual(x.issueCount(), 2)
        x.clearIssues()
        self.assertEqual(x.issueCount(), 0)


if __name__ == '__main__':
    unittest.main()
