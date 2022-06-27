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
// @date    26/06/2022
// @version 1.0
//
#ifndef CLASSIFIER_DECISOINTREE_LEAF_H_
#define CLASSIFIER_DECISOINTREE_LEAF_H_

#include <map>

#include "../decisiontree/Node.h"

namespace decisiontree {
    using namespace std;

    /**
     * @brief
     * A Leaf node classifies data.
     * This holds a dictionary of class -> number of times
     * it appears in the rows from the training data that
     * reach this leaf.
     *
     * @author Kenniston Arraes Bonfim
     * @ingroup DecisionTree
     * @see DecisionTree
     */
    class Leaf: public INode {
    public:
        /** @brief Leaf construction with predictions map */
        Leaf(map<string, int> predictions);

        /** @brief Return predictions from this leaf */
        map<string, int> getPredictions();
    protected:
        /** @brief Predictions of this node */
        map<string, int> predictions;
    };

} // namespace decisiontree

#endif /* CLASSIFIER_DECISOINTREE_LEAF_H_ */
