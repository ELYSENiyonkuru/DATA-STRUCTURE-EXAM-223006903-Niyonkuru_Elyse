 Traffic Light Manager 

---> Task Description

The goal of this program is to simulate a set of traffic lights,

 where each traffic controller cycles through a list of light states.

 The program uses object-oriented principles including inheritance,

 polymorphism, and dynamic memory management.

|
---> Requirements:

1. Define a `State` struct to hold traffic light color and duration.

2. Create an abstract base class `TrafficLightBase` with a pure virtual method cycle().

3. Create two derived classes:

   - StandardTrafficLight (e.g., Green → Yellow → Red)
   - PedestrianTrafficLight (e.g., Walk → Don't Walk)

4. Dynamically allocate each controller’s state array.

5. Use a dynamic array of pointers to controllers (TrafficLightBase).

6. Implement addController() and removeController() functions that resize the controller array.

7. Use pointer arithmetic and cycling logic.

8. Make the program compile and run successfully in **Dev C++** (C++98 standard).


 ---> How It Was Completed

> Implemented State as a struct with a character array and an integer.

> TrafficLightBase is a pure virtual base class with a dynamic array of State.

> StandardTrafficLight` and PedestrianTrafficLight override the cycle() function and initialize their own state arrays.

> A manager class, TrafficLightManager, maintains a dynamic array of `TrafficLightBase*` controllers.

> addController() allocates a new array and copies the old one, then adds the new controller.

> removeController() deletes a controller by index and resizes the array.




// Include required headers librays

   #include <iostream>
   #include <cstring> // For strcpy
   using namespace std;

// Define a struct to represent each light state

     struct State {
    char color[10]; // Name of the light (e.g., "Green", "Red")
    int duration;   // Duration in seconds
    };

// Abstract base class for all traffic lights

    class TrafficLightBase {
     public:
    State* states;   // Dynamic array of states
    int stateCount;  // Number of states
    int currentIndex; // Current state index

// Constructor initializes pointers and counters

    TrafficLightBase() {
        states = NULL;
        stateCount = 0;
        currentIndex = 0;

    }
// Virtual destructor for proper cleanup

    virtual ~TrafficLightBase() {
        delete[] states;
    }


// Pure virtual method to be implemented in derived classes

       virtual void cycle() = 0;
     };


// Standard traffic light (Green → Yellow → Red)

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

// Cycle through light states

        void cycle() {
        cout << "[Standard] " << states[currentIndex].color << " for " << states[currentIndex].duration << " sec" << endl;
        currentIndex = (currentIndex + 1) % stateCount;
    }
      };

// Pedestrian traffic light (Walk ↔ Don't Walk)

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
// Cycle through pedestrian states

         void cycle() {
        cout << "[Pedestrian] " << states[currentIndex].color << " for " << states[currentIndex].duration << " sec" << endl;
        currentIndex = (currentIndex + 1) % stateCount;
       }
      };