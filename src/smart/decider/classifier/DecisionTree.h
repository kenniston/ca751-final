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

#ifndef CLASSIFIER_DECISIONTREE_H_
#define CLASSIFIER_DECISIONTREE_H_

#include <set>
#include <map>
#include <string>
#include <vector>

using namespace std;

/**
 * @brief
 * Decison Tree Class
 */
class DecisionTree {

    /**
     * @brief
     * A Question is used to partition a dataframe.
     * This class just records a column number and a column value.
     * The 'match' method is used to compare the feature value in
     * an example to the feature value stored in the question.
     */
    class Question {

    };

public:
    virtual ~DecisionTree();

    /** @brief General Decision Tree initialization */
    virtual void initialize(vector<vector<string>> df, int classColumn);

    /** @brief Returns a class-count map from a dataframe **/
    virtual map<string, int> targetCount();

    /** @brief Return a unique values for a column in the dataframe */
    virtual set<string> uniqueValues();

    /** @brief Return a dataframe column */
    virtual vector<string> getColumn(int index);

    /** @brief Check if the string value is a number */
    bool isNumber(string value);

protected:
    /** @brief The training dataframe */
    vector<vector<string>> dataframe;

    /** @brief ID for the class column in dataframe */
    int classColumn;
};

#endif /* CLASSIFIER_DECISIONTREE_H_ */
