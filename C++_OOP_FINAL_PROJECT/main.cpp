#include <iostream>
#include <cstring>
using namespace std;

struct State {
    char color[10];
    int duration;
};


class TrafficLightBase {
public:
    State* states;
    int stateCount;
    int currentIndex;

    TrafficLightBase() {
        states = NULL;
        stateCount = 0;
        currentIndex = 0;
    }

    virtual ~TrafficLightBase() {
        delete[] states;
    }


    virtual void cycle() = 0;
};


class StandardTrafficLight : public TrafficLightBase {
public:
    StandardTrafficLight() {
        stateCount = 3;
        states = new State[stateCount];

        strcpy(states[0].color, "Green");
        states[0].duration = 60;

        strcpy(states[1].color, "Yellow");
        states[1].duration = 5;

        strcpy(states[2].color, "Red");
        states[2].duration = 55;

        currentIndex = 0;
    }

    void cycle() {
        cout << "[Standard] " << states[currentIndex].color << " for " << states[currentIndex].duration << " sec" << endl;
        currentIndex = (currentIndex + 1) % stateCount;
    }
};


class PedestrianTrafficLight : public TrafficLightBase {
public:
    PedestrianTrafficLight() {
        stateCount = 2;
        states = new State[stateCount];

        strcpy(states[0].color, "Walk");
        states[0].duration = 30;

        strcpy(states[1].color, "Don't Walk");
        states[1].duration = 30;

        currentIndex = 0;
    }

    void cycle() {
        cout << "[Pedestrian] " << states[currentIndex].color << " for " << states[currentIndex].duration << " sec" << endl;
        currentIndex = (currentIndex + 1) % stateCount;
    }
};


class TrafficLightManager {
private:
    TrafficLightBase** controllers;
    int size;

public:
    TrafficLightManager() {
        controllers = NULL;
        size = 0;
    }

    ~TrafficLightManager() {
        for (int i = 0; i < size; ++i) {
            delete controllers[i];
        }
        delete[] controllers;
    }

    void addController(TrafficLightBase* controller) {
        TrafficLightBase** newControllers = new TrafficLightBase*[size + 1];
        for (int i = 0; i < size; ++i) {
            newControllers[i] = controllers[i];
        }
        newControllers[size] = controller;
        delete[] controllers;
        controllers = newControllers;
        size++;
    }

    void removeController(int index) {
        if (index < 0 || index >= size) return;
        delete controllers[index];
        TrafficLightBase** newControllers = new TrafficLightBase*[size - 1];
        for (int i = 0, j = 0; i < size; ++i) {
            if (i != index) {
                newControllers[j++] = controllers[i];
            }
        }
        delete[] controllers;
        controllers = newControllers;
        size--;
    }

    void runCycles(int rounds) {
        for (int r = 0; r < rounds; ++r) {
            cout << "--- Round " << r + 1 << " ---" << endl;
            for (int i = 0; i < size; ++i) {
                controllers[i]->cycle();
            }
        }
    }
};


int main() {
    TrafficLightManager manager;

    manager.addController(new StandardTrafficLight());
    manager.addController(new PedestrianTrafficLight());

    manager.runCycles(5); // run 5 cycles

    manager.removeController(1); // remove pedestrian light
    manager.runCycles(3); // run 3 more cycles

    return 0;
}

