#include "functions.hpp"

int calculate_samples(int duration, int sample_speed){
    return (sample_speed*duration)/1000;
}

void extract_notes(Note vect_note[], int &note_limit, string file_name, int song_duration, int sample_speed){
    string line;
    ifstream music_sheet;
    music_sheet.open(file_name);
    getline(music_sheet, line); // lee la duracion total 
    song_duration = stoi(line);
    while (!music_sheet.eof()){
        getline(music_sheet, line, '\t');
        vect_note[note_limit].name = line;
        getline(music_sheet, line);
        vect_note[note_limit].sample_limit = calculate_samples(stoi(line), sample_speed);
        note_limit++;
    }
    music_sheet.close();
}