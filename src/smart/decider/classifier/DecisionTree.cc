//
// Copyright (C) 2022 Kenniston Arraes Bonfim <kenniston@gmail.com>
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
// @date    19/06/2022
// @version 1.0
//

#include <iostream>
#include "DecisionTree.h"

using namespace std;

/**
 * General Decision Tree initialization and training.
 *
 * @param df Decision Tree training dataframe.
 */
void DecisionTree::initialize(vector<vector<string>> df, int classColumn)
{
    this->classColumn = classColumn;
    this->dataset = df;
}

/**
 * Destructor used to free allocated memory.
 */
DecisionTree::~DecisionTree()
{

}

/**
 * Returns a class-count map from a dataset
 *
 * @param rows Rows from the dataset class column.
 * @return A map with class count.
 */
map<string, int> DecisionTree::targetCount(vector<string> rows) {
    map<string, int> result;

    for (string row : rows) {
        auto label = result.find(row);
    }
}

int main() {
    vector<string> rows = {"Apple", "Apple", "Orange", "Melon", "Orange"};
    set<string> unique(rows.begin(), rows.end());

    for (string s : unique) {
        cout << s << " ";
    }

    return 0;
}
