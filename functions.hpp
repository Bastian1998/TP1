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
    double frequency;
    int sample_quant;
};
int extract_notes(Note vect_note[], int &note_limit, string file_name, int song_duration, int sample_speed);
int calculate_sample_quant(int duration, int sample_speed);
void count_letters(char letter, int &steps, int number);
void count_numbers(char letter, int &steps, int number);
int count_steps(string note);
void add_frequency(Note vect_note[], int note_limit);
void initialize_wav(ofstream &wav_file, int song_duration, int sample_speed, short int bits );
void load_wav(Note vect_note[], int note_quant, string file_name, int song_duration, int sample_speed, short int bits);
#endif