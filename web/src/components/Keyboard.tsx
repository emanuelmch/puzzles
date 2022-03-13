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

import './Keyboard.css'

import React, { useEffect } from 'react'

type KeyboardProps = {
  onChar: (value: string) => void,
  onBackspace: () => void,
  onEnter: () => void
}

const BACKSPACE = '⌫'
const ENTER = '☑'

const letters = [
  ['Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P'],
  ['A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', BACKSPACE],
  ['Z', 'X', 'C', 'V', 'B', 'N', 'M', ENTER]
]

function Keyboard(props: KeyboardProps) {
  const { onEnter, onBackspace, onChar } = props

  useEffect(() => {
    const listener = (e: KeyboardEvent) => {
      if (e.code === 'Enter') {
        onEnter()
      } else if (e.code === 'Backspace') {
        onBackspace()
      } else {
        const key = e.key.toUpperCase()
        if (key.length === 1 && key >= 'A' && key <= 'Z') {
          onChar(key)
        }
      }
    }

    window.addEventListener('keyup', listener)
    return () => {
      window.removeEventListener('keyup', listener)
    }
  }, [onEnter, onBackspace, onChar])

  const handleClick = (character: string) => {
    if (character === BACKSPACE) {
      onBackspace()
    } else if (character === ENTER) {
      onEnter()
    } else {
      onChar(character)
    }
  }

  return (
    <div className='Keyboard'>
      {letters.map((letterGroup, index) =>
        <div className='KeyboardRow' key={'letter_group_' + index}>
          {
            letterGroup.map(letter =>
              <button key={'key_' + letter}
                className={(letter === BACKSPACE || letter === ENTER) ? 'KeyboardButton KeyboardButton-SpecialButton' : 'KeyboardButton KeyboardButton-NormalButton'}
                onClick={() => handleClick(letter)}>
                {letter}
              </button>
            )
          }
        </div>
      )
      }
    </div >
  )
}

export default Keyboard
