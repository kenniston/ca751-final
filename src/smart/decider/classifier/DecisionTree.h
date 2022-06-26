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
#include <memory>
#include "../VehicularAppStd.h"

using namespace std;

/**
 * @brief
 * Decison Tree Class
 */
class DecisionTree {
public:
    /**
     * @brief
     * A Question is used to partition a dataframe.
     * This class just records a column number and a column value.
     * The 'match' method is used to compare the feature value in
     * an example to the feature value stored in the question.
     */
    class Question {
    public:
        /** @brief Question Constructor with column index and column value */
        Question(int column, string value, string name);

        /** @brief Question Destructor */
        virtual ~Question() = default;

        /** @brief Compare the feature value in an row to the feature value in this question */
        virtual bool match(svector row);

        /** @brief Print the question */
        virtual void print();

    protected:
        /** @brief Column index for this question in dataframe */
        int column;

        /** @brief Column value for this question in dataframe */
        string value;

        /** @brief The name of question */
        string name;
    };

    /** brief Decision Tree destructor */
    virtual ~DecisionTree() = default;

    /** @brief General Decision Tree initialization */
    virtual void initialize(dataframe df, svector header, int classColumn);

    /** @brief Returns a class-count map from a dataframe **/
    virtual map<string, int> targetCount(dataframe df, int target);

    /** @brief Return a unique values for a column in the dataframe */
    virtual set<string> uniqueValues(dataframe df, int target);

    /** @brief Return a dataframe column */
    virtual svector getColumn(dataframe df, int index);

    /** @brief For each row in the dataset, check if it matches the question */
    virtual tuple<dataframe, dataframe> partition(dataframe df, shared_ptr<DecisionTree::Question> question);

    /** @brief Calculate the Gini Impurity for dataframe */
    virtual double gini(dataframe df, int target);

    /** @brief Information Gain */
    virtual double infoGain(dataframe left, dataframe right, int target, double uncertainty);

    /** @brief Find the best question and information gain */
    virtual tuple<double, shared_ptr<DecisionTree::Question>> findBestSplit(dataframe df, int target);

protected:
    /** @brief The training dataframe */
    dataframe data;

    /** @brief Dataframe header */
    svector header;

    /** @brief ID for the class column in dataframe */
    int classColumn;
};

#endif /* CLASSIFIER_DECISIONTREE_H_ */
