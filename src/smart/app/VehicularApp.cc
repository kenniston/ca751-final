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

#include <limits>
#include <fstream>
#include <unistd.h>
#include <omnetpp.h>
#include <sys/stat.h>
#include "VehicularApp.h"
#include "../support/json/json.hpp"

Define_Module(VehicularApp);

using namespace std;
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
        char *buf = (char*)malloc(sizeof(char) * PATH_MAX);
        char *dir = getcwd(buf, PATH_MAX);
        params.outputPath = string(dir) + "/" + par("outputPath").stdstringValue() + "/";
        params.simulationOutputFile = params.outputPath + par("simulationOutputFile").stdstringValue();
    } else if (stage == 1) {
        EV << par("appName").stringValue() << " initialized! " << std::endl;
        setup();
    }
}

void VehicularApp::finish()
{
    VehicularAppLayer::finish();

    // Close all output streams for this application
    messageJsonOutStream.close();
    globalJsonMessageOutStream.close();
    messageCsvOutStream.close();
    globalCsvMessageOutStream.close();
}

/**
 * General application setup
 */
void VehicularApp::setup() {
    // Sumo Vehicle Type
    sumoVType = traciVehicle->getVType();

    // Create output path
    mkdir(params.outputPath.c_str(), 0755);
    mkdir((params.outputPath + "csv/").c_str(), 0755);
    mkdir((params.outputPath + "json/").c_str(), 0755);

    // Create output streams for the Basic Safety Message serialization
    string jsonMessageFileName = params.outputPath + "json/bsm-app-" + std::to_string(appId) +  ".json";
    string jsonGlobalMessageFileName = params.outputPath + "json/global-bsm.json";
    string csvMessageFileName = params.outputPath + "csv/bsm-app-" + std::to_string(appId) +  ".csv";
    string csvGlobalMessageFileName = params.outputPath + "csv/global-bsm.csv";

    messageJsonOutStream.open(jsonMessageFileName, ios_base::app);
    globalJsonMessageOutStream.open(jsonGlobalMessageFileName, ios_base::app);
    messageCsvOutStream.open(csvMessageFileName, ios_base::app);
    globalCsvMessageOutStream.open(csvGlobalMessageFileName, ios_base::app);

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
 * Save the BSM to output stream in JSON format.
 *
 * @param bsm The Basic Safety Message to save.
 * @see BasicSafetyMessage
 */
void VehicularApp::saveJsonBSM(BasicSafetyMessage* bsm)
{
    nlohmann::ordered_json j;

    // Receiver ID in the simulation
    j["receiver"] = appId;

    // Sender ID in the simulation
    j["sender"] = bsm->getSenderRealId();

    // Receiver position at current simulation time
    Coord currPosition = mobility->getPositionAt(simTime());
    j["position"] = to_string(currPosition.x) + "," + to_string(currPosition.y) + "," + to_string(currPosition.z);

    // Receiver speed
    Coord currSpeed = mobility->getHostSpeed();
    j["speed"] = to_string(currSpeed.x) + "," + to_string(currSpeed.y) + "," + to_string(currSpeed.z);

    // Distance between sender and receiver vehicles
    double distance = currPosition.distance(bsm->getSenderPos());
    j["distance"] = distance;

    // Sender position
    Coord senderPosition = bsm->getSenderPos();
    j["senderPos"] = to_string(senderPosition.x) + "," + to_string(senderPosition.y) + "," + to_string(senderPosition.z);

    // Sender speed
    Coord senderSpeed = bsm->getSenderSpeed();
    j["senderSpeed"] = to_string(senderSpeed.x) + "," + to_string(senderSpeed.y) + "," + to_string(senderSpeed.z);

    // Sender acceleration
    Coord senderAccel = bsm->getSenderAccel();
    j["senderAccel"] = to_string(senderAccel.x) + "," + to_string(senderAccel.y) + "," + to_string(senderAccel.z);

    // Sender acceleration
    Coord senderHeading = bsm->getSenderHeading();
    j["senderHeading"] = to_string(senderHeading.x) + "," + to_string(senderHeading.y) + "," + to_string(senderHeading.z);

    // Sender GPS Coordinates
    Coord senderGPSPos = bsm->getSenderGpsCoordinates();
    j["senderGPSPos"] = to_string(senderGPSPos.x) + "," + to_string(senderGPSPos.y) + "," + to_string(senderGPSPos.z);

    // Sender Attacker Type
    j["attackType"] = bsm->getSenderAttackType();

    // Sender Type - Genuine or Attacker
    j["senderType"] = bsm->getSenderType();

    messageJsonOutStream << j << endl;
    globalJsonMessageOutStream << j << endl;
}

/**
 * Save the BSM to output stream in CSV format.
 *
 * @param bsm The Basic Safety Message to save.
 * @see BasicSafetyMessage
 */
void VehicularApp::saveCsvBSM(BasicSafetyMessage* bsm)
{

}

/**
 * Sets all the necessary fields in the WSM, BSM, or WSA.
 *
 */
void VehicularApp::populateWSM(BaseFrame1609_4* wsm, LAddress::L2Type rcvId, int serial) {
    VehicularAppLayer::populateWSM(wsm, rcvId, serial);

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
    saveJsonBSM(bsm);

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
