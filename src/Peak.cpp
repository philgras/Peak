/*
 * peak.cpp
 *
 *  Created on: 10.02.2016
 *      Author: philgras
 */

//#include "Server.h"

//using namespace Peak;
#include "Server.h"
#include <iostream>
#include <algorithm>
#include <cctype>

namespace Peak{

	const char ASCII_LOGO[] = {
		'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','\n','\n','\n',
		' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\n',
		' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\n',
		' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\n',
		' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\n',
		' ',' ',' ',' ',' ',' ',' ',' ','#','#','#','#','#','#','#','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ','\n',
		' ',' ',' ',' ',' ',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ',' ',' ',' ',' ',' ','\n',
		' ',' ',' ',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ',' ',' ',' ','\n',
		' ',' ',' ',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ',' ',' ',' ','\n',
		' ',' ',' ',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ',' ',' ',' ','\n',
		' ',' ',' ',' ',' ',' ','#','#','#','#','#',' ','#','#',' ','#','#','#','#','#',' ',' ',' ',' ',' ',' ','\n',
		' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\n',
		' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\n','\n','\n',
		'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','\n',
		'#','#','#','#','#','#','#','#','#','#',' ','P','E','A','K',' ','#','#','#','#','#','#','#','#','#','#','\n',
		'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','\n','\n','\0'};


void commandLineRoutine();

}


int main(int n, char** c){

	if(n > 0){

		std::cout<<Peak::ASCII_LOGO;
		Peak::commandLineRoutine();
	}

	return 0;

}

void Peak::commandLineRoutine(){

	const char* START_COMMAND = "start";
	const char* STOP_COMMAND = "stop";
	const char* INFO_COMMAND = "info";
	const char* HELP_COMMAND = "help";
	const char* QUIT_COMMAND = "quit";

	bool quit = false;
	std::string input;
	Peak::Server& server = Peak::Server::getInstance();

	do{
		std::cout<<"\n> ";
		std::cout.flush();

		std::cin>>input;

		std::transform(input.begin(),input.end(),input.begin(),tolower);

		if(input == START_COMMAND){
			std::cout<<"Starting the server..."<<std::endl;
			server.start();

		}else if(input == STOP_COMMAND){
			std::cout<<"Stopping the server..."<<std::endl;
			server.shutdown();

		}else if(input == INFO_COMMAND){
			std::cout<<"Server information..."<<std::endl;
			std::cout<<server.getInfo();

		}else if(input == QUIT_COMMAND){
			if(server.isRunning())
				server.shutdown();
			quit = true;

		}else if(input == HELP_COMMAND){
			std::cout<<"Commands: start | stop | info | help | quit "<<std::endl;
		}else{
			std::cout<<"Invalid input: "<<input<<std::endl;
		}

	}while(!quit);


}



