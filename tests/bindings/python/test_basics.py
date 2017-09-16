#
# Tests very basic Python libcellml functionality
#
import sys
import unittest


class BasicsTestCase(unittest.TestCase):

    def test_basics(self):
        try:
            import libcellml
        except ImportError as e:
            self.fail(repr(e))

    def test_component_import(self):
        try:
            import libcellml.component
        except ImportError as e:
            self.fail(repr(e))
        try:
            from libcellml.component import Component
        except ImportError as e:
            self.fail(repr(e))

    def test_component_entity_import(self):
        try:
            import libcellml.componententity
        except ImportError as e:
            self.fail(repr(e))
        try:
            from libcellml.componententity import ComponentEntity
        except ImportError as e:
            self.fail(repr(e))

    def test_named_entity_import(self):
        try:
            import libcellml.namedentity
        except ImportError as e:
            self.fail(repr(e))
        try:
            from libcellml.namedentity import NamedEntity
        except ImportError as e:
            self.fail(repr(e))

    def test_entity_import(self):
        try:
            import libcellml.entity
        except ImportError as e:
            self.fail(repr(e))
        try:
            from libcellml.entity import Entity
        except ImportError as e:
            self.fail(repr(e))

    def test_imported_entity_import(self):
        try:
            import libcellml.importedentity
        except ImportError as e:
            self.fail(repr(e))
        try:
            from libcellml.importedentity import ImportedEntity
        except ImportError as e:
            self.fail(repr(e))

if __name__ == '__main__':
    success = unittest.TextTestRunner().run(suite()).wasSuccessful()
    sys.exit(not success)

