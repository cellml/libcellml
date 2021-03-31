const libCellMLModule = require('libcellml.js/libcellml.common')
let libcellml = null

const model = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><model xmlns=\"http://www.cellml.org/cellml/2.0#\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" name=\"sin\"> \
  <component name=\"sin\"> \
    <variable name=\"x\" units=\"dimensionless\" interface=\"public_and_private\"/> \
    <variable units=\"dimensionless\" name=\"sin\" interface=\"public_and_private\"/> \
    <math xmlns=\"http://www.w3.org/1998/Math/MathML\"> \
      <apply><eq/> \
        <ci>sin</ci> \
        <apply><sin/> \
          <ci>x</ci> \
        </apply> \
      </apply> \
    </math> \
  </component> \
</model> \
"

describe("Validator tests", () => {
  beforeAll(async () => {
    libcellml = await libCellMLModule();
  });
  test("Checking Validator.validateModel.", () => {
    const x = new libcellml.Validator()
    const p = new libcellml.Parser()

    const m = p.parseModel(model)

    x.validateModel(m)

    expect(x.issueCount()).toBe(0)
  });
})
