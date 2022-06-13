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

#include "VehicularRSU11p.h"

Define_Module(VehicularRSU11p);

/**
 * This method is for self messages (mostly timers). it is important to call
 * the VehicularAppLayer function for BSM and WSM transmission.
 *
 * @param msg Message receive by the RSU.
 */
void VehicularRSU11p::handleSelfMsg(cMessage* msg) {
    switch (msg->getKind()) {
        case SEND_BEACON_EVT: {
            BasicSafetyMessage* bsm = new BasicSafetyMessage();
            bsm->setRsu(true);
            populateWSM(bsm);
            sendDown(bsm);
            scheduleAt(simTime() + beaconInterval, sendBeaconEvt);
            break;
        }
        case SEND_WSA_EVT: {
            ServiceAdvertisment* wsa = new ServiceAdvertisment();
            wsa->setRsu(true);
            populateWSM(wsa);
            sendDown(wsa);
            scheduleAt(simTime() + wsaInterval, sendWSAEvt);
            break;
        }
        default: {
            if (msg) EV_WARN << "APP: Error: Got Self Message of unknown kind! Name: " << msg->getName() << endl;
            break;
        }
    }
}

/**
 * The application has received a service advertisement from another car or
 * RSU code for handling the message goes here.
 *
 * @param wsa Advertisment message receive by the RSU.
 * @see TraciDemo11p
 */
void VehicularRSU11p::onWSA(ServiceAdvertisment* wsa)
{
    // if this RSU receives a WSA for service 42, it will tune to the chan
    if (wsa->getPsid() == 42) {
        mac->changeServiceChannel(static_cast<Channel>(wsa->getTargetChannel()));
    }
}

/**
 * The RSU has received a data message from another car or RSU.
 * The RSU repeats the received traffic update in 2 seconds plus
 * some random delay.
 *
 * @param wsm Data message receive by the RSU.
 * @see TraciDemo11p
 */
void VehicularRSU11p::onWSM(BaseFrame1609_4* frame)
{
    BasicSafetyMessage* wsm = check_and_cast<BasicSafetyMessage*>(frame);
    // this rsu repeats the received traffic update in 2 seconds plus some random delay
    sendDelayedDown(wsm->dup(), 2 + uniform(0.01, 0.2));
}
