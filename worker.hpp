//
//  worker.hpp
//  lab 9 zavd 2
//
//  Created by USER on 15.03.2025.
//

#ifndef worker_hpp
#define worker_hpp

#include <stdio.h>


#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <cstdio>

struct Worker {
    char Name[50];
    char Pos[50];
    int Year;
    int Month;
};


void addWorker();
void showWorkers();
void deleteWorkerByIndex(int index);
void deleteWorkerByName(const std::string& name);
int calculateExperience(int year, int month);



