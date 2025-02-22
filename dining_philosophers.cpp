#include <iostream>
#include <thread>
#include <mutex>
#include <ncurses.h>
#include <string>
#include <atomic>
#include <unistd.h> // usleep
#include <chrono> // for tracking time
using namespace std;

enum State { THINKING, WAITING, EATING }; // possible states for philosophers

const int MAX_PHILOSOPHERS = 20;
const int FULLNESS_THRESHOLD = 30.0; // eating time to be "full" (in seconds)
const int TICKS_NUM = 20;
chrono::steady_clock::time_point START_TIME;
int num_philosophers;
atomic<int> available_seats;

State ph_state[MAX_PHILOSOPHERS];                                         // table of states of philosophers
float ph_eating_time[MAX_PHILOSOPHERS];                                   // total time spent on eating by philosophers (in seconds)
float ph_thinking_time[MAX_PHILOSOPHERS];                                 // total time spent on thinking by philosophers (in seconds)
float ph_waiting_time[MAX_PHILOSOPHERS];                                  // total time spent on waiting by philosophers (in seconds)
chrono::steady_clock::time_point ph_waiting_start_time[MAX_PHILOSOPHERS]; // tracking starting times of WAITING

mutex forks[MAX_PHILOSOPHERS];       // mutexes for forks
mutex mtx;                           // mutex for changing states
mutex output_mtx;                    // mutex for sync displaying
mutex checking;                      // mutex for checking available seats in dining room

void change_state(int ph_id, State state) {
    lock_guard<mutex> lock(mtx);
    ph_state[ph_id] = state;
}

// converting state to string (for displaying purposes)
string state_to_string(State state) {
    switch (state) {
    case THINKING:
        return "Thinking ";
    case WAITING:
        return "Waiting  ";
    case EATING:
        return "Eating   ";
    default:
        return "Unknown  ";
    }
}

void think(int ph_id, int duration) {
    change_state(ph_id, THINKING);
    usleep(duration * 100000);
    ph_thinking_time[ph_id] += duration / 10.0;
}

void eat(int ph_id, int duration) {
    change_state(ph_id, EATING);

    // eat in 0.1s intervals to update progress
    for (int i = 0; i < duration * 10; ++i) {
        if (ph_eating_time[ph_id] >= FULLNESS_THRESHOLD) {break;} // stop eating if full

        {
            lock_guard<mutex> lock(output_mtx);
            ph_eating_time[ph_id] += 0.1;
        }
        usleep(100000); // 0.1 second
    }
}

void take_forks(int ph_id) {
    if (ph_state[ph_id] != WAITING) {
        change_state(ph_id, WAITING);
        ph_waiting_start_time[ph_id] = chrono::steady_clock::now();
    }

    // check if there are available seats, if not - wait 0.05s and try again
    {
        lock_guard<mutex> lock(checking);
        if (available_seats <= 0) {
            usleep(50000);
            return;
        }
        available_seats--;
    }

    int left_fork = ph_id;
    int right_fork = (ph_id + 1) % num_philosophers;
    {
        lock_guard<mutex> first_lock(forks[left_fork]);
        lock_guard<mutex> second_lock(forks[right_fork]);

        float waiting_duration = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - ph_waiting_start_time[ph_id]).count() / 1000.0;
        ph_waiting_time[ph_id] += waiting_duration;

        eat(ph_id, 1); // eat for 1 second
    }

    available_seats++;
}

void philosopher(int ph_id) {
    while (ph_eating_time[ph_id] < FULLNESS_THRESHOLD) {
        if (ph_state[ph_id] != WAITING) {think(ph_id, rand() % 20 + 1);} // thinking (0.1-2.0 seconds), but only if he isn't waiting
        take_forks(ph_id);                                               // try taking forks (check if there are available seats)
    }
}

void display() {
    while (true) {
        clear();
        bool all_full = true;
        mvprintw(0, 0, "PHILOSOPHER:\tSTATE:\t\tEATING TIME:\tTOTAL WAITING TIME:\tTOTAL THINKING TIME:\tPROGRESS:");

        {
            lock_guard<mutex> lock(output_mtx);
            for (int i = 0; i < num_philosophers; i++) {
                int progress = (ph_eating_time[i] * TICKS_NUM) / (FULLNESS_THRESHOLD);
                string progress_bar = string(progress, '#') + string(TICKS_NUM - progress, '-');
                
                mvprintw(i + 1, 0, "%d.\t\t%-10s\t%-10.1f\t%-10.1f\t\t%-10.1f\t\t[%s]", i + 1, state_to_string(ph_state[i]).c_str(), ph_eating_time[i], ph_waiting_time[i], ph_thinking_time[i], progress_bar.c_str());

                if (ph_eating_time[i] < FULLNESS_THRESHOLD) {all_full = false;}
            }
        }
        float elapsed_time = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - START_TIME).count() / 1000.0;
        mvprintw(num_philosophers + 2, 0, "Runtime: %-10.1f seconds", elapsed_time);

        refresh();
        usleep(50000); // refreshing screen at 0.05s rate

        if (all_full) {break;} // if all philosophers are full (finished eating)

    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <num_philosophers>\n";
        return 1;
    }

    num_philosophers = stoi(argv[1]);
    if (num_philosophers < 5 || num_philosophers > MAX_PHILOSOPHERS) {
        cerr << "Number of philosophers must be between 5 and " << MAX_PHILOSOPHERS << ".\n";
        return 1;
    }

    // initiating ncurses and run-time tracking
    START_TIME = chrono::steady_clock::now();
    initscr();
    noecho();
    curs_set(0);

    // initiating states and counters (all philosophers start from thinking)
    for (int i = 0; i < num_philosophers; i++) {
        ph_state[i] = THINKING;
        ph_eating_time[i] = 0.;
        ph_waiting_time[i] = 0.;
        ph_thinking_time[i] = 0.;
    }
    available_seats = num_philosophers - 1;

    // creating threads for philosophers
    thread philosophers[MAX_PHILOSOPHERS];
    for (int i = 0; i < num_philosophers; i++) {
        philosophers[i] = thread(philosopher, i);
    }

    // creating thread for displaying
    thread screen(display);

    // joining philosopher threads
    for (auto &ph : philosophers) {
        if (ph.joinable()) {ph.join();}
    }

    if (screen.joinable()) {screen.join();} // joining screen thread

    printw("\n\nAll philosophers finished eating, press any key to exit...\n");
    refresh();
    getch();
    endwin(); // ncurses end

    return 0;
}
