#ifndef LTIME_H_
#define LTIME_H_

#include <SDL2/SDL.h>


class Timer {
    public:
        //Initializes variables
        Timer(void);

        //The various clock actions
        void start(void);
        void stop(void);
        void pause(void);
        void unpause(void);

        //Gets the timer's time
        Uint32 getTicks(void);

        //Checks the status of the timer
        bool isStarted(void);
        bool isPaused(void);

    private:
        //The clock time when the timer started
        Uint32 startTicks;

        //The ticks stored when the timer was paused
        Uint32 pausedTicks;

        //The timer status
        bool paused;
        bool started;
};

Timer::Timer() {
    //Initialize the variables
    startTicks = 0;
    pausedTicks = 0;

    paused = false;
    started = false;
}

void Timer::start() {
    //Start the timer
    started = true;

    //Unpause the timer
    paused = false;

    //Get the current clock time
    startTicks = SDL_GetTicks();
    pausedTicks = 0;
}

void Timer::stop() {
    //Stop the timer
    started = false;

    //Unpause the timer
    paused = false;

    //Clear tick variables
    startTicks = 0;
    pausedTicks = 0;
}

void Timer::pause() {
    //If the timer is running and isn't already paused
    if(started && !paused) {
        //Pause the timer
        paused = true;

        //Calculate the paused ticks
        pausedTicks = SDL_GetTicks() - startTicks;
        startTicks = 0;
    }
}

void Timer::unpause() {
    //If the timer is running and paused
    if(started && paused) {
        //Unpause the timer
        paused = false;

        //Reset the starting ticks
        startTicks = SDL_GetTicks() - pausedTicks;

        //Reset the paused ticks
        pausedTicks = 0;
    }
}

Uint32 Timer::getTicks() {
    //The actual timer time
    Uint32 time = 0;

    //If the timer is running
    if(started) {
        //If the timer is paused
        if(paused) {
            //Return the number of ticks when the timer was paused
            time = pausedTicks;
        } else {
            //Return the current time minus the start time
            time = SDL_GetTicks() - startTicks;
        }
    }

    return time;
}

bool Timer::isStarted() {
    //Timer is running and paused or unpaused
    return started;
}

bool Timer::isPaused() {
    //Timer is running and paused
    return paused && started;
}

#endif