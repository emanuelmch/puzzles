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

#include "common/strings.h"

#include <gtest/gtest.h>

using namespace pzl;

TEST(Strings, PadLeading) {
  EXPECT_EQ(padLeading("", 8, '0'), "00000000");
  EXPECT_EQ(padLeading("1234", 8, '0'), "00001234");
  EXPECT_EQ(padLeading("12345678", 8, '0'), "12345678");
  EXPECT_EQ(padLeading("123456789", 8, '0'), "123456789");
}

TEST(Strings, TrimLeading) {
  EXPECT_EQ(trimLeadingView(" test", ' '), "test");
  EXPECT_EQ(trimLeadingView(" test", 't'), " test");

  EXPECT_EQ(trimLeadingView("rrr", 'r'), "");
  EXPECT_EQ(trimLeadingView("rrr", ' '), "rrr");
}

TEST(Strings, TrimLeadingView) {
  std::string simple = " test";
  EXPECT_EQ(trimLeadingView(simple, ' '), "test");
  EXPECT_EQ(trimLeadingView(simple, 't'), " test");

  std::string repeat = "rrr";
  EXPECT_EQ(trimLeadingView(repeat, 'r'), "");
  EXPECT_EQ(trimLeadingView(repeat, ' '), "rrr");
}

TEST(Strings, ToString) {
  EXPECT_EQ(pzl::toString(0), "0");
  EXPECT_EQ(pzl::toString(1), "1");
  EXPECT_EQ(pzl::toString(9), "9");
  EXPECT_EQ(pzl::toString(10), "10");
  EXPECT_EQ(pzl::toString(99), "99");
  EXPECT_EQ(pzl::toString(1000000), "1000000");

  static_assert(std::numeric_limits<uint32_t>::max() == 4294967295U); // NOLINT(readability-magic-numbers)
  EXPECT_EQ(pzl::toString(8461339), "8461339");
  EXPECT_EQ(pzl::toString(75400661), "75400661");
  EXPECT_EQ(pzl::toString(486977962), "486977962");
  EXPECT_EQ(pzl::toString(4294967295), "4294967295");
}
