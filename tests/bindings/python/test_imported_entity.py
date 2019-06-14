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

    def test_import_source(self):
        from libcellml import ImportedEntity, ImportSource

        # ImportSourcePtr importSource()
        i = ImportSource()
        source = 'hello'
        i.setUrl(source)
        x = ImportedEntity()
        self.assertIsNone(x.importSource())
        x.setImportSource(i)
        self.assertIsNotNone(x.importSource())
        self.assertEqual(x.importSource().url(), source)

    def test_set_import_reference(self):
        from libcellml import ImportedEntity

        # void setImportReference(const std::string &reference)
        r = 'yes'
        x = ImportedEntity()
        x.setImportReference('')
        x.setImportReference(r)
        x.setImportReference('')

    def test_import_reference(self):
        from libcellml import ImportedEntity

        # std::string importReference()
        r = 'yes'
        x = ImportedEntity()
        self.assertEqual(x.importReference(), '')
        x.setImportReference(r)
        self.assertEqual(x.importReference(), r)
        x.setImportReference('')
        self.assertEqual(x.importReference(), '')


if __name__ == '__main__':
    unittest.main()
