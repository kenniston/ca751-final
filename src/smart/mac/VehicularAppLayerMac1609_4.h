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

#ifndef APP_VEHICULARAPPLAYERMAC1609_4_H_
#define APP_VEHICULARAPPLAYERMAC1609_4_H_

#include "veins/base/utils/SimpleAddress.h"
#include "veins/modules/utility/Consts80211p.h"

namespace veins {

    /**
     * @brief
     * Interface between VehicularAppLayer and Mac1609_4
     *
     * @author Kenniston Arraes Bonfim
     *
     * @ingroup macLayer
     */
    class VEINS_API VehicularAppLayerMac1609_4 {
    public:
        virtual bool isChannelSwitchingActive() = 0;

        virtual simtime_t getSwitchingInterval() = 0;

        virtual bool isCurrentChannelCCH() = 0;

        virtual void changeServiceChannel(veins::Channel channelNumber) = 0;

        virtual ~VehicularAppLayerMac1609_4(){};

        /**
         * @brief Returns the MAC address of this MAC module.
         */
        virtual const LAddress::L2Type& getMACAddress() = 0;
    };

} // namespace veins

#endif /* APP_VEHICULARAPPLAYERMAC1609_4_H_ */
