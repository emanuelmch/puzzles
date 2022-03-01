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

import assert from 'assert'

enum ValidationState {
    Incorrect,
    Present,
    Correct
}

type ValidatedLetter = {
    letter: string
    validationState: ValidationState
}

function validateWord(word: String): Array<ValidatedLetter> {
  assert(word.length === 5)
  assert(word === word.toUpperCase())

  const rightWord = 'BUNNY'

  // TODO: Create a Bag type
  const remainingLettersBucket = []
  for (const letter of rightWord) {
    remainingLettersBucket.push(letter)
  }

  const result: Array<ValidatedLetter> = []
  for (let i = 0; i < word.length; ++i) {
    const actual = word.charAt(i)
    const index = remainingLettersBucket.indexOf(actual)

    if (index === -1) {
      result.push({ letter: actual, validationState: ValidationState.Incorrect })
      continue
    }

    const expected = rightWord.charAt(i)
    if (actual === expected) {
      result.push({ letter: actual, validationState: ValidationState.Correct })
    } else {
      result.push({ letter: actual, validationState: ValidationState.Present })
    }
    remainingLettersBucket.splice(index, 1)
  }

  return result
}

export { ValidationState, validateWord }
