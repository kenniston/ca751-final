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

import veins.base.utils.Coord;
import veins.base.utils.SimpleAddress;
import veins.modules.messages.BaseFrame1609_4;

namespace veins;

class BasicSafetyMessage extends BaseFrame1609_4 {
    LAddress::L2Type senderId;
    Coord senderPos;
    Coord senderSpeed;
    Coord senderHeading;
    Coord senderGpsPos;
    double senderAccel;
    double senderWidth;
    double senderLength;
    int senderType;
    int senderAttackType;
    unsigned long senderPseudonym;
    double senderLastDistTraveled;
    bool rsu;
    double rss;
    double arrivalTime;
}