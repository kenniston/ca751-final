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
// @date    31/05/2022
// @version 1.0
//

#ifndef APP_VEHICULARAPP_H_
#define APP_VEHICULARAPP_H_

#include <omnetpp.h>

#include "VehicularAppLayer.h"
#include "../enum/VehicularAppType.h"

using namespace veins;
using namespace omnetpp;

/**
 * @brief
 * Vehicular application for misbehavior detection.
 * Most common functions are overloaded.
 * See VehicularApp.cc for hints
 *
 * @author Kenniston Arraes Bonfim
 *
 */
class VEINS_API VehicularApp: public VehicularAppLayer {
public:
    void initialize(int stage) override;
    void finish() override;

protected:
    std::string myVType;
    bool hasStopped;

    void onBSM(BasicSafetyMessage* bsm) override;
    void onWSM(BaseFrame1609_4* wsm) override;
    void onWSA(ServiceAdvertisment* wsa) override;

    void handleSelfMsg(cMessage* msg) override;
    void handlePositionUpdate(cObject* obj) override;

    VehicularAppType evaluateType(double probability);
};

#endif /* APP_VEHICULARAPP_H_ */
