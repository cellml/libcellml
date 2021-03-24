const libCellMLModule = require('libcellml.js/libcellml.common')
let libcellml = null

describe("Model tests", () => {
  beforeAll(async () => {
        libcellml = await libCellMLModule();
    });
  test('Checking Model name.', () => {
    const m = new libcellml.Model()
   
    expect(m.name()).toBe('');

    m.setName('model-test')
    expect(m.name()).toBe('model-test');
  });
})
