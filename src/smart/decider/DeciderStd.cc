//
// Copyright (C) 2022 kenniston <>
//
// SPDX-License-Identifier: GPL-2.0-or-later
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// @author  Kenniston Arraes Bonfim
// @email   kenniston@gmail.com
// @date    25/06/2022
// @version 1.0
//

#include <algorithm>

#include "DeciderStd.h"

using namespace std;

/**
 * Check if the string value is a number.
 * @param value String to check the value.
 */
bool isNumber(string value) {
     return !value.empty() && std::find_if(value.begin(), value.end(),
             [](unsigned char c) { return !std::isdigit(c); }) == value.end();
}

