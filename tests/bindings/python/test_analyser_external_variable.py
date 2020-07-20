#
# Tests the AnalyserExternalVariable class bindings
#
import unittest


class AnalyserExternalVariableTestCase(unittest.TestCase):

    def test_create_destroy(self):
        from libcellml import Variable
        from libcellml import AnalyserExternalVariable

        v = Variable('test')
        x = AnalyserExternalVariable(v)

        self.assertEqual(x.variable().name(), v.name())

        del x
        del v


if __name__ == '__main__':
    unittest.main()
