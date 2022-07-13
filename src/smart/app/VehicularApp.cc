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
using json = nlohmann::ordered_json;
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
        params.attackConstantX = par("attackConstantX");
        params.attackConstantY = par("attackConstantY");
        params.attackConstantZ = par("attackConstantZ");

        // Output parameters
        char *buf = (char*)malloc(sizeof(char) * PATH_MAX);
        char *dir = getcwd(buf, PATH_MAX);
        params.outputPath = string(dir) + "/" + par("outputPath").stdstringValue() + "/";
        params.simulationOutputFile = params.outputPath + par("simulationOutputFile").stdstringValue();
        params.writeCsvGlobalMessages = par("writeCsvGlobalMessages");
        params.writeCsvVehicleMessages = par("writeCsvVehicleMessages");
        params.writeJsonGlobalMessages = par("writeJsonGlobalMessages");
        params.writeJsonVehicleMessages = par("writeJsonVehicleMessages");

        params.trainingFile = par("trainingFile").stdstringValue();
        params.trainingFileHeader = par("trainingFileHeader");
        params.trainingFileFilterColumns = check_and_cast<cValueArray*>(par("trainingFileFilterColumns").objectValue());
        params.trainingFileLabelColumn = par("trainingFileLabelColumn");
    } else if (stage == 1) {
        EV << par("appName").stringValue() << " initialized! " << std::endl;
        setup();
    }
}

void VehicularApp::finish()
{
    VehicularAppLayer::finish();

    // Close all output streams for this application
    if (messageJsonOutStream.is_open()) {
        messageJsonOutStream.close();
    }
    if (globalJsonMessageOutStream.is_open()) {
        globalJsonMessageOutStream.close();
    }
    if (messageCsvOutStream.is_open()) {
        messageCsvOutStream.close();
    }
    if (globalCsvMessageOutStream.is_open()) {
        globalCsvMessageOutStream.close();
    }

    // Remove allocated memory in history
    for (std::pair<LAddress::L2Type, vector<BasicSafetyMessage*>> element : bsmHistory) {
        for (BasicSafetyMessage* bsm : element.second) {
            delete bsm;
        }
    }
}

/**
 * General application setup
 */
void VehicularApp::setup() {
    // Sumo Vehicle Type
    sumoVType = traciVehicle->getVType();

    // Change Icon
    auto host = findHost();
    cDisplayString& disp = host->getDisplayString();
    //disp.setTagArg("i", 0, "smart/node/mercedes,red");
    //disp.setTagArg("is", 0, "");


    // Configure output files
    configureOutput();

    // Evaluate the vehicle type on the initialization
    evaluateType();

    // Change vehicle color in Sumo simulation based on vehicle type.
    // The vehicle color must be in RGBA format
    if (vAppType == AppType::VehicularAppType::Genuine) {
        traciVehicle->setColor(TraCIColor(255, 255, 0, 255)); // Yellow
    } else {
        traciVehicle->setColor(TraCIColor(255, 46, 46, 255)); // Red
    }

    // Configure the misbehavior decider
    vector<int64_t> filterColums = params.trainingFileFilterColumns->asIntVector();
    decider = make_unique<VehicularAppDecider>();
    decider->initialize(params.trainingFile, filterColums, params.trainingFileLabelColumn);
}

/**
 * Output file configuration
 */
