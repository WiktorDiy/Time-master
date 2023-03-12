#include <chrono>
#include <thread>
#include <ctime>
std::chrono::steady_clock::time_point startTime;




void delay(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}
void delay_seconds(int seconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(seconds*1000));
}
void delay_microseconds(int micros) {
    std::this_thread::sleep_for(std::chrono::microseconds(micros));
}

void time_master_setup() {
    startTime = std::chrono::steady_clock::now();
}

unsigned long millis() {
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - startTime);
    return static_cast<unsigned long>(elapsedTime.count());
}

unsigned long micros() {
    auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - startTime);
    return static_cast<unsigned long>(elapsedTime.count());
}
class executeTime {
  private:
    unsigned long previousMillis;
    float interval;
    void (*action)(); 

  public:
    executeTime(float execute_interval, void (*func)()) { 
      interval = execute_interval;
      previousMillis = 0;
      action = func;
    }
    
    void update() {
      unsigned long currentMillis = millis();
      if (currentMillis - previousMillis >= interval*1000) {
        previousMillis = currentMillis;
        (*action)(); 
      }
    }
};

class DT {
public:
    DT(time_t t = time(NULL)) {
        update(t);
    }

    void update(time_t t = time(NULL)) {
    	abs_time = t;
        std::tm* timePtr = localtime(&t);
        year = timePtr->tm_year + 1900;
        month = timePtr->tm_mon + 1;
        day = timePtr->tm_mday;
        hour = timePtr->tm_hour;
        if (hour == 0) {
            hour12 = 12;
            pm = false;
        }
        else if (hour < 12) {
            hour12 = hour;
            pm = false;
        }
        else if (hour == 12) {
            hour12 = 12;
            pm = true;
        }
        else {
            hour12 = hour - 12;
            pm = true;
        }
        minute = timePtr->tm_min;
        second = timePtr->tm_sec;
        DOW = timePtr->tm_wday;
        time_array[0] = year;
    time_array[1] = month;
    time_array[2] = day;
    time_array[3] = hour;
    time_array[4] = hour12;
    time_array[5] = static_cast<int>(pm);
    time_array[6] = minute;
    time_array[7] = second;
    time_array[8] = DOW;
    }
    
	time_t abs_time;
    int year;
    int month;
    int day;
    int hour;
    int hour12;
    bool pm;
    int minute;
    int second;
    int DOW;
    int time_array[9];
    
    
    
};




