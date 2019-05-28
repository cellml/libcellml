#
# Tests the bindings for ImportedEntity, which is the base class for all
# entities that can be imported.
#
import unittest


class ImportedEntityTestCase(unittest.TestCase):

    def test_create_destroy(self):
        from libcellml import ImportedEntity

        x = ImportedEntity()
        y = ImportedEntity()
        z = ImportedEntity(y)
        del(x, y, z)

    def test_set_import_source(self):
        from libcellml import ImportedEntity, ImportSource

        # void setImportSource(const ImportPtr &imp)
        x = ImportedEntity()
        x.setImportSource(ImportSource())
        x.setImportSource(None)

    def test_is_import(self):
        from libcellml import ImportedEntity, ImportSource

        # bool isImport()
        x = ImportedEntity()
        self.assertFalse(x.isImport())
        x.setImportSource(ImportSource())
        self.assertTrue(x.isImport())
        x.setImportSource(None)
        self.assertFalse(x.isImport())

    def test_get_import_source(self):
        from libcellml import ImportedEntity, ImportSource

        # ImportSourcePtr getImportSource()
        i = ImportSource()
        source = 'hello'
        i.setUrl(source)
        x = ImportedEntity()
        self.assertIsNone(x.getImportSource())
        x.setImportSource(i)
        self.assertIsNotNone(x.getImportSource())
        self.assertEqual(x.getImportSource().getUrl(), source)

    def test_set_import_reference(self):
        from libcellml import ImportedEntity

        # void setImportReference(const std::string &reference)
        r = 'yes'
        x = ImportedEntity()
        x.setImportReference('')
        x.setImportReference(r)
        x.setImportReference('')

    def test_get_import_reference(self):
        from libcellml import ImportedEntity

        # std::string getImportReference()
        r = 'yes'
        x = ImportedEntity()
        self.assertEqual(x.getImportReference(), '')
        x.setImportReference(r)
        self.assertEqual(x.getImportReference(), r)
        x.setImportReference('')
        self.assertEqual(x.getImportReference(), '')


if __name__ == '__main__':
    unittest.main()
