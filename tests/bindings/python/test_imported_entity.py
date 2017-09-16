#
# Tests the ImportedEntity class, which is the base class for all entities that
# can be imported.
#
import unittest

class ImportedEntityTestCase(unittest.TestCase):

    def test_imported_entity(self):
        from libcellml.importedentity import ImportedEntity
        
        # Test create/copy/destroy
        x = ImportedEntity()
        del(x)
        y = ImportedEntity()
        z = ImportedEntity(y)
        del(y,z)
        
        # Test inheritance
        x = ImportedEntity()
        from libcellml.namedentity import NamedEntity
        self.assertIsInstance(x, NamedEntity)
        from libcellml.entity import Entity
        self.assertIsInstance(x, Entity)

        # Test access to inherited methods
        x = ImportedEntity()
        idx = 'test'
        self.assertIs(x.getId(), '')
        x.setId(idx)
        self.assertEqual(x.getId(), idx)
        
        # Test own methods
        reference = 'hello'
        x = ImportedEntity()
        self.assertFalse(x.isImport())
        self.assertIs(x.getImportReference(), '')
        self.assertIsNone(x.getImport())
        x.setImportReference(reference)
        self.assertEqual(x.getImportReference(), reference)
        self.assertFalse(x.isImport())
        
        from libcellml.imports import Import
        source = 'yellow'
        y = Import()
        y.setSource(source)
        x.setImport(y)
        self.assertTrue(x.isImport())
        self.assertIsNotNone(x.getImport(), y)
        self.assertIsInstance(x.getImport(), Import)
        self.assertEqual(x.getImport().getSource(), source)
        x.setImport(None)
        self.assertIsNone(x.getImport())
        self.assertFalse(x.isImport())

if __name__ == '__main__':
    success = unittest.TextTestRunner().run(suite()).wasSuccessful()
    sys.exit(not success)

