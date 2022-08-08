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

const loadLibCellML = require('libcellml.js/libcellml.common')
const { basicModel } = require('./resources')

let libcellml = null

describe("Analyser Equation tests", () => {
    let m
    let a
    let am
    let eqn

    beforeAll(async () => {
        libcellml = await loadLibCellML()
    });
    beforeEach(() => {
        const p = new libcellml.Parser()
        m = p.parseModel(basicModel)
        a = new libcellml.Analyser()

        a.analyseModel(m)
        expect(a.issueCount()).toBe(0)

        am = a.model()

        expect(am.equationCount()).toBe(1)

        eqn = am.equation(0)
    });
    test('Checking Analyser Equation type.', () => {
        expect(eqn.type().value).toBe(libcellml.AnalyserEquation.Type.RATE.value)
    });
    test('Checking Analyser Equation isStateRateBased.', () => {
        expect(eqn.isStateRateBased()).toBe(false)
    });
    test('Checking Analyser Equation dependencies.', () => {
        expect(eqn.dependencies().size()).toBe(0)
    });
    test('Checking Analyser Equation variable.', () => {
        expect(eqn.variable().variable().name()).toBe("x")
    });
    test('Checking Analyser Equation AST.', () => {
        expect(eqn.ast().value()).toBe("")
    });
 })
