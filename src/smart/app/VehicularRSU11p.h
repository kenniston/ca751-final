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
// @date    06/06/2022
// @version 1.0
//

#ifndef APP_VEHICULARRSU11P_H_
#define APP_VEHICULARRSU11P_H_

#include <omnetpp.h>

#include "VehicularAppLayer.h"

using namespace veins;
using namespace omnetpp;

/**
 * @brief
 * Small Vehicular Road Side Unit using 11p.
 * Most common functions are overloaded.
 * See VehicularRSU11p.cc for hints
 *
 * @author Kenniston Arraes Bonfim
 *
 */
class VEINS_API VehicularRSU11p: public VehicularAppLayer {
protected:
    /** @brief Handle self messages such as timer or other kinds of self messages */
    void handleSelfMsg(cMessage* msg) override;

    /** @brief The application has received a DATA message from another car or RSU */
    void onWSM(BaseFrame1609_4* wsm) override;

    /** @brief The application has received a ADVERTISEMENT message from another car or RSU */
    void onWSA(ServiceAdvertisment* wsa) override;
};

#endif /* APP_VEHICULARRSU11P_H_ */
