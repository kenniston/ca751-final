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

#include <unistd.h>
#include <omnetpp.h>
#include <fstream>
#include <sys/stat.h>
#include "VehicularApp.h"
#include "../support/json/json.hpp"

Define_Module(VehicularApp);

using json = nlohmann::json;
using appType = AppType::VehicularAppType;
using attackType = AttackType::VehicularAppAttackType;

static double totalGenuine = 0;
static double totalAttacker = 0;

VehicularAppParams VehicularApp::params = VehicularAppParams();

void VehicularApp::initialize(int stage)
{
    VehicularAppLayer::initialize(stage);

    if (stage == 0) {
        // Framework init
        EV << "Initializing " << par("appName").stringValue() << std::endl;

        // Attack parameters
        params.attackTime = par("attackTime");
        params.attackProbability = par("attackProbability");

        // Output parameters
        params.outputPath = std::string(get_current_dir_name()) + "/" + par("outputPath").stdstringValue() + "/";
        params.simulationOutputFile = params.outputPath + par("simulationOutputFile").stdstringValue();
    } else if (stage == 1) {
        EV << par("appName").stringValue() << " initialized! " << std::endl;
        setup();
    }
}

void VehicularApp::finish()
{
    VehicularAppLayer::finish();
}

/**
 * General application setup
 */
void VehicularApp::setup() {
    // Sumo Vehicle Type
    sumoVType = traciVehicle->getVType();

    // Create output path
    mkdir(params.outputPath.c_str(), 0755);

    // Configure the Basic Safety Message serialization file name
    messageFileName = params.outputPath + "msgs-" + std::to_string(appId) +  ".json";

    json j;
    j["teste"] = { {"velocity", 123.44}, {"value", "str123"} };

    std::ofstream o(messageFileName, std::ios_base::app);
    o << j << std::endl;

    // Evaluate the vehicle type on the initialization
    evaluateType();

    // Change vehicle color in Sumo simulation based on vehicle type.
    // The vehicle color must be in RGBA format
    if (vAppType == AppType::VehicularAppType::Genuine) {
        traciVehicle->setColor(TraCIColor(255, 255, 0, 255)); // Yellow
    } else {
        traciVehicle->setColor(TraCIColor(255, 46, 46, 255)); // Red
    }
}

/**
 * The application has received a beacon message from another car or RSU
 * code for handling the message goes here.
 *
 * @param bsm Beacon message receive by the application.
 * @see TraciDemo11p
 */
void VehicularApp::onBSM(BasicSafetyMessage* bsm)
{
    if (!hasStopped) {
        traciVehicle->setSpeedMode(0x1f);
        traciVehicle->setSpeed(0);
        hasStopped = true;
    } else {
        traciVehicle->setSpeedMode(0x1f);
        traciVehicle->setSpeed(20);
        hasStopped = false;
    }
}

/**
 * The application has received a data message from another car or RSU
 * code for handling the message goes here.
 *
 * @param wsm Data message receive by the application.
 * @see TraciDemo11p
 */
void VehicularApp::onWSM(BaseFrame1609_4* wsm)
{

}

/**
 * The application has received a service advertisement from another car or
 * RSU code for handling the message goes here.
 *
 * @param wsa Advertisment message receive by the application.
 * @see TraciDemo11p
 */
void VehicularApp::onWSA(ServiceAdvertisment* wsa)
{

}

/**
 * This method is for self messages (mostly timers). it is important to call
 * the VehicularAppLayer function for BSM and WSM transmission.
 *
 * @param msg Message receive by the application.
 */
void VehicularApp::handleSelfMsg(cMessage* msg)
{
    VehicularAppLayer::handleSelfMsg(msg);
}

/**
 * The vehicle has moved. Code that reacts to new positions goes here.
 * member variables such as currentPosition and currentSpeed are updated
 * in the parent class.
 */
void VehicularApp::handlePositionUpdate(cObject* obj)
{
    VehicularAppLayer::handlePositionUpdate(obj);
}

/**
 * Check the probability and creation time of a new attacker.
 * The probability and start time can be configured in the
 * omnetpp.ini file.
 *
 * @param probability Probability value for creating new attackers.
 * @see VehicularAppType
 * @see VehicularAppAttackType
 */
void VehicularApp::evaluateType()
{
    double factor = totalAttacker / (totalGenuine + totalAttacker);
    if (params.attackProbability < factor && simTime().dbl() > params.attackTime) {
        totalAttacker++;
        vAppType = appType::Attacker;
        vAppAttackType = attackType(rand()%(AttackType::SIZE_OF_ENUM-1 + 1) + 1);
    } else {
        totalGenuine++;
        vAppType = AppType::VehicularAppType::Genuine;
        vAppAttackType = AttackType::VehicularAppAttackType::Genuine;
    }
}
