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

import { ValidationState, validateWord } from '../lib/WordValidator'
import { WORD_LENGTH } from '../lib/WordGuessingConstants'

import assert from 'assert'
import React from 'react'

import './GuessesGridRows.css'

const enum LetterState {
  Active,
  Inactive,
  Incorrect,
  Present,
  Correct
}

function toClassName(state: LetterState) {
  switch (state) {
    case LetterState.Active:
      return 'LetterSquare LetterSquare-Active'
    case LetterState.Inactive:
      return 'LetterSquare LetterSquare-Inactive'
    case LetterState.Incorrect:
      return 'LetterSquare LetterSquare-Incorrect'
    case LetterState.Present:
      return 'LetterSquare LetterSquare-Present'
    case LetterState.Correct:
      return 'LetterSquare LetterSquare-Correct'
  }
}

function LetterSquare({ letter, state }: { letter: string, state: LetterState }) {
  assert(letter.length === 0 || letter.length === 1)
  return (
    <div className={toClassName(state)}>{letter}</div>
  )
}

type ValidatedLetter = {
  letter: string
  state: LetterState
}

function renderGuess(letters: Array<ValidatedLetter>) {
  return (
    <div className='GridGuess'>
      {
        letters.map((letter, index) =>
          <LetterSquare key={'letter_' + index}
            letter={letter.letter}
            state={letter.state} />
        )
      }
    </div>
  )
}

type PastGuessProps = { guess: string }
function PastGuess({ guess }: PastGuessProps) {
  const letters: Array<ValidatedLetter> = []

  for (const { letter, validationState } of validateWord(guess)) {
    let state: LetterState
    switch (validationState) {
      case ValidationState.Correct:
        state = LetterState.Correct
        break
      case ValidationState.Incorrect:
        state = LetterState.Incorrect
        break
      case ValidationState.Present:
        state = LetterState.Present
        break
    }
    letters.push({ letter, state })
  }
  return renderGuess(letters)
}

type PresentGuessProps = {
  guess: string
}
function PresentGuess({ guess }: PresentGuessProps) {
  const letters: Array<ValidatedLetter> = []

  for (const letter of guess) {
    letters.push({ letter, state: LetterState.Active })
  }
  for (let i = guess.length; i < WORD_LENGTH; ++i) {
    letters.push({ letter: '', state: LetterState.Active })
  }

  return renderGuess(letters)
}

function FutureGuess() {
  const letters: Array<ValidatedLetter> = []

  for (let i = 0; i < WORD_LENGTH; ++i) {
    letters.push({ letter: '', state: LetterState.Inactive })
  }

  return renderGuess(letters)
}

export { PastGuess, PresentGuess, FutureGuess }
