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

        self.assertIsNone(g.model())

        g.setModel(am)

        self.assertIsNotNone(g.model())

        self.assertEqual(file_contents("generator/algebraic_eqn_computed_var_on_rhs/model.h"), g.interfaceCode())
        self.assertEqual(file_contents("generator/algebraic_eqn_computed_var_on_rhs/model.c"), g.implementationCode())

        self.assertEqual(GeneratorProfile.Profile.C, g.profile().profile())

        profile = GeneratorProfile(GeneratorProfile.Profile.PYTHON)
        g.setProfile(profile)

        self.assertEqual("", g.interfaceCode())
        self.assertEqual(file_contents("generator/algebraic_eqn_computed_var_on_rhs/model.py"), g.implementationCode())

        self.assertEqual(GeneratorProfile.Profile.PYTHON, g.profile().profile())


if __name__ == '__main__':
    unittest.main()
