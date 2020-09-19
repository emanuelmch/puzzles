/*
 * Copyright (c) 2018 Emanuel Machado da Silva
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

#include "cpic/runner.h"
#include "maths/runner.h"
#include "shurikens/runner.h"
#include "sudoku/runner.h"

#include "common/runners.h"

#include <iostream>
#include <string>

using std::cout;
using std::string;

using Puzzles::runningTime;

int main(int argc, char *argv[]) {
  // TODO Maybe creating a parsing unit?
  string arg = argc >= 2 ? argv[1] : "";
  auto fullRun = arg == "full";

  auto [success, duration] =
      runningTime([=] { return CPic::run() && Maths::run() && Shurikens::run(fullRun) && Sudoku::run(); });

  if (!success) return 1;
  cout << "All good, we took roughly " << duration << " microseconds!\n";
}
