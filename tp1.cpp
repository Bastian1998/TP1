#include "functions.hpp"

int main(){ // int argc , const char *argv[]
    Note vect_note[MAX_NOTE];
    int note_quant = 0;
    int song_duration = 0;
    string file_name = "prueba.txt";
    string file_name_wav = "song.wav";
    int sample_speed = 8000;
    short int bits = 8;
    song_duration = extract_notes(vect_note, note_quant, file_name, song_duration, sample_speed);
    add_frequency(vect_note, note_quant);
    load_wav(vect_note, note_quant, file_name_wav, song_duration, sample_speed, bits);
    return 0;
}