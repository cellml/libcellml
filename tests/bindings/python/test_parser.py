#
# Tests the Parser class bindings
#
import unittest


class ParserTestCase(unittest.TestCase):

    def test_create_destroy(self):
        from libcellml import Parser

        x = Parser()
        del x

    def test_inheritance(self):
        import libcellml
        from libcellml import Parser

        x = Parser()
        self.assertIsInstance(x, libcellml.logger.Logger)

        # Test access to inherited methods
        self.assertIsNone(x.issue(0))
        self.assertIsNone(x.issue(-1))
        self.assertEqual(x.issueCount(), 0)
        x.addIssue(libcellml.Issue())
        self.assertEqual(x.issueCount(), 1)

    def test_parse_model(self):
        import libcellml
        from libcellml import Parser

        # ModelPtr parseModel(const std::string &input)
        p = Parser()
        self.assertIsInstance(p.parseModel('rubbish'), libcellml.Model)


if __name__ == '__main__':
    unittest.main()
