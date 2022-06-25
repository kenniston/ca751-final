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
#include <algorithm>
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
    this->dataframe = df;
}

/**
 * Destructor used to free allocated memory.
 */
DecisionTree::~DecisionTree()
{

}

/**
 * Returns a class-count map from a dataframe
 *
 * @return A map with class count.
 */
map<string, int> DecisionTree::targetCount() {
    map<string, int> result;

    vector<string> column = getColumn(classColumn);
    for (string value : column) {
        auto idx = result.find(value);
        if (idx == result.end()) {
            result[value] = 0;
        }
        result[value] += 1;
    }

    return result;
}

/**
 * Return a dataframe column.
 *
 * @param index Index for a column in the dataframe
 * @return A column vector
 */
vector<string> DecisionTree::getColumn(int index){
    vector<string> column;

    for (vector<string> row : dataframe) {
        column.push_back(row[index]);
    }

    return column;
}


/**
 * Return a unique values for a column in the dataframe.
 *
 * @param dataframe Dataframe with rows and columns.
 * @param labelColum Index for label column in dataframe
 * @return A set of unique values from the label column in the dataframe.
 */
set<string> DecisionTree::uniqueValues() {
    set<string> result;
    for (vector<string> row : dataframe) {
        result.insert(row[classColumn]);
    }
    return result;
}

/**
 * Check if the string value is a number
 *
 * @param value String to check the value
 */
bool DecisionTree::isNumber(string value) {
     return !value.empty() && std::find_if(value.begin(), value.end(),
             [](unsigned char c) { return !std::isdigit(c); }) == value.end();
}

/**
 * Decision Tree Question Constructor with column
 * index and column value.
 *
 * @param column The column index for this question
 * @param value The column value for this question
 */
DecisionTree::Question::Question(int column, string value) {
    this->column = column;
    this->value = value;
}

/**
 * Compare the feature value in an row to the feature
 * value in this question
 *
 * @param row The row from dataframe to test
 * @return A boolean value for the equality of the row
 *         value and the question value
 */
bool DecisionTree::Question::match(vector<string> row) {
    string val = row[column];
    if (isNumber(val)) {
        int v1 = atof(value);
        int v2 = atof(val);
        return v1 >= v2;
    } else {
        return val == value;
    }
}

/** @brief Print the question */
void DecisionTree::Question::print() {

    cout << "Example value "
}

#include <set>
int main() {
    vector<vector<string>> dataframe = {
        {"Green", "3", "Apple"},
        {"Yellow", "3", "Apple"},
        {"Red", "1", "Grape"},
        {"Red", "1", "Grape"},
        {"Yellow", "3", "Lemon"}
    };

    DecisionTree *d = new DecisionTree();
    d->initialize(dataframe, 2);

    map<string, int>::iterator itr;
    map<string, int> m = d->targetCount();
    for (itr = m.begin(); itr != m.end(); ++itr) {
        cout << itr->first << ": " << itr->second << "\n";
    }

    cout << "3 is a number? " << d->isNumber("3") << "\n";
    cout << "Apple is a number? " << d->isNumber("Apple") << "\n";

    delete d;


    return 0;
}
