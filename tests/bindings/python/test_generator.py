#
# Tests the Parser class bindings
#
import unittest

from test_resources import file_contents

class GeneratorVariableTestCase(unittest.TestCase):

    def test_create_destroy(self):
        from libcellml import GeneratorVariable

        x = GeneratorVariable()
        del(x)


class GeneratorTestCase(unittest.TestCase):

    def test_create_destroy(self):
        from libcellml import Generator

        x = Generator()
        del(x)

    def test_inheritance(self):
        import libcellml
        from libcellml import Generator

        x = Generator()
        self.assertIsInstance(x, libcellml.logger.Logger)

        # Test access to inherited methods
        self.assertIsNone(x.issue(0))
        self.assertIsNone(x.issue(-1))
        self.assertEqual(x.issueCount(), 0)
        x.addIssue(libcellml.Issue())
        self.assertEqual(x.issueCount(), 1)

    def test_process_model(self):
        from libcellml import Generator
        from libcellml import Model

        m = Model()
        g = Generator()

        g.processModel(m)

        self.assertEqual(0, g.errorCount())
        self.assertEqual(Generator.ModelType.UNKNOWN, g.modelType())

    def test_algebraic_eqn_computed_var_on_rhs(self):
        from libcellml import Parser
        from libcellml import Generator
        from libcellml import GeneratorProfile

        p = Parser()
        m = p.parseModel(file_contents('generator/algebraic_eqn_computed_var_on_rhs/model.cellml'))

        g = Generator()

        g.processModel(m)

        self.assertEqual(Generator.ModelType.ALGEBRAIC, g.modelType())

        self.assertEqual(file_contents("generator/algebraic_eqn_computed_var_on_rhs/model.py"), g.implementationCode())

        profile = GeneratorProfile(GeneratorProfile.Profile.C)
        g.setProfile(profile)

        self.assertEqual(file_contents("generator/algebraic_eqn_computed_var_on_rhs/model.h"), g.interfaceCode())
        self.assertEqual(file_contents("generator/algebraic_eqn_computed_var_on_rhs/model.c"), g.implementationCode())

        self.assertEqual(GeneratorProfile.Profile.C, g.profile().profile())

    def test_getters(self):
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
