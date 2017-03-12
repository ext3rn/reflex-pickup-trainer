#include "PickupSettings.h"

#include <string>
#include <fstream>
#include <unistd.h>
#include <limits.h>
#include <iostream>
#include <random>

#define CONFIG_FILE_NAME	"config"
#define CONFIG_DELIMITER	'='
#define CONFIG_COMMENT		';'

PickupSettings::PickupSettings() {
    read_config();
}

void PickupSettings::read_config() {
    // Open config file in current directory
    const size_t buf_size = PATH_MAX + 1;
    char buf_path[buf_size] = {0};
    const std::string cur_dir(getcwd(buf_path, buf_size));
    m_config_path = cur_dir + "/" + CONFIG_FILE_NAME;
    std::ifstream file(m_config_path);

    if (!file) {
        load_default();
        write_config_to_file();
    } else {
        // Read each line in config file
        std::string text;
        while (getline(file, text)) {
            const auto pos_delim = text.find(CONFIG_DELIMITER);

            // Skip comments
            if (text.find(CONFIG_COMMENT) == 0) {
                continue;
            }

            // If delimiter exists, split line into item name and interval
            if (pos_delim != std::string::npos) {
                std::string name = text.substr(0, pos_delim);
                const std::string str_interval = text.substr(pos_delim + 1);
                // Remove trailing spaces from item name
                const auto pos_last = name.find_last_not_of(" \t");
                name = name.substr(0, pos_last + 1);

                size_t last_char = 0;
                const unsigned int interval = std::stoul(str_interval,
                        &last_char, 10);

                m_item_list.emplace_back(new PickupItem(name, interval));
            }
        }
    }

    if (m_item_list.size() == 0) {
        std::cerr << "Error initializing from " << m_config_path << std::endl;
        load_default();
    }
}

std::shared_ptr<PickupItem> PickupSettings::get_random_item() {
    static std::default_random_engine engine(std::random_device{}());
    static std::uniform_int_distribution<unsigned int>
            dist(0, m_item_list.size() - 1);

    return m_item_list[dist(engine)];
}

void PickupSettings::load_default() {
    std::cerr << "Loading default values" << std::endl;

    m_item_list = {
        std::make_shared<PickupItem>("Red Armor", 25U) ,
        std::make_shared<PickupItem>("Yellow Armor", 25U),
        std::make_shared<PickupItem>("Mega Health", 30U),
    };
}

void PickupSettings::write_config_to_file() {
    std::cerr << "Writing config to " << m_config_path << std::endl;
    std::ofstream file(m_config_path, std::ofstream::out | std::ofstream::trunc);

    for (const auto &item : m_item_list) {
        file << item->m_name << " " << CONFIG_DELIMITER << " "
             << item->m_interval << std::endl;
    }
}
