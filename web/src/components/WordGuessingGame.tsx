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

import GuessesGrid from './GuessesGrid'

import assert from 'assert'
import React from 'react'

import { MAX_GUESSES } from '../lib/WordGuessingConstants'

type WordGuessingGameProps = any
type WordGuessingGameState = {
  oldGuesses: string[]
}

class WordGuessingGame extends React.Component<WordGuessingGameProps, WordGuessingGameState> {
  constructor(props: any) {
    super(props)
    this.state = {
      oldGuesses: [] as string[]
    }
  }

  render() {
    return (
      <GuessesGrid
        oldGuesses={this.state.oldGuesses}
        onNewGuess={this.addNewGuess}
      />
    )
  }

  addNewGuess = (newGuess: string) => {
    assert(newGuess.length === 5)
    assert(this.state.oldGuesses.length < MAX_GUESSES)

    const oldGuesses = this.state.oldGuesses
    oldGuesses.push(newGuess)
    this.setState({ oldGuesses })
  }
}

export default WordGuessingGame
