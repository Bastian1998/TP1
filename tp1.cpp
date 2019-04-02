#include "functions.hpp"

int main(){ // int argc , const char *argv[]
    Note vect_note[MAX_NOTE];
    int note_limit = 0;
    int song_duration = 0;
    string file_name = "prueba.txt";
    int sample_speed = 8000;
    extract_notes(vect_note, note_limit, file_name, song_duration, sample_speed);
    return 0;
}