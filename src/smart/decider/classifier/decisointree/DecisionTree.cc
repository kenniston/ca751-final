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

#include <math.h>
#include <iostream>

#include "DecisionTree.h"

namespace decisiontree {

    using namespace std;

    /**
     * General Decision Tree initialization and training.
     *
     * @param df Decision Tree training dataframe.
     */
    void DecisionTree::initialize(vector<vector<string>> df, svector header, int classColumn)
    {
        this->data = df;
        this->header = header;
        this->classColumn = classColumn;
    }

    /**
     * Returns a class-count map from a dataframe.
     *
     * @param df Dataframe with rows and columns.
     * @param column Class column in the dataframe.
     * @return A map with class count.
     */
    map<string, int> DecisionTree::labelCount(dataframe df, int column)
    {
        map<string, int> result;
        svector columnRows = getColumn(df, column);
        for (string value : columnRows) {
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
     * @param df Dataframe with rows and columns.
     * @param index Index for a column in the dataframe.
     * @return A column vector.
     */
    svector DecisionTree::getColumn(dataframe df, int index)
    {
        svector column;
        for (svector row : df) {
            column.push_back(row[index]);
        }
        return column;
    }

    /**
     * Return a unique values for a column in the dataframe.
     *
     * @param dataframe Dataframe with rows and columns.
     * @param column Index for label column in dataframe.
     * @return A set of unique values from the label column in the dataframe.
     */
    set<string> DecisionTree::uniqueValues(dataframe df, int column)
    {
        set<string> result;
        for (svector row : df) {
            result.insert(row[column]);
        }
        return result;
    }

    /**
     * Partitions a dataset.
     * For each row in the dataset, check if it matches the question.
     * If so, add it to 'true rows', otherwise, add it to 'false rows'.
     *
     * @param df Dataframe with rows and columns.
     * @param question The question to match.
     * @return A tuple with true and false rows.
     */
    tuple<dataframe, dataframe> DecisionTree::partition(dataframe df, shared_ptr<Question> question)
    {
        dataframe trueRows;
        dataframe falseRows;

        for (svector row : df) {
            if (question->match(row)) {
                trueRows.push_back(row);
            } else {
                falseRows.push_back(row);
            }
        }
        return tuple<dataframe, dataframe>{ trueRows, falseRows };
    }

    /**
     * Calculate the Gini Impurity for dataframe.
     *
     * @param df Dataframe with rows and columns.
     * @param column Index for label column in dataframe.
     * @return Dataframe Gini impurity value.
     */
    double DecisionTree::gini(dataframe df, int column)
    {
        auto count = labelCount(df, column);
        double impurity = 1;
        for (auto m : count) {
            double labelProbability = (double) m.second / df.size();
            impurity -= pow(labelProbability, 2);
        }
        return impurity;
    }

    /**
     * Information Gain.
     * The uncertainty of the starting node, minus the weighted impurity of
     * two child nodes.
     *
     * @param left  Left dataframe with rows and columns.
     * @param right Right dataframe with rows and columns.
     * @param column Index for label column in dataframe.
     * @return Information gain value.
     */
    double DecisionTree::infoGain(dataframe left, dataframe right, int column, double uncertainty)
    {
        double p = (double) left.size() / (left.size() + right.size());
        return uncertainty - p * gini(left, column) - (1 - p) * gini(right, column);
    }

    /**
     * Find the best question and information gain
     *
     * @param df Dataframe with rows and columns.
     * @param labelColumn Index for label column in dataframe.
     * @return The best question and the best information gain.
     */
    tuple<double, shared_ptr<Question>> DecisionTree::findBestSplit(dataframe df, int labelColumn)
    {
        double bestGain = 0;
        shared_ptr<Question> bestQuestion;

        // Calculate the uncertainty of the dataframe
        double uncertainty = gini(df, labelColumn);

        // Get the dataframe column count
        int columnCount = df[0].size();

        // Search for the best question and best gain in
        // all columns of the dataframe
        for (int col = 0; col < columnCount; col++) {
            // Get unique values from each column to create a question
            auto values = uniqueValues(df, col);

            // Search for the best question and information
            // gain from unique values
            for (auto val : values) {
                auto question = make_shared<Question>(col, val, header[col]);
                auto part = partition(df, question);

                // Ignore this question if it doesn't divide the dataframe
                if (get<0>(part).size() == 0 || get<1>(part).size() == 0) {
                    continue;
                }

                // Calculate the information gain from this split
                double gain = infoGain(get<0>(part), get<1>(part), col, uncertainty);
                if (gain >= bestGain) {
                    bestGain = gain;
                    bestQuestion = question;
                }
            }
        }

        return tuple<double, shared_ptr<Question>>{ bestGain, bestQuestion };
    }

} // namespace decisiontree


int main() {
    using namespace decisiontree;

    dataframe df = {
        {"Green", "3", "Apple"},
        {"Yellow", "3", "Apple"},
        {"Red", "1", "Grape"},
        {"Red", "1", "Grape"},
        {"Yellow", "3", "Lemon"}
    };

    // Initialize test
    unique_ptr<DecisionTree> d = make_unique<DecisionTree>();
    d->initialize(df, {"color", "diameter", "label"}, 2);

    // Target count test
    map<string, int>::iterator itr;
    map<string, int> m = d->labelCount(df, 2);
    for (itr = m.begin(); itr != m.end(); ++itr) {
        cout << itr->first << ": " << itr->second << "\n";
    }

    // isNumber Tests
    cout << "3 is a number? " << isNumber("3") << "\n";
    cout << "Apple is a number? " << isNumber("Apple") << "\n";

    // Question tests
    auto q1 = Question(1, "3", "diameter");
    cout << q1.to_string();
    auto q2 = Question(0, "Green", "color");
    cout << q2.to_string();

    svector row = df[0];
    cout << "Q2 Match (color == Green) => " << q2.match(row) << "\n==============\n";

    // Partition test
    shared_ptr<Question> q3 = make_shared<Question>(0, "Red", "color");
    cout << q3->to_string();
    auto part = d->partition(df, q3);
    // Print all Red rows
    cout << "Red rows: \n";
    for (auto row : get<0>(part)){
        cout << "  [";
        for (auto col = row.begin(); col != row.end(); ++col) {
            cout << *col;
            if (col+1 != row.end()) cout << ",";
        }
        cout << "]\n";
    }
    cout << "Other rows: \n";
    for (auto row : get<1>(part)){
        cout << "  [";
        for (auto col = row.begin(); col != row.end(); ++col) {
            cout << *col;
            if (col+1 != row.end()) cout << ",";
        }
        cout << "]\n";
    }

    // Gini tests
    dataframe noMixing = {
        {"Green", "3", "Apple"},
        {"Yellow", "3", "Apple"},
    };
    cout << "noMixing Gini: " << d->gini(noMixing, 2) << "\n";

    dataframe someMixing = {
       {"Green", "3", "Apple"},
       {"Red", "1", "Grape"},
    };
    cout << "someMixing Gini: " << d->gini(someMixing, 2) << "\n";

    dataframe lotsOfMixing = {
       {"Green", "3", "Apple"},
       {"Orange", "1", "Orange"},
       {"Red", "1", "Grape"},
       {"Yellow", "1", "Grapefruit"},
       {"Blue", "1", "Blueberry"},
    };
    cout << "lotsOfMixing Gini: " << d->gini(lotsOfMixing, 2) << "\n";

    // Information Gain tests
    double uncertainty = d->gini(df, 2);
    cout << "current uncertainty: " << uncertainty << "\n";

    shared_ptr<Question> q4 = make_shared<Question>(0, "Green", "color");
    auto gpart = d->partition(df, q4);
    double greenGain = d->infoGain(get<0>(gpart), get<1>(gpart), 2, uncertainty);
    cout << "Green Gain: " << greenGain << "\n";

    shared_ptr<Question> q5 = make_shared<Question>(0, "Red", "color");
    auto rpart = d->partition(df, q5);
    double redGain = d->infoGain(get<0>(rpart), get<1>(rpart), 2, uncertainty);
    cout << "Red Gain: " << redGain << "\n";

    // Best split test
    auto spart = d->findBestSplit(df, 2);
    cout << "Best Question: \n";
    cout << get<1>(spart)->to_string();

    return 0;
}
