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
#ifndef CLASSIFIER_DECISOINTREE_QUESTION_H_
#define CLASSIFIER_DECISOINTREE_QUESTION_H_

#include <string>

#include "../../DeciderStd.h"

namespace decisiontree {
    using namespace std;

    /**
     * @brief
     * A Question is used to partition a dataframe.
     * This class just records a column number and a column value.
     * The 'match' method is used to compare the feature value in
     * an example to the feature value stored in the question.
     *
     * @author Kenniston Arraes Bonfim
     *
     * @ingroup DecisionTree
     *
     * @see DecisionTree
     */
    class Question {
    public:
        /** @brief Question Constructor with column index and column value */
        Question(int column, string value, string name);

        /** @brief Question Destructor */
        virtual ~Question() = default;

        /** @brief Compare the feature value in an row to the feature value in this question */
        virtual bool match(svector row);

        /** @brief Return a question information string */
        virtual string to_string();

    protected:
        /** @brief Column index for this question in dataframe */
        int column;

        /** @brief Column value for this question in dataframe */
        string value;

        /** @brief The name of question */
        string name;
    };

} // namespace decisiontree

#endif /* CLASSIFIER_DECISOINTREE_QUESTION_H_ */
