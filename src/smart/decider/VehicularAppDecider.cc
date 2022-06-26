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

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "VehicularAppDecider.h"

using namespace std;

/**
 * General Decider Setup.
 *
 * @param dataFrameFile Filename of Dataframe to load data.
 * @param filter Dataframe column filter.
 * @param labelColumn Index for label column in dataframe.
 */
void VehicularAppDecider::initialize(string dataFrameFile, ivector filter, int labelColumn)
{
    if (dataFrameFile.empty()) {
        return;
    }

    // Loads the training dataframe.
    auto res = loadDataframe(dataFrameFile, filter, labelColumn);

    // Initialize the
    treeClassifier = make_unique<DecisionTree>();
    treeClassifier->initialize(get<0>(res), get<1>(res), labelColumn);
}

/**
 * Load the Dataframe from a CSV file.
 * The first line should be the dataframe header.
 *
 * @param filename Filename of Dataframe to load.
 * @param filter Dataframe column filter.
 * @param labelColumn Index for label column in dataframe.
 * @return A tuple with loaded dataframe and header vector.
 */
tuple<dataframe, svector> VehicularAppDecider::loadDataframe(string filename,
    ivector filter, int labelColumn)
{
    dataframe result;
    svector header;
    string line;
    ifstream infile(filename);

    int row = 0;
    while (getline(infile, line)) {
        int col = 0;
        string token;
        svector columns;
        stringstream strstream(line);
        while (getline(strstream, token, ',')) { // Parse columns
            if (!filter.empty()) {
                if (find(filter.begin(), filter.end(), col) != filter.end()) {
                    if (row == 0) columns.push_back(token); else header.push_back(token);
                }
            } else {
                if (row == 0) columns.push_back(token); else header.push_back(token);
            }
            col++;
        }
        result.push_back(columns);
        row++;
    }

    return tuple<dataframe, svector>{result, header};
}
