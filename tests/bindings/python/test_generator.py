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
        from libcellml import Parser
        from libcellml import Generator
        from libcellml import GeneratorProfile
        from test_resources import file_contents

        p = Parser()
        m = p.parseModel(file_contents('generator/algebraic_eqn_computed_var_on_rhs/model.cellml'))

        a = Analyser()
        a.analyseModel(m)

        am = a.model()

        self.assertEqual(AnalyserModel.Type.ALGEBRAIC, am.type())

        g = Generator()

        g.setModel(am)

        self.assertEqual(file_contents("generator/algebraic_eqn_computed_var_on_rhs/model.h"), g.interfaceCode())
        self.assertEqual(file_contents("generator/algebraic_eqn_computed_var_on_rhs/model.c"), g.implementationCode())

        self.assertEqual(GeneratorProfile.Profile.C, g.profile().profile())

        profile = GeneratorProfile(GeneratorProfile.Profile.PYTHON)
        g.setProfile(profile)

        self.assertEqual("", g.interfaceCode())
        self.assertEqual(file_contents("generator/algebraic_eqn_computed_var_on_rhs/model.py"), g.implementationCode())

        self.assertEqual(GeneratorProfile.Profile.PYTHON, g.profile().profile())

    def test_coverage(self):
        from libcellml import Parser
        from libcellml import Generator
        from libcellml import GeneratorProfile
        from libcellml import GeneratorVariable

        p = Parser()
        m = p.parseModel(file_contents('generator/garny_kohl_hunter_boyett_noble_rabbit_san_model_2003/model.cellml'))

        g = Generator()

        g.processModel(m)

        self.assertEqual(Generator.ModelType.ODE, g.modelType())
        self.assertEqual(185, g.variableCount())

        v = g.variable(1)

        self.assertEqual(GeneratorVariable.Type.CONSTANT, v.type())
        self.assertEqual("g_Ca_L_Centre_0DCapable", v.variable().name())

        voi = g.voi()

        self.assertEqual("time", voi.variable().name())

        self.assertEqual(15, g.stateCount())
        self.assertEqual("P_af", g.state(9).variable().name())
        self.assertEqual("V", g.state(14).initialisingVariable().name())

if __name__ == '__main__':
    unittest.main()
