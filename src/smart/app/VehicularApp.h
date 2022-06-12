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
#include "VehicularAppParams.h"
#include "../enum/VehicularAppType.h"
#include "../enum/VehicularAppAttackType.h"

using namespace std;
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
    /** @brief General application parameters */
    static VehicularAppParams params;

    /** @brief The car has stopped in sumo simulation */
    bool hasStopped;

    /** @brief Received messages output stream in JSON format */
    ofstream messageJsonOutStream;

    /** @brief Global output stream for all vehicles in JSON format. The stream file is the same for all vehicles. */
    ofstream globalJsonMessageOutStream;

    /** @brief Received messages output stream in CSV format */
    ofstream messageCsvOutStream;

    /** @brief Global output stream for all vehicles in CSV format. This stream file is the same for all vehicles. */
    ofstream globalCsvMessageOutStream;

    /** @brief Vehicule type from sumo integration */
    string sumoVType;

    /** @brief Application attack type based on attack probability parameter */
    AttackType::VehicularAppAttackType vAppAttackType;

    /** @brief Application type based on attack probability parameter */
    AppType::VehicularAppType vAppType;

    /** @brief Evaluate the vehicle type on the initialization based on attack probability */
    void evaluateType();

    /** @brief General application setup */
    void setup();

    /** @brief Handle self messages such as timer or other kinds of self messages */
    void handleSelfMsg(cMessage* msg) override;

    /** @brief The vehicle has moved. Code that reacts to new positions goes here */
    void handlePositionUpdate(cObject* obj) override;

    /** @brief The application has received a BEACON message from another car or RSU */
    void onBSM(BasicSafetyMessage* bsm) override;

    /** @brief The application has received a DATA message from another car or RSU */
    void onWSM(BaseFrame1609_4* wsm) override;

    /** @brief The application has received a ADVERTISEMENT message from another car or RSU */
    void onWSA(ServiceAdvertisment* wsa) override;

    /** @brief Save the BSM to output stream in JSON format */
    void saveJsonBSM(BasicSafetyMessage* bsm);

    /** @brief Save the BSM to output stream in CSV format */
    void saveCsvBSM(BasicSafetyMessage* bsm);
};

#endif /* APP_VEHICULARAPP_H_ */
