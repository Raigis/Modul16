#include <iostream>
#include <chrono>
#include <thread>
#include <sstream>

using namespace std::chrono_literals;
using namespace std::this_thread;

enum switches {
    LIGHTS_INSIDE = 1, 
    LIGHTS_OUTSIDE = 2, 
    HEATERS = 4, 
    WATER_PIPE_HEATING = 8, 
    CONDITIONER = 16
};

std::string enter() {
    std::string input;
    std::cout << "Temperature inside, temperature outside, movement, lights:\n" ;
    std::getline(std::cin, input);
    return input;
}

void temp_in_check(int &tempIn, int &switchesState){
    if (!(switchesState & HEATERS) && tempIn < 22) {
        switchesState |= HEATERS;
        std::cout << "Heaters ON!\n";
    } else if (switchesState & HEATERS && tempIn > 25) {
        switchesState &= ~HEATERS;
        std::cout << "Heaters OFF!\n";
    } 
    if (!(switchesState & CONDITIONER) && tempIn >= 30) {
        switchesState |= CONDITIONER;
        std::cout << "Conditioner ON!\n";
    } else if (switchesState & CONDITIONER && tempIn <= 25) {
        switchesState &= ~CONDITIONER;
        std::cout << "Conditioner OFF!\n";
    }
}

void temp_out_check(int &tempOut, int &switchesState) {
    if (!(switchesState & WATER_PIPE_HEATING) && tempOut < 0) {
        switchesState |= WATER_PIPE_HEATING;
        std::cout << "Water pipe heating ON!\n";
    } else if (switchesState & WATER_PIPE_HEATING && tempOut > 5) {
        switchesState &= ~WATER_PIPE_HEATING;
        std::cout << "Water pipe heating OFF!\n";
    }
}

void ligths_out_check (std:: string &answerMov, int &switchesState, int &hour) {
    if(!(switchesState & LIGHTS_OUTSIDE) && (hour >= 16 || hour <= 5) && answerMov == "yes") {
        switchesState |= LIGHTS_OUTSIDE;
        std::cout << "Lights outside ON!\n";
    } else if(switchesState & LIGHTS_OUTSIDE && ((hour < 16 && hour > 5) || answerMov == "no")) {
        switchesState &= ~LIGHTS_OUTSIDE;
        std::cout << "Lights outside OFF!\n";
    }
}

void lights_in_check (std::string &answerLight, int &switchesState) {
     if (!(switchesState & LIGHTS_INSIDE) && answerLight == "on") {
        switchesState |= LIGHTS_INSIDE;
        std::cout << "Lights inside ON!\n";
    } else if (switchesState & LIGHTS_INSIDE && answerLight == "off") {
        switchesState &= ~LIGHTS_INSIDE;
        std::cout << "Lights inside OFF!\n";
    }
}

void switches_check(int &tempIn, int &tempOut, std::string &answerMov, std::string &answerLight, int &switchesState, int hour) {
    std::cout << "\033[2J";
    std::cout << "\033[0;0f";
    temp_in_check(tempIn, switchesState);
    temp_out_check(tempOut, switchesState);
    ligths_out_check (answerMov, switchesState, hour);
    lights_in_check (answerLight, switchesState);
    sleep_for(3s);
    std::cout << "\033[2J";
    std::cout << "\033[0;0f";
}

void request (int &switchesState, int &hour) {
    int tempIn, tempOut;
    std:: string answerMov, answerLight;
    std::stringstream enterStream(enter());
    enterStream >> tempIn >> tempOut >> answerMov >> answerLight;
    switches_check(tempIn, tempOut, answerMov, answerLight, switchesState, hour);
}

void switches_print (int &switchesState, double &tempColor) {
    std::cout << "Light inside: ";
    if (switchesState & LIGHTS_INSIDE) {
        std::cout << "on\tColor temperature: " << (int)tempColor << "K\n";
    } else {
        std::cout << "off\n";
    }
    std::cout << "Light outside: ";
    if (switchesState & LIGHTS_OUTSIDE) {
        std::cout << "on\n";
    } else {
        std::cout << "off\n";
    }
    std::cout << "Heaters: ";
    if (switchesState & HEATERS) {
        std::cout << "on\n";
    } else {
        std::cout << "off\n";
    }
    std::cout << "Water pipe heating: ";
    if (switchesState & WATER_PIPE_HEATING) {
        std::cout << "on\n";
    } else {
        std::cout << "off\n";
    }
    std::cout << "Conditioner: ";
    if (switchesState & CONDITIONER) {
        std::cout << "on\n";
    } else {
        std::cout << "off\n";
    }
    
}

void count_time (std::string &time) {
    time[4] != '9' ? time[4] = (char)(((int)time[4])+1) : 
    (time[4] = '0', time[3] != '5' ? time[3] = (char)(((int)time[3])+1) : 
    (time[3] = '0', time[1] != '9' && !(time[0] == '2' && time[1] == '3') ? time[1] = (char)(((int)time[1])+1) :
    (time[1] = '0', time[0] != '2' ? time[0] = (char)(((int)time[0])+1) :
    (time[4] = '0', time[3] = '0', time[1] = '0', time[0] = '0'))));
}

int main () {
    std::string time;
    std::cout << "Enter the start time of tracking: ";
    std::getline(std::cin, time);
    int switchesState = 0;
    double tempColor = 5000;
    for (int workTime = 0; workTime <= 2880; workTime++) {
        std::cout << "\033[2J";
        std::cout << "\033[0;0f"; 
        std::cout << time << "\n";
        int hour = std::stoi(time);
        if (workTime % 60 == 0) {
            request(switchesState, hour);
        }
        if (hour >= 16 && hour < 20) {
            tempColor -= 9.584;
            if (tempColor < 2700) tempColor = 2700;
        } else if (time == "00:00") {
            tempColor = 5000;
        }
        switches_print(switchesState, tempColor);     
        count_time(time);
        sleep_for(250ms);
    }
}