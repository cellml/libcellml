const libCellMLModule = require('libcellml.js/libcellml.common')
let libcellml = null

describe("Version tests", () => {
  beforeAll(async () => {
        libcellml = await libCellMLModule();
    });
 test('Checking version string.', () => {
   expect(libcellml.versionString()).toBe('0.3.0');
 });
})
