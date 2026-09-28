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
let libcellml = null

describe("Variable tests", () => {
    beforeAll(async () => {
        libcellml = await loadLibCellML()
    })
    test('Checking issue as string', () => {
        expect(libcellml.Issue.levelAsString(libcellml.Issue.Level.ERROR)).toBe("error")
        expect(libcellml.Issue.referenceRuleAsString(libcellml.Issue.ReferenceRule.ANALYSER_VARIABLE_INITIALISED_MORE_THAN_ONCE)).toBe("analyser_variable_initialised_more_than_once")
    })
})
