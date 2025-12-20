/*
 * Yarrboard Framework
 *
 * Copyright (c) 2025 Zach Hoeken <hoeken@gmail.com>
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#include "utility.h"

double round2(double value)
{
  return (long)(value * 100 + 0.5) / 100.0;
}

double round3(double value)
{
  return (long)(value * 1000 + 0.5) / 1000.0;
}

double round4(double value)
{
  return (long)(value * 10000 + 0.5) / 10000.0;
}