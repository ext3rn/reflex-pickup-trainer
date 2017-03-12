#ifndef PICKUPITEM_H
#define PICKUPITEM_H

#include <string>

class PickupSettings;
class ItemSpawn;

class PickupItem {
    friend PickupSettings;
    friend ItemSpawn;

public:
    PickupItem() = delete;
    PickupItem(const std::string &name, unsigned int interval);
    ~PickupItem() = default;

private:
    std::string m_name;
    unsigned int m_interval = 0;
};

#endif // PICKUPITEM_H
