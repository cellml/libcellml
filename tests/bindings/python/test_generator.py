#
# Tests the Parser class bindings
#
import unittest

from test_resources import file_contents

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


if __name__ == '__main__':
    unittest.main()
