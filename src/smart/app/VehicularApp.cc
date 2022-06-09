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

#include <omnetpp.h>
#include "VehicularApp.h"

Define_Module(VehicularApp);

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

    } else if (stage == 1) {
        EV << par("appName").stringValue() << " initialized! Loading settings..." << std::endl;

        myVType = traciVehicle->getVType();

        // Change vehicle color in Sumo simulation
        traciVehicle->setColor(TraCIColor(255, 0, 0, 255));
    }
}

void VehicularApp::finish()
{
    VehicularAppLayer::finish();
}

void VehicularApp::onBSM(BasicSafetyMessage* bsm)
{
    // Your application has received a beacon message from another car or RSU
    // code for handling the message goes here
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

void VehicularApp::onWSM(BaseFrame1609_4* wsm)
{
    // Your application has received a data message from another car or RSU
    // code for handling the message goes here, see TraciDemo11p.cc for examples
}

void VehicularApp::onWSA(ServiceAdvertisment* wsa)
{
    // Your application has received a service advertisement from another car or RSU
    // code for handling the message goes here, see TraciDemo11p.cc for examples
}

void VehicularApp::handleSelfMsg(cMessage* msg)
{
    VehicularAppLayer::handleSelfMsg(msg);
    // this method is for self messages (mostly timers)
    // it is important to call the DemoBaseApplLayer function for BSM and WSM transmission
}

void VehicularApp::handlePositionUpdate(cObject* obj)
{
    VehicularAppLayer::handlePositionUpdate(obj);
    // the vehicle has moved. Code that reacts to new positions goes here.
    // member variables such as currentPosition and currentSpeed are updated in the parent class
}

/**
 * Check the probability and creation time of a new attacker.
 * The probability and start time can be configured in the
 * omnetpp.ini file.
 *
 * @param probability Probability value for creating new attackers.
 * @see VehicularAppType
 * @return Evaluated vehicle type (Attacker or Genuine).
 */
VehicularAppType VehicularApp::evaluateType(double probability)
{
    if (simTime().dbl() < params.attackTime) {
        return VehicularAppType::Genuine;
    }

    if ((totalAttacker + totalGenuine) == 0) {
        totalGenuine++;
        return VehicularAppType::Genuine;
    }

    double factor = totalAttacker / (totalGenuine + totalAttacker);
    if (probability > factor) {
        totalAttacker++;
        return VehicularAppType::Attacker;
    }

    return VehicularAppType::Genuine;
}
