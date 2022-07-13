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
#include <sstream>
#include <numeric>
#include <iostream>

#include "DecisionTree.h"
#include "../decisiontree/Leaf.h"
#include "../decisiontree/DecisionNode.h"

using namespace decisiontree;

int main2() {

    dataframe df = {
        {"Green", "3", "Apple"},
        {"Yellow", "3", "Apple"},
        {"Red", "1", "Grape"},
        {"Red", "1", "Grape"},
        {"Yellow", "3", "Lemon"}
    };

    int labelColumn = 2;

    // Initialize test
    unique_ptr<DecisionTree> d = make_unique<DecisionTree>();
    d->initialize(df, {"color", "diameter", "label"}, labelColumn);

    // Target count test
    map<string, int>::iterator itr;
    map<string, int> m = d->labelCount(df, labelColumn);
    for (itr = m.begin(); itr != m.end(); ++itr) {
        cout << itr->first << ": " << itr->second << endl;
    }

    // isNumber Tests
    cout << "3 is a number? " << isNumber("3") << endl;
    cout << "Apple is a number? " << isNumber("Apple") << endl;

    // Question tests
    auto q1 = Question(1, "3", "diameter");
    cout << q1.to_string() << endl;
    auto q2 = Question(0, "Green", "color");
    cout << q2.to_string() << endl;

    svector row = df[0];
    cout << "Q2 Match (color == Green) => " << q2.match(row) << endl << "==============" << endl;

    // Partition test
    shared_ptr<Question> q3 = make_shared<Question>(0, "Red", "color");
    cout << q3->to_string() << endl;
    auto part = d->partition(df, q3);
    // Print all Red rows
    cout << "Red rows:" << endl;
    for (auto row : get<0>(part)){
        cout << "  [";
        for (auto col = row.begin(); col != row.end(); ++col) {
            cout << *col;
            if (col+1 != row.end()) cout << ",";
        }
        cout << "]" << endl;
    }
    cout << "Other rows:" << endl;
    for (auto row : get<1>(part)){
        cout << "  [";
        for (auto col = row.begin(); col != row.end(); ++col) {
            cout << *col;
            if (col+1 != row.end()) cout << ",";
        }
        cout << "]" << endl;
    }

    // Gini tests
    dataframe noMixing = {
        {"Green", "3", "Apple"},
        {"Yellow", "3", "Apple"},
    };
    cout << "noMixing Gini: " << d->gini(noMixing, labelColumn) << endl;

    dataframe someMixing = {
       {"Green", "3", "Apple"},
       {"Red", "1", "Grape"},
    };
    cout << "someMixing Gini: " << d->gini(someMixing, labelColumn) << endl;

    dataframe lotsOfMixing = {
       {"Green", "3", "Apple"},
       {"Orange", "1", "Orange"},
       {"Red", "1", "Grape"},
       {"Yellow", "1", "Grapefruit"},
       {"Blue", "1", "Blueberry"},
    };
    cout << "lotsOfMixing Gini: " << d->gini(lotsOfMixing, labelColumn) << endl;

    // Information Gain tests
    double uncertainty = d->gini(df, labelColumn);
    cout << "current uncertainty: " << uncertainty << endl;

    shared_ptr<Question> q4 = make_shared<Question>(0, "Green", "color");
    auto gpart = d->partition(df, q4);
    double greenGain = d->infoGain(get<0>(gpart), get<1>(gpart), labelColumn, uncertainty);
    cout << "Green Gain: " << greenGain << endl;

    shared_ptr<Question> q5 = make_shared<Question>(0, "Red", "color");
    auto rpart = d->partition(df, q5);
    double redGain = d->infoGain(get<0>(rpart), get<1>(rpart), labelColumn, uncertainty);
    cout << "Red Gain: " << redGain << endl;

    // Best split test
    auto spart = d->findBestSplit(df, labelColumn);
    cout << "Best Question:" << endl;
    cout << get<1>(spart)->to_string() << endl;

    // Build tree and print test
    d->build(df, labelColumn);
    cout << "==============" << endl;
    cout << "Tree:" << endl;
    cout << d->str();

    // Classify test
    cout << "==============" << endl;
    cout << "Prediction for df[0]:" << endl;
    auto predictions = d->classify(df[1]);
    cout << "Predict {";
    for (auto itr = predictions.begin(); itr != predictions.end(); ++itr) {
        cout << "'" << itr->first << "': " << itr->second * 100 << "%";
        if (next(itr) != predictions.end()) {
            cout << ", ";
        }
    }
    cout << "}" << endl;

    // Test Dataframe
    cout << "==============" << endl;
    cout << "Test Dataframe:" << endl;
    dataframe testdf = {
        {"Green", "3", "Apple"},
        {"Yellow", "4", "Apple"},
        {"Red", "2", "Grape"},
        {"Red", "1", "Grape"},
        {"Yellow", "3", "Lemon"}
    };
    for (auto row : testdf) {
        auto predictions = d->classify(row);
        cout << "Actual: " << row[2] << ". ";
        cout << "Predicted {";
        for (auto itr = predictions.begin(); itr != predictions.end(); ++itr) {
            cout << "'" << itr->first << "': " << itr->second * 100 << "%";
            if (next(itr) != predictions.end()) {
                cout << ", ";
            }
        }
        cout << "}" << endl;
    }

    return 0;
}
