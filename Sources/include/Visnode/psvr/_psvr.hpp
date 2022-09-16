#include "../ihidapi/_hidapi.hpp"

const unsigned char psvr_vrmode_off[8] {0x23,0x00,0xaa,0x04,0x00,0x00,0x00,0x00};
const unsigned char psvr_vrmode_on[8] {0x23,0x00,0xaa,0x04,0x01,0x00,0x00,0x00};
const unsigned char psvr_power_off[8] {0x17,0x00,0xaa,0x04,0x01,0x00,0x00,0x00};
const unsigned char psvr_power_on[8] {0x17,0x00,0xaa,0x04,0x00,0x00,0x00,0x00};

#define sony_vid 0x054c
#define psvr_pid 0x09af
#define ctrl_device_iface 5
#define ld_device_iface 4

namespace psvr{
    class Psvr{
        public:
        static hid_device* handle;
        static bool vrMode;
        static bool powered;

        static void open(); //default constructor

        static void startup();
        static void shutdown();
        static void vrmode();
        static void cinemaMode();

        static void close();//default destructor
    };
}