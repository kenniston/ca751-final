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

#ifndef APP_VEHICULAR_DECIDER_H_
#define APP_VEHICULAR_DECIDER_H_

#include <string>
#include <vector>
#include "classifier/DecisionTree.h"

using namespace std;

class VehicularAppDecider {
public:
    virtual ~VehicularAppDecider();

    /** @brief General Decider initialization function */
    void initialize(string dataFrameFile, vector<int64_t> filterColumns, bool header, int labelColumn);

protected:
    /** @brief Decision Tree Classifier */
    DecisionTree* treeClassifier;

    /** @brief Load the Dataframe from a CSV file */
    vector<vector<string>> loadDataframe(string filename, vector<int64_t> filterColumns, bool header, int labelColumn);
};

#endif /* APP_VEHICULAR_DECIDER_H_ */