#
# Tests the Importer class bindings
#
import unittest


class ValidatorTestCase(unittest.TestCase):

    def test_create_destroy(self):
        from libcellml import Importer

        x = Importer()
        del(x)

    def test_inheritance(self):
        import libcellml
        from libcellml import Importer

        # Test inheritance
        x = Importer()
        self.assertIsInstance(x, libcellml.logger.Logger)

        # Test access to inherited methods
        self.assertIsNone(x.issue(0))
        self.assertIsNone(x.issue(-1))
        self.assertEqual(x.issueCount(), 0)
        x.addIssue(libcellml.Issue())
        self.assertEqual(x.issueCount(), 1)

    def test_resolve_imports(self):
        from libcellml import Model
        from libcellml import Importer

        m = Model()
        i = Importer()
        i.resolveImports(m, 'file.txt')


if __name__ == '__main__':
    unittest.main()
