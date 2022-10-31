#include "_psvr.hpp"

namespace psvr{

Psvr::Psvr(){
    int res = hid_init();
    handle = hid_func::open_device_idx(sony_vid, psvr_pid, ctrl_device_iface, 0);

    if (!handle) {
		std::cout << "failed to open PSVR control handle" << std::endl;
		return;
	}

    if (hid_set_nonblocking(handle, 1) == -1) {
		std::cout << "failed to set non-blocking on device" << std::endl;
		return;
	}

    startup();
}

void Psvr::startup(){
    //no check because power on is critical
    if (hid_write(handle, psvr_power_on, sizeof(psvr_power_on)) == -1) {
		std::cout << "failed to write to device (power on)" << std::endl;
		return;
	}
    powered = true;
}

void Psvr::shutdown(){
    if(!powered) return;
	if (hid_write(handle, psvr_power_off, sizeof(psvr_power_off)) == -1) {
		std::cout << "failed to write to device (power off)" << std::endl;
		return;
	}
    powered = false;
}

void Psvr::vrmode(){
    if(vrMode) return;
	if (hid_write(handle, psvr_vrmode_on, sizeof(psvr_vrmode_on)) == -1) {
		std::cout << "failed to write to device (set VR mode)" << std::endl;
		return;
	}
    vrMode = true;
}

void Psvr::cinemaMode(){
    if(!vrMode) return;
    	if (hid_write(handle, psvr_vrmode_off, sizeof(psvr_vrmode_off)) == -1) {
		std::cout << "failed to write to device (set VR mode off)" << std::endl;
		return;
	}
    vrMode = false;
}

Psvr::~Psvr(){
    if(powered) shutdown();
    hid_close(handle);
	int res = hid_exit();
}
}