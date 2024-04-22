#
# Tests the Interpreter class bindings
#
import math
import unittest


class InterpreterTestCase(unittest.TestCase):

    def test_create_destroy(self):
        from libcellml import Interpreter

        x = Interpreter()
        del x

    def assert_array_equal(self, expected_values, values):
        self.assertEqual(len(expected_values), len(values))

        for i in range(len(expected_values)):
            if math.isnan(expected_values[i]):
                self.assertTrue(math.isnan(values[i]))
            else:
                self.assertAlmostEqual(expected_values[i], values[i])

    def test_hodgkin_huxley_squid_axon_model_1952(self):
        from libcellml import Analyser
        from libcellml import AnalyserModel
        from libcellml import Interpreter
        from libcellml import Parser
        from test_resources import file_contents

        p = Parser()
        m = p.parseModel(file_contents('generator/hodgkin_huxley_squid_axon_model_1952/model.cellml'))
        a = Analyser()

        a.analyseModel(m)

        am = a.model()

        self.assertEqual(AnalyserModel.Type.ODE, am.type())

        i = Interpreter()

        self.assertIsNone(i.model())

        i.setModel(am)

        self.assertIsNotNone(i.model())

        self.assertEqual(0.0, i.voi())

        nan_x_4 = 4 * [math.nan]
        nan_x_18 = 18 * [math.nan]

        self.assert_array_equal(nan_x_4, i.states())
        self.assert_array_equal(nan_x_4, i.rates())
        self.assert_array_equal(nan_x_18, i.variables())

        i.initialiseAstVariables()
        i.computeAstComputedConstants()
        i.computeAstRates()
        i.computeAstVariables()

        self.assert_array_equal([0.0, 0.6, 0.05, 0.325], i.states())
        self.assert_array_equal([0.60076875, -0.0004555239065400646, 0.012385538355398518, -0.0013415722863204596], i.rates())
        self.assert_array_equal([0.0, 3.1839, -4.81966875, 1.035, 1.0, 0.0, -10.613, 0.3, -115.0, 120.0, 0.22356372458463003, 4.0, 0.07, 0.04742587317756678, 12.0, 36.0, 0.05819767068693265, 0.125], i.variables())


if __name__ == '__main__':
    unittest.main()
