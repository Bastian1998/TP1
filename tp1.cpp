#include "functions.hpp"

int main(int argc, const char *argv[]){
     // int argc , const char *argv[]
     if (argc < 1)
        return -1;
    Note vect_note[MAX_NOTE];
    int note_quant = 0;
    int song_duration = 0;
    string file_name = argv[1];
    string file_name_wav = argv[2];
    int sample_speed = stoi(argv[4]);
    short int bits = (short) stoi(argv[3]);
    song_duration = extract_notes(vect_note, note_quant, file_name, song_duration, sample_speed);
    add_frequency(vect_note, note_quant);
    load_wav(vect_note, note_quant, file_name_wav, song_duration, sample_speed, bits);
    return 0;
}