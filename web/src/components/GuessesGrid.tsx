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
import { PastGuess, PresentGuess, FutureGuess } from './GuessesGridRows'

import React, { useState } from 'react'

import { MAX_GUESSES } from '../lib/WordGuessingConstants'

type GuessesGridProps = {
  oldGuesses: Array<string>
  isGameOver: boolean
  onNewGuess: (guess: string) => void
}

function GuessesGrid({ oldGuesses, isGameOver, onNewGuess }: GuessesGridProps) {
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
  }

  return (
    <div>
      {!isGameOver &&
        <KeyboardReader
          onChar={onChar}
          onBackspace={onBackspace}
          onEnter={onEnter}
        />
      }
      {
        oldGuesses.map(guess =>
          <PastGuess key={'guess_' + guess} guess={guess} />
        )
      }
      {!isGameOver &&
        <PresentGuess guess={currentGuess} />
      }
      {oldGuesses.length < MAX_GUESSES &&
        [...Array(MAX_GUESSES - 1 - oldGuesses.length)].map((_, i) =>
          <FutureGuess key={'empty_' + i} />
        )
      }
      {isGameOver && oldGuesses.length !== MAX_GUESSES &&
        <FutureGuess />
      }
    </div>
  )
}

export default GuessesGrid
