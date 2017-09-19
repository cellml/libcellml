#
# Tests the bindings for ImportedEntity, which is the base class for all
# entities that can be imported.
#
import sys
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
        del(x, idx)
        
        # Test own methods
        
        # void setImport(const ImportPtr &imp)
        from libcellml.importsource import Import
        x = ImportedEntity()
        x.setImport(Import())
        x.setImport(None)
        del(x)
        
        # bool isImport()
        x = ImportedEntity()
        self.assertFalse(x.isImport())
        x.setImport(Import())
        self.assertTrue(x.isImport())
        x.setImport(None)
        self.assertFalse(x.isImport())
        del(x)

        # ImportPtr getImport()
        i = Import()
        source = 'hello'
        i.setSource(source)
        x = ImportedEntity()
        self.assertIsNone(x.getImport())
        x.setImport(i)
        self.assertIsNotNone(x.getImport())
        self.assertEqual(x.getImport().getSource(), source)
        del(x, i, source)
        
        # void setImportReference(const std::string &reference)
        r = 'yes'
        x = ImportedEntity()
        x.setImportReference('')
        x.setImportReference(r)
        x.setImportReference('')
        del(r, x)
        
        # std::string getImportReference()
        r = 'yes'
        x = ImportedEntity()
        self.assertEqual(x.getImportReference(), '')
        x.setImportReference(r)
        self.assertEqual(x.getImportReference(), r)
        x.setImportReference('')
        self.assertEqual(x.getImportReference(), '')
        del(r, x)        

if __name__ == '__main__':
    unittest.main()
