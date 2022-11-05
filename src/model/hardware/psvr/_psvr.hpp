#include "../ihidapi/_hidapi.hpp"
#include "../../../model/patterns/commands/commands.hpp"

const unsigned char psvr_vrmode_off[8]{0x23, 0x00, 0xaa, 0x04, 0x00, 0x00, 0x00, 0x00};
const unsigned char psvr_vrmode_on[8]{0x23, 0x00, 0xaa, 0x04, 0x01, 0x00, 0x00, 0x00};
const unsigned char psvr_power_off[8]{0x17, 0x00, 0xaa, 0x04, 0x01, 0x00, 0x00, 0x00};
const unsigned char psvr_power_on[8]{0x17, 0x00, 0xaa, 0x04, 0x00, 0x00, 0x00, 0x00};

#define sony_vid 0x054c
#define psvr_pid 0x09af
#define ctrl_device_iface 5
#define ld_device_iface 4

namespace psvr
{
    class Psvr
    {
    public:
        hid_device *handle;
        bool vrMode;
        bool powered;

        Psvr(); // default constructor
        ~Psvr();

        void startup();
        void shutdown();
        void vrmode();
        void cinemaMode();
        void close(); // default destructor
    };

    class StartupCommand : public Command
    {
    private:
        Psvr *_internal;
    public:
        StartupCommand(Psvr *internal) : _internal(internal) {}
        void Execute() const override {_internal->startup();}
    };

    class ShutdownCommand : public Command
    {
    private:
        Psvr *_internal;
    public:
        ShutdownCommand(Psvr *internal) : _internal(internal) {}
        void Execute() const override { _internal->shutdown();}
    };

    class CinemaModeCommand : public Command
    {
    private:
        Psvr *_internal;
    public:
        CinemaModeCommand(Psvr *internal) : _internal(internal) {}
        void Execute() const override { _internal->cinemaMode();}
    };

    class VrModeCommand : public Command
    {
    private:
        Psvr *_internal;
    public:
        VrModeCommand(Psvr *internal) : _internal(internal) {}
        void Execute() const override { _internal->vrmode(); }
    };
}