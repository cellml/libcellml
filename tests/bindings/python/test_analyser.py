#
# Tests the Analyser class bindings
#
import unittest


class AnalyserTestCase(unittest.TestCase):

    def test_create_destroy(self):
        from libcellml import Analyser

        x = Analyser()
        del x

    def test_inheritance(self):
        import libcellml
        from libcellml import Analyser

        x = Analyser()
        self.assertIsInstance(x, libcellml.logger.Logger)

        # Test access to inherited methods.
        self.assertIsNone(x.issue(0))
        self.assertIsNone(x.issue(-1))
        self.assertEqual(x.issueCount(), 0)
        x.addIssue(libcellml.Issue())
        self.assertEqual(x.issueCount(), 1)

    def test_process_model(self):
        from libcellml import Analyser
        from libcellml import AnalyserModel
        from libcellml import Model

        m = Model('my_model')
        a = Analyser()

        a.processModel(m)

        self.assertEqual(0, a.errorCount())
        self.assertEqual(AnalyserModel.Type.UNKNOWN, a.model().type())


if __name__ == '__main__':
    unittest.main()
