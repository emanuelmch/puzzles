/*
 * Copyright (c) 2022 Emanuel Machado da Silva
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

import { ValidationState, validateWord } from './WordValidator';

test('validates a word with all correct letters', () => {
    let result = validateWord('BUNNY')

    expect(result.length).toEqual(5)
    expect(result.at(0)).toEqual({ letter: 'B', validationState: ValidationState.Correct })
    expect(result.at(1)).toEqual({ letter: 'U', validationState: ValidationState.Correct })
    expect(result.at(2)).toEqual({ letter: 'N', validationState: ValidationState.Correct })
    expect(result.at(3)).toEqual({ letter: 'N', validationState: ValidationState.Correct })
    expect(result.at(4)).toEqual({ letter: 'Y', validationState: ValidationState.Correct })
});

test('validates a word with all present letters', () => {
    let result = validateWord('NYBUN')

    expect(result.length).toEqual(5)
    expect(result.at(0)).toEqual({ letter: 'N', validationState: ValidationState.Present })
    expect(result.at(1)).toEqual({ letter: 'Y', validationState: ValidationState.Present })
    expect(result.at(2)).toEqual({ letter: 'B', validationState: ValidationState.Present })
    expect(result.at(3)).toEqual({ letter: 'U', validationState: ValidationState.Present })
    expect(result.at(4)).toEqual({ letter: 'N', validationState: ValidationState.Present })
});

test('validates a word with all incorrect letters', () => {
    let result = validateWord('WHALE')

    expect(result.length).toEqual(5)
    expect(result.at(0)).toEqual({ letter: 'W', validationState: ValidationState.Incorrect })
    expect(result.at(1)).toEqual({ letter: 'H', validationState: ValidationState.Incorrect })
    expect(result.at(2)).toEqual({ letter: 'A', validationState: ValidationState.Incorrect })
    expect(result.at(3)).toEqual({ letter: 'L', validationState: ValidationState.Incorrect })
    expect(result.at(4)).toEqual({ letter: 'E', validationState: ValidationState.Incorrect })
});
