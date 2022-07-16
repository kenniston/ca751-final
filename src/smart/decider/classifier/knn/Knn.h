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
#ifndef CLASSIFIER_KNN_H_
#define CLASSIFIER_KNN_H_

#include <tuple>
#include <string>

#include "../../DeciderStd.h"

namespace knn {
    using namespace std;

    /**
     * @brief
     * Knn classifier.
     *
     * @author Kenniston Arraes Bonfim
     * @ingroup KNN
     * @see KNN
     */
    class Knn {
    public:
        /** @brief Question Destructor */
        virtual ~Knn() = default;

        /** @brief General KNN initialization */
        virtual void initialize(dataframe df, svector header, int classColumn, int K);

        /** @brief Classify the input data **/
        virtual tuple<string, int> classify(svector sample);
    protected:
        /** @brief k-nearest neighbors constant */
        int K;

        /** @brief The training dataframe */
        dataframe data;

        /** @brief Dataframe header */
        svector header;

        /** @brief ID for the class column in dataframe */
        int classColumn;
    };
}

#endif /* CLASSIFIER_KNN_H_ */
