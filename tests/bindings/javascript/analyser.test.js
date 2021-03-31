
const libCellMLModule = require('libcellml.js/libcellml.common')
let libcellml = null

const model = "<?xml version=\"1.0\" encoding=\"UTF-8\"?> \
<model name=\"initialised_variable_of_integration\" xmlns=\"http://www.cellml.org/cellml/2.0#\" xmlns:cellml=\"http://www.cellml.org/cellml/2.0#\"> \
    <units name=\"per_second\"> \
        <unit exponent=\"-1\" units=\"second\"/> \
    </units> \
    <component name=\"my_component\"> \
        <variable name=\"time\" units=\"second\" initial_value=\"0\"/> \
        <variable name=\"x\" units=\"dimensionless\" initial_value=\"0\"/> \
        <math xmlns=\"http://www.w3.org/1998/Math/MathML\"> \
            <apply> \
                <eq/> \
                <apply> \
                    <diff/> \
                    <bvar> \
                        <ci>time</ci> \
                    </bvar> \
                    <ci>x</ci> \
                </apply> \
                <cn cellml:units=\"per_second\">1</cn> \
            </apply> \
        </math> \
    </component> \
</model> \
"

describe("Analyser tests", () => {
  beforeAll(async () => {
    libcellml = await libCellMLModule();
  });
  test("Checking Analyser.analyseModel.", () => {
    const p = new libcellml.Parser()
    const m = p.parseModel(model)

    expect(p.issueCount()).toBe(0)

    const a = new libcellml.Analyser()

    a.analyseModel(m)

    expect(a.issueCount()).toBe(1)
    expect(a.issue(0).description()).toBe("Variable 'time' in component 'my_component' cannot be both a variable of integration and initialised.")
  });
  test("Checking Analyser.addExternalVariable.", () => {
  });
  test("Checking Analyser.removeExternalVariableByXXX.", () => {
  });
  test("Checking Analyser.removeExternalVariableByXXX.", () => {
  });
  test("Checking Analyser.removeExternalVariableByXXX.", () => {
  });
  test("Checking Analyser.removeAllExternalVariables.", () => {
  });
  test("Checking Analyser.containsExternalVariableByXXX.", () => {
  });
  test("Checking Analyser.containsExternalVariableByXXX.", () => {
  });
  test("Checking Analyser.externalVariableByXXX.", () => {
  });
  test("Checking Analyser.externalVariableByXXX.", () => {
  });
  test("Checking Analyser.externalVariableCount.", () => {
  });
  test("Checking Analyser.model.", () => {
  });
})
