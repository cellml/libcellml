#
# Tests for the ImportRequirement class.
#
import unittest

from test_resources import resource_path, file_contents


class ImportRequirementTestCase(unittest.TestCase):

    def test_create_destroy(self):
        from libcellml.types import ImportRequirement
        from libcellml import Model
        m = Model()
        url = 'i-am-a-url'
        x = ImportRequirement(url, m)
        del x

    def test_url_model(self):
        from libcellml.types import ImportRequirement
        from libcellml import Model

        m = Model()
        m.setName('my_model_name')
        url = 'i-am-a-url'
        x = ImportRequirement(url, m)
        self.assertEquals(url, x.url())
        self.assertEquals('my_model_name', x.model().name())
        del x

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
            self.assertEqual(importer.library(resource_path('importer/requirements/'+keys[i])).name(), r.model().name())
            i += 1


if __name__ == '__main__':
    unittest.main()