void VehicularApp::configureOutput(){
    // Create output path
    mkdir(params.outputPath.c_str(), 0755);
    mkdir((params.outputPath + "csv/").c_str(), 0755);
    mkdir((params.outputPath + "json/").c_str(), 0755);

    // Create output streams for the Basic Safety Message serialization
    string jsonMessageFileName = params.outputPath + "json/bsm-app-" + std::to_string(appId) +  ".json";
    string jsonGlobalMessageFileName = params.outputPath + "json/global-bsm.json";
    string csvMessageFileName = params.outputPath + "csv/bsm-app-" + std::to_string(appId) +  ".csv";
    string csvGlobalMessageFileName = params.outputPath + "csv/global-bsm.csv";
    string csvHeader =
            "receiver,positionX,positionY,positionZ,speedX,speedY,speedZ,"
            "headingX,headingY,headingZ,distance,sender,senderPosX,senderPosY,"
            "senderPosZ,senderSpeed,senderSpeedX,senderSpeedY,senderSpeedZ,senderHeadingX,"
            "senderHeadingY,senderHeadingZ,senderAccel,senderGPSPosX,senderGPSPosY,"
            "senderGPSPosZ,attackType,senderType,senderDistTraveled,isRSU,RSS,arrivalTime";

    if (params.writeJsonVehicleMessages) {
        messageJsonOutStream.open(jsonMessageFileName, ios_base::app);
    }
    if (params.writeJsonGlobalMessages) {
        globalJsonMessageOutStream.open(jsonGlobalMessageFileName, ios_base::app);
    }
    if (params.writeCsvVehicleMessages) {
        bool createHeader = access(csvMessageFileName.c_str(), F_OK) == -1;
        messageCsvOutStream.open(csvMessageFileName, ios_base::app);
        if (createHeader) messageCsvOutStream << csvHeader << endl;
    }
    if (params.writeCsvGlobalMessages) {
        bool createHeader = access(csvGlobalMessageFileName.c_str(), F_OK) == -1;
        globalCsvMessageOutStream.open(csvGlobalMessageFileName, ios_base::app);
        if (createHeader) globalCsvMessageOutStream << csvHeader << endl;
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
    json j;

    // Receiver ID in the simulation
    j["receiver"] = appId;

    // Receiver position at current simulation time
    j["position"] = to_string(curPosition.x) + "," + to_string(curPosition.y) + "," + to_string(curPosition.z);

    // Receiver speed
    j["speed"] = to_string(curSpeed.x) + "," + to_string(curSpeed.y) + "," + to_string(curSpeed.z);

    // Receiver heading
    j["heading"] = to_string(curHeading.x) + "," + to_string(curHeading.y) + "," + to_string(curHeading.z);

    // Distance between sender and receiver vehicles
    double distance = curPosition.distance(bsm->getSenderPos());
    j["distance"] = distance;

    // Sender ID in the simulation
    j["sender"] = bsm->getSenderId();

    // Sender position
    Coord senderPosition = bsm->getSenderPos();
    j["senderPos"] = to_string(senderPosition.x) + "," + to_string(senderPosition.y) + "," + to_string(senderPosition.z);

    // Sender speed vector
    Coord senderSpeed = bsm->getSenderSpeed();
    j["senderSpeed"] = to_string(senderSpeed.x) + "," + to_string(senderSpeed.y) + "," + to_string(senderSpeed.z);

    // Sender speed length
    j["senderSpeedLength"] = senderSpeed.length();

    // Sender heading
    Coord senderHeading = bsm->getSenderHeading();
    j["senderHeading"] = to_string(senderHeading.x) + "," + to_string(senderHeading.y) + "," + to_string(senderHeading.z);

    // Sender acceleration
    j["senderAccel"] = bsm->getSenderAccel();

    // Sender GPS Coordinates
    Coord senderGPSPos = bsm->getSenderGpsPos();
    j["senderGPSPos"] = to_string(senderGPSPos.x) + "," + to_string(senderGPSPos.y) + "," + to_string(senderGPSPos.z);

    // Sender Attacker Type
    j["attackType"] = bsm->getSenderAttackType();

    // Sender Type - Genuine or Attacker
    j["senderType"] = bsm->getSenderType();

    // Last Distance Traveled (Sender)
    j["senderDistTraveled"] = bsm->getSenderLastDistTraveled();

    // RSU flag
    j["isRSU"] = bsm->getRsu() ? 1 : 0;

    // Received Signal Strength (RSS)
    j["RSS"] = bsm->getRss();

    // BSM Arrival Time
    j["arrivalTime"] = bsm->getArrivalTime();

    if (params.writeJsonVehicleMessages) {
        messageJsonOutStream << j << endl;
        messageJsonOutStream.flush();
    }
    if (params.writeJsonGlobalMessages) {
        globalJsonMessageOutStream << j << endl;
        globalJsonMessageOutStream.flush();
    }
}

/**
 * Save the BSM to output stream in CSV format.
 *
 * @param bsm The Basic Safety Message to save.
 * @see BasicSafetyMessage
 */
void VehicularApp::saveCsvBSM(BasicSafetyMessage* bsm)
{
    stringstream str;

    // Receiver ID in the simulation
    str << appId << ",";

    // Receiver position at current simulation time
    str << to_string(curPosition.x) + "," + to_string(curPosition.y) + "," + to_string(curPosition.z) << ",";

    // Receiver speed
    str << to_string(curSpeed.x) + "," + to_string(curSpeed.y) + "," + to_string(curSpeed.z) << ",";

    // Receiver heading
    str << to_string(curHeading.x) + "," + to_string(curHeading.y) + "," + to_string(curHeading.z) << ",";

    // Distance between sender and receiver vehicles
    double distance = curPosition.distance(bsm->getSenderPos());
    str << distance << ",";

    // Sender ID in the simulation
    str << bsm->getSenderId() << ",";

    // Sender position
    Coord senderPosition = bsm->getSenderPos();
    str << to_string(senderPosition.x) + "," + to_string(senderPosition.y) + "," + to_string(senderPosition.z) << ",";

    // Sender speed
    Coord senderSpeed = bsm->getSenderSpeed();
    str<< to_string(senderSpeed.length()) << ",";

    // Sender speed vector
    str << to_string(senderSpeed.x) + "," + to_string(senderSpeed.y) + "," + to_string(senderSpeed.z) << ",";

    // Sender heading
    Coord senderHeading = bsm->getSenderHeading();
    str << to_string(senderHeading.x) + "," + to_string(senderHeading.y) + "," + to_string(senderHeading.z) << ",";

    // Sender acceleration
    str << bsm->getSenderAccel() << ",";

    // Sender GPS Coordinates
    Coord senderGPSPos = bsm->getSenderGpsPos();
    str << to_string(senderGPSPos.x) + "," + to_string(senderGPSPos.y) + "," + to_string(senderGPSPos.z) << ",";

    // Sender Attacker Type
    str << bsm->getSenderAttackType() << ",";

    // Sender Type - Genuine or Attacker
    str << bsm->getSenderType() << ",";

    // Last Distance Traveled (Sender)
    str << bsm->getSenderLastDistTraveled() << ",";

    // RSU flag
    str << (bsm->getRsu() ? 1 : 0) << ",";

    // Received Signal Strength (RSS)
    str << bsm->getRss() << ",";

    // BSM Arrival Time
    str << bsm->getArrivalTime();


    if (params.writeCsvVehicleMessages) {
        messageCsvOutStream << str.str() << endl;
        messageCsvOutStream.flush();
    }
    if (params.writeCsvGlobalMessages) {
        globalCsvMessageOutStream << str.str() << endl;
        globalCsvMessageOutStream.flush();
    }
}

/**
 * Sets all the necessary fields in the WSM, BSM, or WSA.
 *
 * @param bsm Beacon message to be sent.
 */
void VehicularApp::performAttack(BasicSafetyMessage* bsm)
{
    if (vAppAttackType == attackType::Genuine) return;

    switch (vAppAttackType) {
        case attackType::ConstantPosition:
        {
            curPosition = Coord(params.attackConstantX, params.attackConstantY, params.attackConstantZ);
            std::pair<double, double> curLonLat = traci->getLonLat(curPosition);
            curGPS = Coord(curLonLat.first, curLonLat.second);
            bsm->setSenderPos(curPosition);
            bsm->setSenderGpsPos(curGPS);
            break;
        }
        case attackType::RandomPosition: {
            curPosition = world->getRandomPosition();
            std::pair<double, double> curLonLat = traci->getLonLat(curPosition);
            curGPS = Coord(curLonLat.first, curLonLat.second);
            bsm->setSenderPos(curPosition);
            bsm->setSenderGpsPos(curGPS);
            break;
        }
        default:
            break;
    }
}

/**
 * Sets all the necessary fields in the WSM, BSM, or WSA.
 *
 */
void VehicularApp::populateWSM(BaseFrame1609_4* wsm, LAddress::L2Type rcvId, int serial) {
    VehicularAppLayer::populateWSM(wsm, rcvId, serial);

    if (BasicSafetyMessage* bsm = dynamic_cast<BasicSafetyMessage*>(wsm)) {
        // Configure GPS coordinates, vehicle acceleration and speed
        std::pair<double, double> curLonLat = traci->getLonLat(curPosition);
        curGPS = Coord(curLonLat.first, curLonLat.second);
        curAccel = traciVehicle->getAcceleration();
        bsm->setSenderSpeed(curSpeed);

        // Configure the vehicle type and attack type in the beacon message
        bsm->setSenderType(vAppType);
        bsm->setSenderAttackType(vAppAttackType);

        // Configure vehicule heading and acceleration
        bsm->setSenderHeading(curHeading);
        bsm->setSenderAccel(curAccel);

        // Check and perform attacks
        performAttack(bsm);
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
    updateHistory(bsm);

    if (params.writeJsonVehicleMessages || params.writeJsonGlobalMessages) {
        saveJsonBSM(bsm);
    }

    if (params.writeCsvVehicleMessages || params.writeCsvGlobalMessages) {
        saveCsvBSM(bsm);
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
    if (params.attackProbability > factor && simTime().dbl() > params.attackTime) {
        totalAttacker++;
        vAppType = appType::Attacker;
        vAppAttackType = attackType(rand()%(AttackType::SIZE_OF_ENUM-1) + 1);
    } else {
        totalGenuine++;
        vAppType = AppType::VehicularAppType::Genuine;
        vAppAttackType = AttackType::VehicularAppAttackType::Genuine;
    }
}

/**
 * Update the BSM and save it to history.
 *
 * @param bsm Beacon message receive by the application.
 */
void VehicularApp::updateHistory(BasicSafetyMessage* bsm) {
    // Make copy of BSM
    BasicSafetyMessage* bsmCopy = bsm->dup();

    LAddress::L2Type senderId = bsmCopy->getSenderId();

    // Calculate the distance traveled based on the last BSM received
    vector<BasicSafetyMessage* > vec = bsmHistory[senderId];
    if (vec.size() > 0) {
        Coord lastCoord = vec[vec.size() - 1]->getSenderPos();
        Coord curCoord = bsmCopy->getSenderPos();

        double lastDistance = curCoord.distance(lastCoord);
        bsmCopy->setSenderLastDistTraveled(lastDistance);
        bsm->setSenderLastDistTraveled(lastDistance);
    }

    // Store the received BSM in the sender's history
    vec.push_back(bsmCopy);
    bsmHistory[senderId] = vec;
}

