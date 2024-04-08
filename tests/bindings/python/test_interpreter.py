#
# Tests the Interpreter class bindings
#
import unittest


class InterpreterTestCase(unittest.TestCase):

    def test_create_destroy(self):
        from libcellml import Interpreter

        x = Interpreter()
        del x

    def test_algebraic_eqn_computed_var_on_rhs(self):
        from libcellml import Analyser
        from libcellml import AnalyserModel
        from libcellml import Interpreter
        from libcellml import Parser
        from test_resources import file_contents

        p = Parser()
        m = p.parseModel(file_contents('generator/algebraic_eqn_computed_var_on_rhs/model.cellml'))

        a = Analyser()
        a.analyseModel(m)

        am = a.model()

        self.assertEqual(AnalyserModel.Type.ALGEBRAIC, am.type())

        i = Interpreter()

        self.assertIsNone(i.model())

        i.setModel(am)

        self.assertIsNotNone(i.model())

        self.assertEqual(0.0, i.voi())

        self.assertEqual(0, i.stateCount())
        self.assertIsNone(i.states())

        self.assertEqual(0, i.rateCount())
        self.assertIsNone(i.rates())

        self.assertEqual(0, i.variableCount())
        self.assertIsNone(i.variables())

        i.initialiseVariables()
        i.computeComputedConstants()
        i.computeRates()
        i.computeVariables()


if __name__ == '__main__':
    unittest.main()
