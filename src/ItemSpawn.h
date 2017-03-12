#ifndef ITEMSPAWN_H
#define ITEMSPAWN_H

#include <memory>
#include <chrono>

#include "PickupItem.h"
#include "PickupSettings.h"

class ItemSpawn {
public:
    ItemSpawn(std::shared_ptr<PickupSettings> item);
    ItemSpawn() = delete;
    void answer(unsigned int user_answer);
    bool is_answer_correct() const;
    std::string get_item_name() const;
    std::string get_old_time() const;
    std::string get_new_time() const;
    float get_answer_duration() const;

private:
    unsigned int generate_random_no(unsigned int upper_limit) const;
    std::shared_ptr<PickupItem> m_item;
    std::shared_ptr<PickupSettings> m_settings;
    unsigned int m_old_time = 0;
    unsigned int m_new_time = 0;
    bool m_is_answer_correct = false;
    std::chrono::steady_clock::time_point m_answer_start_time;
    std::chrono::duration<float> m_answer_duration;
};

unsigned int get_total_correct(
        const std::vector<std::shared_ptr<ItemSpawn>> &spawn_list);
float calc_average(const std::vector<std::shared_ptr<ItemSpawn>> &spawn_list);

inline std::string ItemSpawn::get_item_name() const {
    return m_item->m_name;
}

inline bool ItemSpawn::is_answer_correct() const {
    return m_is_answer_correct;
}

inline float ItemSpawn::get_answer_duration() const {
    return m_answer_duration.count();
}

#endif // ITEMSPAWN_H
