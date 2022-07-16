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
// @date    28/06/2022
// @version 1.0
//
#include <algorithm>
#include "Knn.h"

namespace knn {

    /**
     * General KNN initialization and training.
     *
     * @param df KNN training dataframe.
     */
    void Knn::initialize(dataframe df, svector header, int classColumn, int K)
    {
        this->data = df;
        this->header = header;
        this->classColumn = classColumn;
        this->K = K;
    }

    /**
     * Classify the input data.
     *
     * @param data A vector with columns to classify.
     * @return A tuple with the predicted class and dataframe
     *         index of predicted class.
     */
    tuple<string, int> Knn::classify(svector sample) {
        vector<pair<double, int>> squaredDistances(sample.size());

        for (int i = 0; i < data.size(); i++) {
            double sum = 0;
            for (int j = 0; j < sample.size(); j++) {
                double v1 = stod(sample[j]);
                double v2 = stod(data[i][j]);
                double diff = v1 - v2;
                sum += diff * diff;
            }
            squaredDistances[i].first = sum;
            squaredDistances[i].second = i;
        }

        std::sort(squaredDistances.begin(), squaredDistances.end());

        double result = -1;
        int idx = 0;
        for (int i = 0; i < this->K; i++) {
            if (squaredDistances[i].first < result || result == -1) {
                result = squaredDistances[i].first;
                idx = i;
            }
        }

        return tuple<string, int>{ data[idx][this->classColumn], idx };
    }

} // namespace knn
