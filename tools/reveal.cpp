// This is a reveal program. It reveals the map.

#include <iostream>
#include <integers.h>
#include <vector>
using namespace std;

#include <DFTypes.h>
#include <DFHackAPI.h>

int main (void)
{
    uint32_t x_max,y_max,z_max;
    DFHack::t_designation designations[256];
    
    DFHack::API DF("Memory.xml");
    if(!DF.Attach())
    {
        cerr << "DF not found" << endl;
        return 1;
    }
    DF.InitMap();
    DF.getSize(x_max,y_max,z_max);
    
    // walk the map
    for(uint32_t x = 0; x< x_max;x++)
    {
        for(uint32_t y = 0; y< y_max;y++)
        {
            for(uint32_t z = 0; z< z_max;z++)
            {
                if(DF.isValidBlock(x,y,z))
                {
                    // read block designations
                    DF.ReadDesignations(x,y,z, (uint32_t *) designations);
                    // change the hidden flag to 0
                    for (uint32_t i = 0; i < 256;i++)
                    {
                        designations[i].bits.hidden = 0;
                    }
                    // write the designations back
                    DF.WriteDesignations(x,y,z, (uint32_t *) designations);
                }
            }
        }
    }
    DF.Detach();
    #ifndef LINUX_BUILD
    cout << "Done. Press any key to continue" << endl;
    cin.ignore();
    #endif
    return 0;
}
