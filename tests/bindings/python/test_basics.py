#
# Tests very basic Python libcellml functionality
#
import sys
import unittest

class BasicsTestCase(unittest.TestCase):

    def test_libcellml_import(self):
        import libcellml

    def test_component_import(self):
        import libcellml.component
        from libcellml.component import Component

    def test_component_entity_import(self):
        import libcellml.componententity
        from libcellml.componententity import ComponentEntity

    def test_entity_import(self):
        import libcellml.entity
        from libcellml.entity import Entity

    def test_import(self):
        import libcellml.importsource
        from libcellml.importsource import Import

    def test_imported_entity_import(self):
        import libcellml.importedentity
        from libcellml.importedentity import ImportedEntity

    def test_named_entity_import(self):
        import libcellml.namedentity
        from libcellml.namedentity import NamedEntity

    def test_model_import(self):
        import libcellml.model
        from libcellml.model import Model

if __name__ == '__main__':
    unittest.main()
