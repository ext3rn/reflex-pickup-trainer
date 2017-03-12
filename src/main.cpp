#include <iostream>
#include <cstdlib>
#include <memory>
#include <vector>
#include <iomanip>

#include "PickupSettings.h"
#include "ItemSpawn.h"

using std::cout;
using std::cin;
using std::endl;

int main() {
    // Initialize settings
    std::shared_ptr<PickupSettings> settings(new PickupSettings);

    std::vector<std::shared_ptr<ItemSpawn>> spawn_list;

    while (true) {
        spawn_list.emplace_back(new ItemSpawn(settings));
        auto &spawn = *spawn_list.back();

        cout << spawn.get_item_name() << ": " << spawn.get_old_time() << endl;
        cout << "Answer: ";

        std::string str_answer;
        if (!(cin >> str_answer) || str_answer == "q") {
            cout << "\nCorrect answers: " << get_total_correct(spawn_list)
                 << "/" << spawn_list.size() - 1 << endl;
            cout << "Average time taken: " << calc_average(spawn_list)
                 << " seconds" << endl;
            return EXIT_SUCCESS;
        }

        unsigned int uint_answer = std::stoul(str_answer, nullptr, 10);

        spawn.answer(uint_answer);

        if (spawn.is_answer_correct()) {
            cout << "Correct!" << endl;
        } else {
            cout << "Wrong! " << spawn.get_new_time() << endl;
        }
        cout << "Time taken: " << std::fixed << std::setprecision(2)
             << spawn.get_answer_duration() << " seconds" << endl
             << endl;
    }

    return EXIT_SUCCESS;
}
