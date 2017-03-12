#include "ItemSpawn.h"

#include <random>
#include <string>
#include <iomanip>
#include <algorithm>
#include <sstream>

ItemSpawn::ItemSpawn(std::shared_ptr<PickupSettings> settings):
        m_settings(settings) {
    m_old_time = generate_random_no(59);
    m_item = m_settings->get_random_item();
    m_new_time = (m_old_time + m_item->m_interval) % 60U;

    m_answer_start_time = std::chrono::steady_clock::now();
}

// Generate random unsigned int from 0 to upper_limit inclusive
unsigned int ItemSpawn::generate_random_no(unsigned int upper_limit) const {
    static std::default_random_engine engine(std::random_device{}());
    static std::uniform_int_distribution<unsigned int> dist(0, upper_limit);

    return dist(engine);
}

void ItemSpawn::answer(unsigned int user_answer) {
    m_is_answer_correct = (user_answer == m_new_time);

    auto answer_end_time = std::chrono::steady_clock::now();
    m_answer_duration = answer_end_time - m_answer_start_time;
}

std::string ItemSpawn::get_old_time() const {
    std::ostringstream formatted_time;
    formatted_time << std::setfill('0') << std::setw(2) << m_old_time;
    return formatted_time.str();
}

std::string ItemSpawn::get_new_time() const {
    std::ostringstream formatted_time;
    formatted_time << std::setfill('0') << std::setw(2) << m_new_time;
    return formatted_time.str();
}

unsigned int get_total_correct(
        const std::vector<std::shared_ptr<ItemSpawn>> &spawn_list) {
    if (spawn_list.size() <= 1) {
        return 0U;
    }
    auto beg = spawn_list.cbegin();
    auto end = spawn_list.cend();
    return std::count_if(beg, end,
            [](const std::shared_ptr<ItemSpawn> &spawn) {
                return spawn->is_answer_correct();
            });
}

float calc_average(const std::vector<std::shared_ptr<ItemSpawn>> &spawn_list) {
    if (spawn_list.size() <= 1) {
        return 0.0;
    }
    std::vector<float> duration_list;

    for (const auto spawn : spawn_list) {
        duration_list.push_back(spawn->get_answer_duration());
    }

    // Ignore latest (invalid) ItemSpawn
    return std::accumulate(duration_list.cbegin(),
                           duration_list.cend() - 1,
                           0.0) /
            (duration_list.size() - 1);
}
