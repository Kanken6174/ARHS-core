#include "_hidapi.hpp"

namespace hid_func{

hid_device* open_device_idx(int manufacturer, int product, int iface, int device_index)
{
	struct hid_device_info* devs = hid_enumerate(manufacturer, product);
	struct hid_device_info* cur_dev = devs;

	int idx = 0;
	hid_device* ret = NULL;

	while (cur_dev) {
		std::cout << manufacturer << product << cur_dev->path << std::endl;

		if (cur_dev->interface_number == iface) {
			if (idx == device_index) {
				std::cout << "\topening " << cur_dev->path << std::endl;
				ret = hid_open_path(cur_dev->path);
				break;
			}

			idx++;
		}

		cur_dev = cur_dev->next;
	}

	hid_free_enumeration(devs);

	return ret;
}
}