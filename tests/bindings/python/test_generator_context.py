#
# Tests the GeneratorContext class bindings
#
import unittest


class GeneratorContextTestCase(unittest.TestCase):

    def test_tracked_untracked_variables(self):
        from libcellml import Analyser
        from libcellml import GeneratorContext
        from libcellml import Parser
        from test_resources import file_contents

        p = Parser()
        m = p.parseModel(file_contents('generator/hodgkin_huxley_squid_axon_model_1952/model.cellml'))
        v = m.component("membrane").variable("Cm")
        a = Analyser()

        a.analyseModel(m)

        am = a.analyserModel()
        av = am.analyserVariable(v)
        gc = GeneratorContext()

        gc.untrackVariable(av)

        self.assertFalse(gc.isTrackedVariable(av))
        self.assertTrue(gc.isUntrackedVariable(av))

        gc.trackVariable(av)

        self.assertTrue(gc.isTrackedVariable(av))
        self.assertFalse(gc.isUntrackedVariable(av))

        gc.untrackAllConstants(am)

        self.assertEqual(0, gc.trackedConstantCount(am))
        self.assertEqual(5, gc.untrackedConstantCount(am))

        gc.trackAllConstants(am)

        self.assertEqual(5, gc.trackedConstantCount(am))
        self.assertEqual(0, gc.untrackedConstantCount(am))

        gc.untrackAllComputedConstants(am)

        self.assertEqual(0, gc.trackedComputedConstantCount(am))
        self.assertEqual(3, gc.untrackedComputedConstantCount(am))

        gc.trackAllComputedConstants(am)

        self.assertEqual(3, gc.trackedComputedConstantCount(am))
        self.assertEqual(0, gc.untrackedComputedConstantCount(am))

        gc.untrackAllAlgebraicVariables(am)

        self.assertEqual(0, gc.trackedAlgebraicVariableCount(am))
        self.assertEqual(10, gc.untrackedAlgebraicVariableCount(am))

        gc.trackAllAlgebraicVariables(am)

        self.assertEqual(10, gc.trackedAlgebraicVariableCount(am))
        self.assertEqual(0, gc.untrackedAlgebraicVariableCount(am))

        gc.untrackAllVariables(am)

        self.assertEqual(0, gc.trackedVariableCount(am))
        self.assertEqual(18, gc.untrackedVariableCount(am))

        gc.trackAllVariables(am)

        self.assertEqual(18, gc.trackedVariableCount(am))
        self.assertEqual(0, gc.untrackedVariableCount(am))


if __name__ == '__main__':
    unittest.main()
