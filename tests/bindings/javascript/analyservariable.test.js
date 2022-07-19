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
const { hhSquidAxon1952 } = require('./resources')

let libcellml = null

describe("Analyser Variable tests", () => {
    let m
    let a
    let am

    beforeAll(async () => {
        libcellml = await loadLibCellML()
    });
    beforeEach(() => {
        const p = new libcellml.Parser()
        m = p.parseModel(hhSquidAxon1952)
        a = new libcellml.Analyser()

        a.analyseModel(m)
        expect(a.issueCount()).toBe(0)

        am = a.model()

        expect(am.variableCount()).toBe(18)
    });
    test('Checking Analyser Variable type.', () => {
        const av = am.variable(5)
        expect(av.type().value).toBe(libcellml.AnalyserVariable.Type.ALGEBRAIC.value)
    });
    test('Checking Analyser Variable index.', () => {
        const av = am.variable(7)
        expect(av.index()).toBe(7)
    });
    test('Checking Analyser Variable initialising variable.', () => {
        const av = am.variable(3)
        expect(av.initialisingVariable().name()).toBe("g_K")
    });
    test('Checking Analyser Variable variable.', () => {
        const av = am.variable(10)
        expect(av.variable().name()).toBe("alpha_m")
    });
    test('Checking Analyser Variable equation.', () => {
        const av = am.variable(14)
        expect(av.equation().type().value).toBe(libcellml.AnalyserEquation.Type.VARIABLE_BASED_CONSTANT.value)
    });
 })
