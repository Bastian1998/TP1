#ifndef FUNCIONES_H
#define FUNCIONES_H
#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include <cmath>
const int MAX_NOTE = 170;
struct Note{
    string name;
    float frecuency;
    int sample_limit;
};
void extract_notes(Note vect_note[], int &note_limit, string file_name, int song_duration, int sample_speed);
int calculate_samples(int duration, int sample_speed);
#endif