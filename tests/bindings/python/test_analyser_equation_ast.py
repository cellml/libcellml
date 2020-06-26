#
# Tests the AnalyserEquationAst class bindings
#
import unittest


class AnalyserEquationAstTestCase(unittest.TestCase):

    def test_create_destroy(self):
        from libcellml import AnalyserEquationAst

        x = AnalyserEquationAst()
        del x


if __name__ == '__main__':
    unittest.main()
