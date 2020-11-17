#
# Tests the Importer class bindings.
#
import unittest

from test_resources import resource_path, file_contents


class ValidatorTestCase(unittest.TestCase):

    def test_create_destroy(self):
        from libcellml import Importer

        x = Importer()
        del x

    def test_inheritance(self):
        import libcellml
        from libcellml import Importer

        # Test inheritance.
        x = Importer()
        self.assertIsInstance(x, libcellml.logger.Logger)

        # Test access to inherited methods.
        self.assertIsNone(x.issue(0))
        self.assertIsNone(x.issue(-1))
        self.assertEqual(x.issueCount(), 0)
        x.addIssue(libcellml.Issue())
        self.assertEqual(x.issueCount(), 1)

    def test_resolve_imports(self):
        from libcellml import Importer
        from libcellml import Parser

        i = Importer()
        p = Parser()

        m = p.parseModel(file_contents('sine_approximations_import.xml'))

        self.assertEqual(0, p.issueCount())

        self.assertTrue(m.hasUnresolvedImports())

        i.resolveImports(m, resource_path())
        self.assertFalse(m.hasUnresolvedImports())

    def test_importer(self):
        from libcellml import Importer, Parser, Printer

        parser = Parser()
        i = Importer()

        m = parser.parseModel(file_contents('importer/diamond.cellml'))
        printer = Printer()

        i.resolveImports(m, resource_path('importer/'))
        self.assertFalse(m.hasUnresolvedImports())

        # Library should contain left, right, and one instance (not two) of the point.
        self.assertEqual(3, i.libraryCount())
        self.assertEqual(resource_path(
            'importer/diamond_left.cellml'), i.key(0))
        self.assertEqual(resource_path(
            'importer/diamond_point.cellml'), i.key(1))
        self.assertEqual(resource_path(
            'importer/diamond_right.cellml'), i.key(2))

        # Access library items by their URL.
        left = i.library(resource_path('importer/diamond_left.cellml'))

        self.assertEqual(file_contents(
            'importer/diamond_left.cellml'), printer.printModel(left))

    def test_add_model(self):
        from libcellml import Component, Importer, Model, Parser

        parser = Parser()
        importer = Importer()

        model = parser.parseModel(file_contents(
            'importer/generic_no_source.cellml'))

        sourceModel = Model('source')
        sourceModel.addComponent(Component('a'))
        sourceModel.addComponent(Component('b'))
        sourceModel.addComponent(Component('c'))
        sourceModel.addComponent(Component('d'))

        # Add a model manually to the library, including the URL that it will replace in future imports.
        self.assertTrue(importer.addModel(sourceModel, 'i_dont_exist.cellml'))
        self.assertFalse(importer.addModel(sourceModel, 'i_dont_exist.cellml'))

        importer.resolveImports(model, '')

        self.assertEqual(0, importer.issueCount())
        self.assertFalse(model.hasUnresolvedImports())

    def test_replace_model(self):
        from libcellml import Component, Importer, Model, Parser

        parser = Parser()

        model = parser.parseModel(file_contents(
            'importer/generic_no_source.cellml'))

        importer = Importer()

        wrongSourceModel = Model('wrong')
        rightSourceModel = Model('right')
        rightSourceModel.addComponent(Component('a'))
        rightSourceModel.addComponent(Component('b'))
        rightSourceModel.addComponent(Component('c'))
        rightSourceModel.addComponent(Component('d'))

        self.assertTrue(importer.addModel(
            wrongSourceModel, 'i_dont_exist.cellml'))

        self.assertFalse(importer.replaceModel(
            rightSourceModel, 'not_in_library'))
        self.assertTrue(importer.replaceModel(
            rightSourceModel, 'i_dont_exist.cellml'))

        importer.resolveImports(model, '')

        self.assertEqual(0, importer.issueCount())
        self.assertFalse(model.hasUnresolvedImports())

    def test_flatten(self):
        from libcellml import Importer, Parser

        parser = Parser()
        importer = Importer()

        model = parser.parseModel(file_contents('importer/diamond.cellml'))

        importer.resolveImports(model, resource_path('importer/'))

        flattenedModel = importer.flattenModel(model)
        self.assertEqual(2, flattenedModel.componentCount())

    def test_clear_imports(self):
        from libcellml import Importer, Parser

        parser = Parser()
        importer = Importer()

        model = parser.parseModel(file_contents(
            'importer/nested_components.cellml'))
        self.assertEqual(0, parser.issueCount())

        importer.resolveImports(model, resource_path('importer/'))

        self.assertEqual(0, importer.issueCount())

        self.assertFalse(model.hasUnresolvedImports())
        importer.clearImports(model)
        self.assertTrue(model.hasUnresolvedImports())

    def test_requirements(self):
        from libcellml import Parser, Importer
        keys = [
            'complicatedComponents.cellml',
            'components.cellml',
            'complicatedUnits.cellml',
            'units1.cellml',
            'units2.cellml'
        ]

        parser = Parser()
        model = parser.parseModel(
            file_contents('importer/requirements/complicatedExample.cellml'))
        self.assertEqual(0, parser.issueCount())

        importer = Importer()
        importer.resolveImports(model, resource_path('importer/requirements/'))
        self.assertEqual(0, importer.issueCount())

        requirements = importer.requirements(model)

        i = 0
        for r in requirements:
            self.assertEqual(keys[i], r.url())
            i += 1


if __name__ == '__main__':
    unittest.main()
