#
# Tests the Generator class bindings
#
import unittest


class GeneratorTestCase(unittest.TestCase):

    def test_create_destroy(self):
        from libcellml import Generator

        x = Generator()
        del x

    def test_algebraic_eqn_computed_var_on_rhs(self):
        from libcellml import Analyser
        from libcellml import AnalyserModel
        from libcellml import Generator
        from libcellml.generator import Generator_equationCode
        from libcellml import GeneratorProfile
        from libcellml import Parser
        from test_resources import file_contents

        p = Parser()
        m = p.parseModel(file_contents('generator/algebraic_eqn_computed_var_on_rhs/model.cellml'))

        a = Analyser()
        a.analyseModel(m)

        am = a.model()

        self.assertEqual(AnalyserModel.Type.ALGEBRAIC, am.type())

        g = Generator()

        self.assertEqual(file_contents("generator/algebraic_eqn_computed_var_on_rhs/model.h"), g.interfaceCode(am))
        self.assertEqual(file_contents("generator/algebraic_eqn_computed_var_on_rhs/model.c"), g.implementationCode(am))

        self.assertEqual(GeneratorProfile.Profile.C, g.profile().profile())

        profile = GeneratorProfile(GeneratorProfile.Profile.PYTHON)
        g.setProfile(profile)

        self.assertEqual("", g.interfaceCode(am))
        self.assertEqual(file_contents("generator/algebraic_eqn_computed_var_on_rhs/model.py"), g.implementationCode(am))

        self.assertEqual(GeneratorProfile.Profile.PYTHON, g.profile().profile())

        self.assertEqual("x = a", Generator.equationCode(am.analyserEquation(0).ast()))
        self.assertEqual("x = a", Generator_equationCode(am.analyserEquation(0).ast()))

    def test_tracked_untracked_variables(self):
        from libcellml import Analyser
        from libcellml import AnalyserExternalVariable
        from libcellml import Generator
        from libcellml import Parser
        from test_resources import file_contents

        p = Parser()
        m = p.parseModel(file_contents('generator/hodgkin_huxley_squid_axon_model_1952/model.cellml'))
        v = m.component("membrane").variable("Cm")
        a = Analyser()

        a.analyseModel(m)

        am = a.model()
        av = am.analyserVariable(v)
        g = Generator()

        g.untrackVariable(av)

        self.assertFalse(g.isTrackedVariable(av))
        self.assertTrue(g.isUntrackedVariable(av))

        g.trackVariable(av)

        self.assertTrue(g.isTrackedVariable(av))
        self.assertFalse(g.isUntrackedVariable(av))

        g.untrackAllConstants(am)

        self.assertEqual(0, g.trackedConstantCount(am))
        self.assertEqual(5, g.untrackedConstantCount(am))

        g.trackAllConstants(am)

        self.assertEqual(5, g.trackedConstantCount(am))
        self.assertEqual(0, g.untrackedConstantCount(am))

        g.untrackAllComputedConstants(am)

        self.assertEqual(0, g.trackedComputedConstantCount(am))
        self.assertEqual(3, g.untrackedComputedConstantCount(am))

        g.trackAllComputedConstants(am)

        self.assertEqual(3, g.trackedComputedConstantCount(am))
        self.assertEqual(0, g.untrackedComputedConstantCount(am))

        g.untrackAllAlgebraic(am)

        self.assertEqual(0, g.trackedAlgebraicCount(am))
        self.assertEqual(10, g.untrackedAlgebraicCount(am))

        g.trackAllAlgebraic(am)

        self.assertEqual(10, g.trackedAlgebraicCount(am))
        self.assertEqual(0, g.untrackedAlgebraicCount(am))

        g.untrackAllVariables(am)

        self.assertEqual(0, g.trackedVariableCount(am))
        self.assertEqual(18, g.untrackedVariableCount(am))

        g.trackAllVariables(am)

        self.assertEqual(18, g.trackedVariableCount(am))
        self.assertEqual(0, g.untrackedVariableCount(am))


if __name__ == '__main__':
    unittest.main()
