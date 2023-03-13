/*The time master library implements some functions that many users of arduino boards love plus some extra. This library is almost all that you will ever want when it comes to time.
the list of functions contains:
delay(); waits for given numbers of miliseconds
delay_seconds(); waits for given number of seconds
delay_microseconds(); waits for given number of microseconds
millis(); returns number of miliseconds from the beginning of the program
micros(); returns number of microseconds from the beginning of the program
It also adds two classes: Dt, and execute_Time
The DT class consists of those variables:
time_t abs_time;
    int year;
    int month;
    int day;
    int hour;	in the 24 hour format
    int hour12;	in the 12 hour wierd american format
    bool pm;	wierd americat format pm flag
    int minute;
    int second;
    int DOW;	//sunday is the first day of the weak(starting from 0)
    int time_array[9]; combines al above mentiond elements in an array in the above order
	If in the proces of creating object or running.update member a parameter in time_t format was passed It will be converted to human redable values.
	If no parameter was provided The object will default to current real time.
	
	The second function called executeTime is very simmilar to the blink-without-delay example from arduino IDE. 
	it has .update(); method with no parameters and in it's setup it takes a frequency in seconds(as a float) and a function name to be executed
*/

#include "time_master.h"
#include <iostream>
#include <windows.h>//used just for console out colour
void count();//setup void to handle counts
int cc;//counter variable
int main(){
	DT current_date;
	current_date.update();
	std::cout << current_date.year<<" - "<<current_date.month<< " - "<< current_date.day<<std::endl;
	std::cout << current_date.hour<<" . "<<current_date.minute<<" . "<<current_date.second<<std::endl;
	std::string ispm = (current_date.pm)? "PM" : "AM";
	std::cout << current_date.hour12<<" "<<ispm<<std::endl;
	std::cout << current_date.DOW<<std::endl;
	delay_seconds(10);
	executeTime counter(3, count);//uses execute Time class to run a specific function called "count" at a given frequency in seconds (creates obhect)
	time_master_setup();//sets of millis(); and micros();
	int pm = millis();//previous millis variable
	while (true){
		counter.update();//updates execute time class object as fast as possible to refresh internal millis counter for the "counter" object
		std::cout<<"millis: "<< millis()<<"  Micros:  "<<micros()<<std::endl; //prints out current millis and micros
		if (millis()-pm > 10000){
			pm = millis();
			delay_seconds(2);
		}//the if block checks milllis ahainst previous millis and if diffrence is bigger than 10000 miliseconds (10 seconds) it executes 2 seconds deay
		delay(100);//wait 100 miliseconds
		delay_microseconds(5000);//wait 5000 microseconds
	}
}
void count(){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);//change console out to red
	std::cout<<" | COUNTER:  "<<cc<<"  |"<<std::endl;//prints out counter
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_GREEN);//changes console back to white
    cc++;//increments the counter variable
}
