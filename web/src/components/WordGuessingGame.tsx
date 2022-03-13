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
import Keyboard from './Keyboard'
import { isTargetWord } from '../lib/WordValidator'

import assert from 'assert'
import React from 'react'

import { MAX_GUESSES } from '../lib/WordGuessingConstants'

type WordGuessingGameProps = any
type WordGuessingGameState = {
  oldGuesses: string[]
  isGameOver: boolean,
  currentGuess: string
}

class WordGuessingGame extends React.Component<WordGuessingGameProps, WordGuessingGameState> {
  constructor(props: any) {
    super(props)
    this.state = {
      oldGuesses: [],
      isGameOver: false,
      currentGuess: ''
    }
  }

  componentDidUpdate(_: any, prevState: WordGuessingGameState) {
    // TODO: This doesn't feel like the best place for this check, check if there any actual performance issues of waiting until this lifecyle
    // call to update isGameOver whenever we update oldGuesses
    if (this.state.oldGuesses !== prevState.oldGuesses && this.isGameOver()) {
      this.setState({ isGameOver: true })
    }
  }

  render() {
    return (
      <>
        <GuessesGrid
          oldGuesses={this.state.oldGuesses}
          isGameOver={this.state.isGameOver}
          currentGuess={this.state.currentGuess}
        />
        {!this.state.isGameOver &&
          <Keyboard
            onChar={this.onChar}
            onBackspace={this.onBackspace}
            onEnter={this.onEnter} />
        }
      </>
    )
  }

  onChar = (char: String) => {
    const currentGuess = this.state.currentGuess
    if (currentGuess.length < 5) {
      this.setState({ currentGuess: currentGuess + char })
    }
  }

  onBackspace = () => {
    const currentGuess = this.state.currentGuess
    if (currentGuess.length > 0) {
      this.setState({ currentGuess: currentGuess.slice(0, -1) })
    }
  }

  onEnter = () => {
    const { oldGuesses, currentGuess } = this.state
    if (oldGuesses.length < MAX_GUESSES && currentGuess.length === 5) {
      this.setState({
        oldGuesses: oldGuesses.concat(currentGuess),
        currentGuess: ''
      })
    }
  }

  isGameOver = () => {
    assert(this.state.isGameOver === false)

    const { oldGuesses } = this.state
    if (oldGuesses.length === 0) return false
    if (oldGuesses.length === MAX_GUESSES) return true

    const lastGuess = oldGuesses.at(oldGuesses.length - 1)!
    return isTargetWord(lastGuess)
  }
}

export default WordGuessingGame
