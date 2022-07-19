/*
Copyright libCellML Contributors

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

const libCellMLModule = require('libcellml.js/libcellml.common')
const { basicModel, modelWithError } = require('./resources')

let libcellml = null

describe("Analyser tests", () => {
  let m
  let a
  let aev

  beforeAll(async () => {
    libcellml = await libCellMLModule();
  });
  beforeEach(() => {
    const p = new libcellml.Parser()
    m = p.parseModel(basicModel)
    a = new libcellml.Analyser()

    a.analyseModel(m)
    expect(a.issueCount()).toBe(0)

    const v = m.componentByIndex(0).variableByIndex(0)
    aev = new libcellml.AnalyserExternalVariable(v)
  });
  test("Checking Analyser.analyseModel.", () => {
    const p = new libcellml.Parser()

    m = p.parseModel(modelWithError)
    expect(p.issueCount()).toBe(0)

    a.analyseModel(m)

    expect(a.issueCount()).toBe(1)
    expect(a.issue(0).description()).toBe("Variable 'time' in component 'my_component' cannot be both a variable of integration and initialised.")
  });
  test("Checking Analyser.addExternalVariable.", () => {
     expect(a.addExternalVariable(aev)).toBe(true)
  });
  test("Checking Analyser.removeExternalVariableByIndex.", () => {
    a.addExternalVariable(aev)
    expect(a.externalVariableCount()).toBe(1)
    a.removeExternalVariableByIndex(0)
    expect(a.externalVariableCount()).toBe(0)
  });
  test("Checking Analyser.removeExternalVariableByModel.", () => {
    a.addExternalVariable(aev)
    expect(a.externalVariableCount()).toBe(1)
    a.removeExternalVariableByModel(m, "component", "time")
    expect(a.externalVariableCount()).toBe(0)
  });
  test("Checking Analyser.removeExternalVariableByExternalVariable.", () => {
    a.addExternalVariable(aev)
    expect(a.externalVariableCount()).toBe(1)
    a.removeExternalVariableByExternalVariable(aev)
    expect(a.externalVariableCount()).toBe(0)
  });
  test("Checking Analyser.removeAllExternalVariables.", () => {
    a.addExternalVariable(aev)
    expect(a.externalVariableCount()).toBe(1)
    a.removeAllExternalVariables()
    expect(a.externalVariableCount()).toBe(0)
  });
  test("Checking Analyser.containsExternalVariableByModel.", () => {
    expect(a.containsExternalVariableByModel(m, "component", "time")).toBe(false)
    a.addExternalVariable(aev)
    expect(a.containsExternalVariableByModel(m, "component", "time")).toBe(true)
  });
  test("Checking Analyser.containsExternalVariableByExternalVariable.", () => {
    expect(a.containsExternalVariableByExternalVariable(aev)).toBe(false)
    a.addExternalVariable(aev)
    expect(a.containsExternalVariableByExternalVariable(aev)).toBe(true)
  });
  test("Checking Analyser.externalVariableByIndex.", () => {
    a.addExternalVariable(aev)
    expect(a.externalVariableByIndex(0)).toStrictEqual(aev)
  });
  test("Checking Analyser.externalVariableByModel.", () => {
    a.addExternalVariable(aev)
    expect(a.externalVariableByModel(m, "component", "time")).toStrictEqual(aev)
  });
  test("Checking Analyser.externalVariableCount.", () => {
    expect(a.externalVariableCount()).toBe(0)
    a.addExternalVariable(aev)
    expect(a.externalVariableCount()).toBe(1)
  });
  test("Checking Analyser.model.", () => {
    expect(a.model()).toBeDefined()
  });
})
