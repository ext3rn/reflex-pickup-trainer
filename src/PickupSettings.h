#ifndef PICKUPSETTINGS_H
#define PICKUPSETTINGS_H

#include <memory>
#include <vector>

#include "PickupItem.h"

class PickupSettings {
public:
    PickupSettings();
    ~PickupSettings() = default;
    std::shared_ptr<PickupItem> get_random_item();

private:
    void read_config();
    void load_default();
    void write_config_to_file();
    std::vector<std::shared_ptr<PickupItem>> m_item_list;
    std::string m_config_path;
};

#endif // PICKUPSETTINGS_H
