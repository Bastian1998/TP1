#include "functions.hpp"
//Calcula  la cantidad de muestras de una nota segun su duracion
int calculate_sample_quant(int duration, int sample_speed){
    return  (sample_speed*duration)/1000;
}
//Extrae informacion de un archivo de texto y lo envia a un vector de struct, tambien retorna la duracion total de  la cancion
int extract_notes(Note vect_note[], int &note_quant, string file_name, int song_duration, int sample_speed){
    string line;
    ifstream music_sheet;
    music_sheet.open(file_name);
    getline(music_sheet, line); // lee la duracion total 
    song_duration = stoi(line);
    while (!music_sheet.eof()){
        getline(music_sheet, line, '\t');
        vect_note[note_quant].name = line;
        getline(music_sheet, line);
        vect_note[note_quant].sample_quant = calculate_sample_quant(stoi(line), sample_speed);
        note_quant++;
    }
    music_sheet.close();
    return song_duration;
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
void add_frequency(Note vect_note[], int note_quant){
    double exponent = 0;
    double base_freq = 27.5;
    double constant = 0;
    int steps = 0;
    for (int i = 0; i < note_quant; i++){
        if (vect_note[i].name != "H"){
            steps = count_steps(vect_note[i].name);
            exponent = steps/12.0;
            constant = pow(2.0, exponent);
            vect_note[i].frequency = (double) (base_freq * constant);
        }else
            vect_note[i].frequency = 0;     
    }
}
// Carga el formato del archivo wav
void initialize_wav(ofstream &wav_file, int song_duration, int sample_speed, short int bits ){
    int file_size = ((song_duration*sample_speed)/1000) + 36;
    int chunk_format_size = 16;
    short int audio_format = 1;
    short int cc = 1;
    short int bytes_rate = short(sample_speed * cc * bits) / 8;
    short int block_align = short(bits * cc) / 8;
    int chunk_data_size = ((sample_speed*song_duration)/1000) + 8;
    wav_file << "RIFF";
    wav_file.write((char*) &(file_size), sizeof(int));
    wav_file << "WAVE";
    wav_file << "fmt ";
    wav_file.write ((char*) &(chunk_format_size), sizeof(int));
    wav_file.write ((char*) &(audio_format), sizeof(short int));
    wav_file.write ((char*) &(cc), sizeof(short int));
    wav_file.write ((char*) &(sample_speed), sizeof(int));
    wav_file.write ((char*) &(bytes_rate), sizeof(int));
    wav_file.write ((char*) &(block_align), sizeof(short int));
    wav_file.write ((char*) &(bits), sizeof(short int));
    wav_file << "data";
    wav_file.write ((char*) &(chunk_data_size), sizeof(int));
}
// Crea el archivo wav, le asigna las muestras por nota y aplica fadeout  a las ultimas 25 notas
void load_wav(Note vect_note[], int note_quant, string file_name_wav, int song_duration, int sample_speed, short int bits){
    ofstream wav_file;
    wav_file.open(file_name_wav, ios::binary);
    double sample = 0.0;
    char sample_to_char;
    double amplitude = 127.5;
    double height = 127.5;
    double phase_angle = 0.0;
    double amplitude_aux = 127.5;
    initialize_wav(wav_file, song_duration, sample_speed, bits);
    for (int i = 0; i < note_quant; i++){
        if (i > note_quant - 25)
            amplitude -= (amplitude_aux/25.0);
        for(int s = 0; s < vect_note[i].sample_quant; s++){
            sample = amplitude*sin((2.0 * M_PI * vect_note[i].frequency * s + phase_angle) / (double) sample_speed) + height;
            sample_to_char = (char) sample;
            wav_file.write((char*) &(sample_to_char), sizeof(char));
            if (s  == (vect_note[i].sample_quant) - 1 )
                phase_angle = phase_angle + 2.0 * M_PI * vect_note[i].frequency * (s + 1);
        }
    }
    wav_file.close();
}
    
    

    


