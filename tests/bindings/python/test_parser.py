#
# Tests the Parser class bindings
#
import unittest


class ParserTestCase(unittest.TestCase):

    def test_create_destroy(self):
        from libcellml import Parser

        x = Parser()
        del(x)
        y = Parser()
        z = Parser(y)
        del(y, z)

    def test_inheritance(self):
        import libcellml
        from libcellml import Parser

        x = Parser()
        self.assertIsInstance(x, libcellml.Logger)

        # Test access to inherited methods
        self.assertIsNone(x.issue(0))
        # self.assertIsNone(x.issue(-1))  # TODO Removed as negatives are not allowed as indices ... do they need to be ints intead of size_t?
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
