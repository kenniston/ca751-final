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

#include "Question.h"
#include "../../DeciderStd.h"

namespace decisiontree {

    using namespace std;

    /**
     * @brief
     * Decison Tree Class
     *
     * @author Kenniston Arraes Bonfim
     *
     * @ingroup DecisionTree
     */
    class DecisionTree {
    public:
        /** brief Decision Tree destructor */
        virtual ~DecisionTree() = default;

        /** @brief General Decision Tree initialization */
        virtual void initialize(dataframe df, svector header, int classColumn);

        /** @brief Returns a class-count map from a dataframe **/
        virtual map<string, int> labelCount(dataframe df, int column);

        /** @brief Return a unique values for a column in the dataframe */
        virtual set<string> uniqueValues(dataframe df, int column);

        /** @brief Return a dataframe column */
        virtual svector getColumn(dataframe df, int index);

        /** @brief For each row in the dataset, check if it matches the question */
        virtual tuple<dataframe, dataframe> partition(dataframe df, shared_ptr<Question> question);

        /** @brief Calculate the Gini Impurity for dataframe */
        virtual double gini(dataframe df, int column);

        /** @brief Information Gain from a column */
        virtual double infoGain(dataframe left, dataframe right, int column, double uncertainty);

        /** @brief Find the best question and information gain */
        virtual tuple<double, shared_ptr<Question>> findBestSplit(dataframe df, int labelColumn);

    protected:
        /** @brief The training dataframe */
        dataframe data;

        /** @brief Dataframe header */
        svector header;

        /** @brief ID for the class column in dataframe */
        int classColumn;
    };

} // namespace decisiontree

#endif /* CLASSIFIER_DECISIONTREE_H_ */
