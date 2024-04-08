#
# Tests the Interpreter class bindings
#
import unittest


class InterpreterTestCase(unittest.TestCase):

    def test_create_destroy(self):
        from libcellml import Interpreter

        x = Interpreter()
        del x

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

        self.assertEqual(4, len(i.states()))
        self.assertEqual(4, len(i.rates()))
        self.assertEqual(18, len(i.variables()))

        i.initialiseVariables()
        i.computeComputedConstants()
        i.computeRates()
        i.computeVariables()


if __name__ == '__main__':
    unittest.main()
