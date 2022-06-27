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

#include "../decisiontree/Question.h"

#include <string>
#include <sstream>


namespace decisiontree {

    using namespace std;

    /**
     * Decision Tree Question Constructor with column
     * index and column value.
     *
     * @param column The column index for this question.
     * @param value The column value for this question.
     * @param name The name of this question.
     */
    Question::Question(int column, string value, string name)
    {
        this->column = column;
        this->value = value;
        this->name = name;
    }

    /**
     * Compare the feature value in an row to the feature
     * value in this question.
     *
     * @param row The row from dataframe to test.
     * @return A boolean value for the equality of the row
     *         value and the question value.
     */
    bool Question::match(svector row)
    {
        string val = row[column];
        if (isNumber(val)) {
            double v1 = stod(val);
            double v2 = stod(value);
            return v1 >= v2;
        } else {
            return val == value;
        }
    }

    /**
     * Return a question information string.
     */
    string Question::to_string()
    {
        stringstream out;
        string condition = "==";
        if (isNumber(value)) condition = ">=";
        out << "Is " << name << " " << condition << " " << value << "?";
        return out.str();
    }

} // namespace decisiontree

