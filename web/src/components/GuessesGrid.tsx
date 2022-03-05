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

import './GuessesGrid.css'

import KeyboardReader from './KeyboardReader'
import { ValidationState, validateWord } from '../lib/WordValidator'

import React, { useState } from 'react'

import { MAX_GUESSES, WORD_LENGTH } from '../lib/WordGuessingConstants'

enum LetterState {
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

const LetterSquare = ({ letter, state }: { letter: string, state: LetterState }) => (
  <div className={toClassName(state)}>{letter}</div>
)

type GridRowProps = {
  guess: string,
  activeGuess?: Boolean
}

const GridRow = (props: GridRowProps) => {
  const states = new Array<{ letter: string, state: LetterState }>(0)

  if (props.activeGuess === true) {
    const state = LetterState.Active
    for (const letter of props.guess) {
      states.push({ letter, state })
    }
    for (let i = props.guess.length; i < WORD_LENGTH; ++i) {
      states.push({ letter: '', state })
    }
  } else if (props.guess.length === 0) {
    const state = LetterState.Inactive
    for (let i = 0; i < WORD_LENGTH; ++i) {
      states.push({ letter: '', state })
    }
  } else {
    for (const { letter, validationState } of validateWord(props.guess)) {
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
      states.push({ letter, state })
    }
  }

  return (
    <div className='GridRow'>
      {
        states.map((state, index) =>
          <LetterSquare key={'letter_' + index}
            letter={state.letter}
            state={state.state} />
        )
      }
    </div>
  )
}

type GuessesGridProps = {
  oldGuesses: string[]
  onNewGuess: (guess: string) => void
}

function GuessesGrid({ oldGuesses, onNewGuess }: GuessesGridProps) {
  const [currentGuess, setCurrentGuess] = useState('')

  const onChar = (char: String) => {
    if (currentGuess.length < 5) {
      setCurrentGuess(currentGuess + char)
    }
  }

  const onBackspace = () => {
    if (currentGuess.length > 0) {
      const newWord = currentGuess.slice(0, -1)
      setCurrentGuess(newWord)
    }
  }

  const onEnter = () => {
    if (oldGuesses.length < MAX_GUESSES && currentGuess.length === 5) {
      onNewGuess(currentGuess)
      setCurrentGuess('')
    }
    console.log(`oldGuesses = ${oldGuesses}`)
  }

  return (
    <div>
      <KeyboardReader
        onChar={onChar}
        onBackspace={onBackspace}
        onEnter={onEnter}
      />
      {
        oldGuesses.map(guess =>
          <GridRow key={'guess_' + guess} guess={guess} />
        )
      }
      {oldGuesses.length < MAX_GUESSES &&
        <GridRow guess={currentGuess} activeGuess={true} />
      }
      {oldGuesses.length < MAX_GUESSES &&
        [...Array(MAX_GUESSES - 1 - oldGuesses.length)].map((_, i) =>
          <GridRow key={'empty_' + i} guess={''} />
        )
      }
    </div>
  )
}

export default GuessesGrid
