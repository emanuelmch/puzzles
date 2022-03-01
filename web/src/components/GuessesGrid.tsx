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

const LetterSquare = ({ letter, active }: { letter: String, active: Boolean }) => (
    <div className={active ? 'LetterSquare' : 'LetterSquare-inactive'}>{letter}</div>
)

type GridRowProps = {
    guess: String,
    active: Boolean
}

const GridRow = (props: GridRowProps) => (
    <div className='GridRow'>
        {
            [...Array(5)].map((_, i) =>
                <LetterSquare key={i} letter={props.guess.charAt(i)} active={props.active} />
            )
        }
    </div>
)

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
                    <GridRow key={'guess_' + guess} guess={guess} active={false} />
                )
            }
            {oldGuesses.length < MAX_GUESSES &&
                <GridRow guess={currentGuess} active={true} />
            }
            {oldGuesses.length < MAX_GUESSES &&
                [...Array(MAX_GUESSES - 1 - oldGuesses.length)].map((_, i) =>
                    <GridRow key={'empty_' + i} active={false} guess={''} />
                )
            }
        </div>
  )
}

export default Grid
