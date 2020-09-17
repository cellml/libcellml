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

    def test_analyse_model(self):
        from libcellml import Analyser
        from libcellml import AnalyserModel
        from libcellml import Model

        # Analyse an empty model and make sure that we get no errors and an
        # UNKNOWN type for the analyser model.

        m = Model('my_model')
        a = Analyser()

        a.analyseModel(m)

        self.assertEqual(0, a.errorCount())
        self.assertEqual(AnalyserModel.Type.UNKNOWN, a.model().type())

    def test_coverage(self):
        from libcellml import Analyser
        from libcellml import AnalyserModel
        from libcellml import AnalyserVariable
        from libcellml import Parser
        from test_resources import file_contents

        p = Parser()
        m = p.parseModel(file_contents('generator/garny_kohl_hunter_boyett_noble_rabbit_san_model_2003/model.cellml'))

        a = Analyser()
        a.analyseModel(m)

        am = a.model()

        self.assertEqual(AnalyserModel.Type.ODE, am.type())
        self.assertEqual(185, am.variableCount())

        av = am.variable(1)

        self.assertEqual(AnalyserVariable.Type.CONSTANT, av.type())
        self.assertEqual("g_Ca_L_Centre_0DCapable", av.variable().name())

        voi = am.voi()

        self.assertEqual("time", voi.variable().name())

        self.assertEqual(15, am.stateCount())
        self.assertEqual("P_af", am.state(9).variable().name())
        self.assertEqual("V", am.state(14).initialisingVariable().name())


if __name__ == '__main__':
    unittest.main()
