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
// @date    09/06/2022
// @version 1.0
//

#ifndef APP_VEHICULARAPPPARAMS_H_
#define APP_VEHICULARAPPPARAMS_H_

/**
 * @brief
 * Vehicular application parameters.
 *
 * @author Kenniston Arraes Bonfim
 *
 */
class VehicularAppParams {
public:
    /* Attack start time in seconds */
    double attackTime;

    /* Attacker rate in the simulation */
    double attackProbability;

    /* Output path for messages and result analysis */
    std::string outputPath;

    /* Global filename for simulation messages */
    std::string simulationOutputFile;
};

#endif /* APP_VEHICULARAPPPARAMS_H_ */
