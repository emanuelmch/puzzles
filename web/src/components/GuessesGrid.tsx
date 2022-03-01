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

import KeyboardReader from './KeyboardReader'

import React, { useState } from 'react'

import './GuessesGrid.css'

const MAX_GUESSES = 6

enum LetterState {
    Active,
    Inactive,
    Incorrect,
    AnotherPlace,
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
    case LetterState.AnotherPlace:
      return 'LetterSquare LetterSquare-AnotherPlace'
    case LetterState.Correct:
      return 'LetterSquare LetterSquare-Correct'
  }
}

const LetterSquare = ({ letter, state }: { letter: String, state: LetterState }) => (
    <div className={toClassName(state)}>{letter}</div>
)

type GridRowProps = {
    guess: String,
    activeGuess?: Boolean
}

const GridRow = (props: GridRowProps) => {
  const states = Array<{ letter: string, state: LetterState }>(0)
  for (let i = 0; i < 5; ++i) {
    const letter = props.guess.charAt(i)
    let state: LetterState

    if (props.activeGuess === true) {
      state = LetterState.Active
    } else if (letter === '') {
      state = LetterState.Inactive
    } else {
      switch (i % 3) {
        case 0:
          state = LetterState.Incorrect
          break
        case 1:
          state = LetterState.AnotherPlace
          break
        case 2:
        default: // Will never help, but helps the compiler
          state = LetterState.Correct
          break
      }
    }

    states.push({ letter, state })
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

function Grid() {
  const [oldGuesses, setOldGuesses] = useState<string[]>([])
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
      const guesses = oldGuesses
      guesses.push(currentGuess)

      setOldGuesses(guesses)
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

export default Grid
