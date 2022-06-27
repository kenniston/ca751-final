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
#ifndef CLASSIFIER_DECISOINTREE_DECISIONNODE_H_
#define CLASSIFIER_DECISOINTREE_DECISIONNODE_H_

#include <string>
#include <memory>

#include "../decisiontree/Node.h"
#include "../decisiontree/Question.h"

namespace decisiontree {
    using namespace std;

    /**
     * @brief
     * A Decision Node asks a question.
     * This holds a reference to the question, and to the
     * two child nodes.
     *
     * @author Kenniston Arraes Bonfim
     * @ingroup DecisionTree
     * @see DecisionTree
     */
    class DecisionNode: public INode {
    public:
        /** @brief DecisionNode constructor with a question and two branchs (true and false answers to the question) */
        DecisionNode(shared_ptr<Question> question, shared_ptr<INode> trueBranch, shared_ptr<INode> falseBranch);

        /** @brief The question for this decision node in the tree */
        shared_ptr<Question> question;

        /** @brief The 'true' child for this decision node in the tree */
        shared_ptr<INode> trueBranch;

        /** @brief The 'false' child for this decision node in the tree */
        shared_ptr<INode> falseBranch;
    };

} // namespace decisiontree

#endif /* CLASSIFIER_DECISOINTREE_DECISIONNODE_H_ */
