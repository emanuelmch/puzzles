/*
 * Copyright (c) 2020 Emanuel Machado da Silva
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

#include "runner.h"

#include "shurikens/data/data.h"
#include "shurikens/logger.h"
#include "shurikens/solver/breadth_search_solver.h"
#include "shurikens/solver/depth_search_solver.h"
#include "shurikens/solver/threaded_search_solver.h"

#include "common/runners.h"

#include <iostream>
#include <memory>

using namespace Shurikens;
using namespace std::chrono_literals;

using Puzzles::runningTime;

using std::cout;

inline bool runSolvers(bool fullRun) {
  std::unique_ptr<Solver> solvers[] = {std::make_unique<BreadthSearchSolver>(), std::make_unique<DepthSearchSolver>(),
                                       std::make_unique<ThreadedSearchSolver>()};
  Logger logger;

  auto allSuccess = true;
  auto shurikens = Shurikens::createAllShurikens();

  for (const auto &data : shurikens) {
    for (const auto &solver : solvers) {
      if (!fullRun && data.solutionSize() > solver->quickSolveLimit) {
        //        cout << "Shuriken: Skipped " << solver->name << " solve for " << data.name << "\n";
        continue;
      }

      auto [solution, duration] =
          runningTime([&solver, &data] { return solver->solve(data.shuriken, data.solutionSize()); });

      if (data.isSolution(solution)) {
        cout << "Shuriken: " << solver->name << " solved " << data.name << ", it took about " << duration
             << " microseconds!\n";
      } else {
        cout << "Shuriken: " << solver->name << " solver failed to solve " << data.name
             << ", was expecting one of these:\n";
        for (auto &expected : data.solutions) {
          logger.log(expected);
        }
        cout << "Shuriken: But got this:\n";
        logger.log(solution);
        allSuccess = false;
      }
    }
  }

  return allSuccess;
}

bool Shurikens::run(bool fullRun) {
  return runSolvers(fullRun);
}
