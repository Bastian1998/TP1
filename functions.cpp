#include "functions.hpp"
//Calcula  la cantidad de muestras de una nota segun su duracion
int calculate_samples(int duration, int sample_speed){
    return (sample_speed*duration)/1000;
}
//Extrae informacion de un archivo de texto y lo envia a un vector de struct
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
//Cuenta saltos entre letras
void count_letters(char letter, int &steps, int number){
    if (letter == 'B')
        steps += 2;
    else if (letter == 'C')
        steps += 3;
    else if (letter == 'D')
        steps += 5;
    else if (letter == 'E')
        steps += 7;
    else if (letter == 'F')
        steps += 8;
    else if (letter == 'G')
        steps += 10;    
    else if (letter == 'A' and number > 0)
        steps += 12;
}
//Cuenta saltos entre numeros
void count_numbers(char letter, int &steps, int number){
    for (int i = 1; i < 9; i++){
        if (i == number){
            if (letter != 'B')
                steps += (i-1)*12;
            else
                steps += i*12;
        }
    }
}
//Cuenta los saltos entre notas musicales tomando como base A0, la primera nota musical
int count_steps(string note){ 
    int steps = 0, number = 0;
    char letter = note[0];

    if (note.length() == 3){
        steps++;
        number = note[2] - 48; // La tabla ascci inicia en 48
    }else
        number = note[1] - 48;
    count_numbers(letter, steps, number);
    count_letters(letter, steps, number);
    return steps;
}
// Agrega la frecuencia de cada nota al vector de structs
void add_frequency(Note vect_note[], int note_limit){
    double exponent = 0;
    double base_freq = 27.5;
    double constant = 0;
    int steps = 0;
    for (int i = 0; i < note_limit; i++){
        steps = count_steps(vect_note[i].name);
        exponent = steps/12.0;
        constant = pow(2.0, exponent);
        vect_note[i].frequency = (float) (base_freq * constant);
    }
}