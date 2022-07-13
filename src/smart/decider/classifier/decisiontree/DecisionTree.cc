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

#include "../decisiontree/DecisionTree.h"

#include <math.h>
#include <sstream>
#include <numeric>
#include <iostream>

#include "DecisionTree.h"
#include "../decisiontree/Leaf.h"
#include "../decisiontree/DecisionNode.h"

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
            // Check for label column
            if (col == labelColumn) continue;

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

    /**
     * Builds the tree based on dataframe information (gain and questions)
     *
     * @param df Dataframe with rows and columns.
     * @param labelColumn Index for label column in dataframe.
     */
    void DecisionTree::build(dataframe df, int labelColumn)
    {
        root = buildTree(df, labelColumn);
    }

    /**
     * Builds the tree based on dataframe information (gain and questions)
     *
     * @param df Dataframe with rows and columns.
     * @param labelColumn Index for label column in dataframe.
     * @return A tree root node.
     */
    shared_ptr<INode> DecisionTree::buildTree(dataframe df, int labelColumn)
    {
        // Try partitioing the dataset on each of the unique attribute,
        // calculate the information gain, and return the question that
        // produces the highest gain.
        auto spart = findBestSplit(df, labelColumn);
        double gain = get<0>(spart);
        shared_ptr<Question> question = get<1>(spart);

        // Base case: no further info gain.
        // Since there is no further questions, return a leaf.
        if (gain == 0) {
            map<string, int> counts = labelCount(df, labelColumn);
            return dynamic_pointer_cast<INode>(make_shared<Leaf>(counts));
        }

        // If reach here, it has a useful feature/value to partition on.
        auto dpart = partition(df, question);

        // Recursively build the 'true' branch.
        shared_ptr<INode> trueBranch = buildTree(get<0>(dpart), labelColumn);

        // Recursively build the 'false' branch.
        shared_ptr<INode> falseBranch = buildTree(get<1>(dpart), labelColumn);

        // Return a Decision Node with a question.
        // This records the best feature/value to ask at this point,
        // as well as the branches for the question (answers).
        return dynamic_pointer_cast<INode>(make_shared<DecisionNode>(question, trueBranch, falseBranch));
    }

    /**
     * Return a string with tree structure
     */
    string DecisionTree::str()
    {
        return to_string(root);
    }

    /**
     * Return a string with node structure
     */
    string DecisionTree::to_string(shared_ptr<INode> node, string spacing)
    {
        stringstream out;

        // Leaf node with predictions
        if (shared_ptr<Leaf> leaf = dynamic_pointer_cast<Leaf>(node)) {
            out << spacing << "Predict {";
            auto predictions = leaf->getPredictions();
            for (map<string, int>::iterator itr = predictions.begin(); itr != predictions.end(); ++itr) {
                out << "'" << itr->first << "': " << itr->second;
                if (next(itr) != predictions.end()) {
                    out << ", ";
                }
            }
            out << "}" << endl;
            return out.str();
        } else if (shared_ptr<DecisionNode> dnode = dynamic_pointer_cast<DecisionNode>(node)) {
            // Question information from Decision Node
            out << spacing << dnode->question->to_string() << endl;

            // 'True' branch for this node
            out << spacing << "--> True:" << endl;
            out << to_string(dnode->trueBranch, spacing + "  ");

            out << spacing << "--> False:" << endl;
            out << to_string(dnode->falseBranch, spacing + "  ");
        }

        return out.str();
    }

    /**
     * Classify the input data.
     *
     * @param data A vector with columns to classify.
     * @return A map with the prediction result.
     */
    map<string, float> DecisionTree::classify(svector data)
    {
        return classifyData(data, root);
    }

    /**
     * Classify the input data into the tree.
     *
     * @param data A vector with columns to classify.
     * @param node A node (leaf or decision node) to validade.
     * @return A map with the label and percentage of prediction for each label.
     */
    map<string, float> DecisionTree::classifyData(svector data, shared_ptr<INode> node)
    {
        if (shared_ptr<Leaf> leaf = dynamic_pointer_cast<Leaf>(node)) {
            // Calculate the percentage of each label
            auto predictions = leaf->getPredictions();
            map<string, float> result;

            // Calculate the total of items for this prediction
            float total = accumulate(predictions.begin(), predictions.end(), 0,
                    [](auto sum, auto &item){ return sum + item.second; });
            for (auto itr = predictions.begin(); itr != predictions.end(); ++itr) {
                result[itr->first] = itr->second / total;
            }
            return result;
        } else {
            shared_ptr<DecisionNode> dnode = dynamic_pointer_cast<DecisionNode>(node);
            if (dnode->question->match(data)) {
                return classifyData(data, dnode->trueBranch);
            } else {
                return classifyData(data, dnode->falseBranch);
            }
        }
    }

} // namespace decisiontree

