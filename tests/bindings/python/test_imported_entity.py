#
# Tests the bindings for ImportedEntity, which is the base class for all
# entities that can be imported.
#
import sys
import unittest

class ImportedEntityTestCase(unittest.TestCase):

    def test_imported_entity(self):
        import libcellml
        from libcellml import ImportedEntity
        
        # Test create/copy/destroy
        x = ImportedEntity()
        del(x)
        y = ImportedEntity()
        z = ImportedEntity(y)
        del(y, z)
        
        # Test inheritance
        x = ImportedEntity()
        self.assertIsInstance(x, libcellml.NamedEntity)
        self.assertIsInstance(x, libcellml.Entity)

        # Test access to inherited methods
        x = ImportedEntity()
        idx = 'test'
        self.assertIs(x.getId(), '')
        x.setId(idx)
        self.assertEqual(x.getId(), idx)
        del(x, idx)
        
        # Test own methods
        
        # void setImportSource(const ImportPtr &imp)
        from libcellml import ImportSource
        x = ImportedEntity()
        x.setImportSource(ImportSource())
        x.setImportSource(None)
        del(x)
        
        # bool isImport()
        x = ImportedEntity()
        self.assertFalse(x.isImport())
        x.setImportSource(ImportSource())
        self.assertTrue(x.isImport())
        x.setImportSource(None)
        self.assertFalse(x.isImport())
        del(x)

        # ImportSourcePtr getImportSource()
        i = ImportSource()
        source = 'hello'
        i.setSource(source)
        x = ImportedEntity()
        self.assertIsNone(x.getImportSource())
        x.setImportSource(i)
        self.assertIsNotNone(x.getImportSource())
        self.assertEqual(x.getImportSource().getSource(), source)
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
