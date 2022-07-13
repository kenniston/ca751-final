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
// @date    12/07/2022
// @version 1.0
//
package smart.simulations.road;

import org.car2x.veins.nodes.RSU;
import org.car2x.veins.base.connectionManager.ConnectionManager;
import org.car2x.veins.base.modules.BaseWorldUtility;
import org.car2x.veins.modules.mobility.traci.TraCIScenarioManager*;
import org.car2x.veins.modules.obstacle.ObstacleControl;
import org.car2x.veins.modules.world.annotations.AnnotationManager;
import org.car2x.veins.nodes.Car;
import org.car2x.veins.visualizer.roads.RoadsCanvasVisualizer;

network RoadNetwork //extends Scenario
{
    parameters:
        double playgroundSizeX @unit(m);
        double playgroundSizeY @unit(m);
        double playgroundSizeZ @unit(m);
        @display("bgb=1242,478,#A0E0A0,#A0E0A0,0");
    submodules:
        rsu[2]: RSU {
            @display("p=224,196;i=veins/sign/yellowdiamond;is=vs");
        }
        obstacles: ObstacleControl {
            @display("p=1162,378");
        }
        annotations: AnnotationManager {
            @display("p=582,378");
        }
        connectionManager: ConnectionManager {
            parameters:
                @display("p=236,378;i=abstract/multicast");
        }
        world: BaseWorldUtility {
            parameters:
                playgroundSizeX = veins_eval_by_version(veins_omnetpp_buildnum(), "playgroundSizeX", 1525, "parent.playgroundSizeX");
                playgroundSizeY = veins_eval_by_version(veins_omnetpp_buildnum(), "playgroundSizeY", 1525, "parent.playgroundSizeY");
                playgroundSizeZ = veins_eval_by_version(veins_omnetpp_buildnum(), "playgroundSizeZ", 1525, "parent.playgroundSizeZ");
                @display("p=58,378;i=misc/globe");
        }
        manager: TraCIScenarioManagerLaunchd {
            parameters:
                @display("p=734,378");
        }
        roadsCanvasVisualizer: RoadsCanvasVisualizer {
            @display("p=954,378");
        }
        node[0]: Car {
            @display("p=426,378");
        }

    connections allowunconnected:
}
