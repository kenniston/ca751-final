package smart.simulations.brasilia;

import org.car2x.veins.nodes.RSU;
import org.car2x.veins.nodes.Scenario;

network BrasiliaNetwork extends Scenario
{
    submodules:
        rsu[1]: RSU {
            @display("p=62,140;i=veins/sign/yellowdiamond;is=vs");
        }
}
