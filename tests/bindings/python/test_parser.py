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
        self.assertIsInstance(x, libcellml.logger.Logger)

        # Test access to inherited methods
        self.assertIsNone(x.error(0))
        self.assertIsNone(x.error(-1))
        self.assertEqual(x.errorCount(), 0)
        x.addError(libcellml.Error())
        self.assertEqual(x.errorCount(), 1)

    def test_parse_model(self):
        import libcellml
        from libcellml import Parser

        # ModelPtr parseModel(const std::string &input)
        p = Parser()
        self.assertIsInstance(p.parseModel('rubbish'), libcellml.Model)


if __name__ == '__main__':
    unittest.main()
