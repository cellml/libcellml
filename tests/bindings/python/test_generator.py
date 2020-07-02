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
        a.processModel(m)

        am = a.model()

        self.assertEqual(AnalyserModel.Type.ALGEBRAIC, am.type())

        g = Generator()

        self.assertEqual(file_contents("generator/algebraic_eqn_computed_var_on_rhs/model.py"),
                         g.implementationCode(am))

        profile = GeneratorProfile(GeneratorProfile.Profile.C)
        g.setProfile(profile)

        self.assertEqual(file_contents("generator/algebraic_eqn_computed_var_on_rhs/model.h"), g.interfaceCode(am))
        self.assertEqual(file_contents("generator/algebraic_eqn_computed_var_on_rhs/model.c"), g.implementationCode(am))


if __name__ == '__main__':
    unittest.main()
