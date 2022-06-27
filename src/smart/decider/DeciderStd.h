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
#ifndef DECIDER_VEHICULARAPP_STD_H_
#define DECIDER_VEHICULARAPP_STD_H_

#include <string>
#include <vector>

using namespace std;

/** @brief Vehicular Application data types */
typedef vector<vector<string>> dataframe;
typedef vector<string> svector;
typedef vector<int64_t> ivector;
typedef vector<float> fvector;

/** @brief Check if the string value is a number */
bool isNumber(string value);

/** @brief Object instance check */
template<typename Base, typename T>
inline bool instanceof(const T *ptr) {
   return dynamic_cast<const Base*>(ptr) != nullptr;
}

#endif /* DECIDER_VEHICULARAPP_STD_H_ */
