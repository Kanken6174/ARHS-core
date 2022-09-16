#include <hidapi/hidapi.h>
#include <iostream>

namespace hid_func{
hid_device* open_device_idx(int manufacturer, int product, int iface, int device_index);
}