// AudioEncoder.cpp : This file contains the 'main' function. Program execution begins and ends there.

#pragma warning(disable:4996)
#include "MultiThreadHandler.h"
#include <cstdlib>
#include <dirent.h>
#include <lame/lame.h>
#include <fstream>

#define WAV_SIZE    8192
#define MP3_SIZE    8192
#define SAMPLE_RATE 44100
#define LAME_GOOD 0

static std::vector<std::string> ReadFilesFromDirectory(std::string &myDir);
static std::string GetFileWithSpcificExt(std::string file, std::string extinsion);
static void mp3ToWaveConverter(std::string& wavInput);

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Invalid Path!" << '\n';
        std::cout << "Please Enter " << argv[0] << " and a valid directory";
        return 0;
    }
    std::string input_dir = argv[1];
    std::vector<std::string> directory = ReadFilesFromDirectory(input_dir);
    if (!directory.empty())
    {
        MultiThreadHandler audioEncoder(directory, mp3ToWaveConverter);
    }
    else
    {
        std::cout << "Empty Directory!" << '\n';
    }
    return 0;
}

static std::vector<std::string> ReadFilesFromDirectory(std::string &myDir)
{
    std::vector<std::string> directory;
    DIR* dir = nullptr;
    struct dirent* entry;
    dir = opendir(myDir.c_str());
    if (dir == nullptr)
    {
        std::cout<<"Can't open the directory"<<'\n';
    }
    else
    {
        while ((entry = readdir(dir)) != NULL)
        {
            std::string fileName = entry->d_name;
            fileName = GetFileWithSpcificExt(fileName, ".wav");
            if (fileName != "DEADSTRING")
            {
                fileName = myDir + "/" + fileName;
                directory.push_back(fileName);
            }
        }
        closedir(dir);
    } 
    return directory;
}

static std::string GetFileWithSpcificExt(std::string file, std::string extinsion)
{
    std::transform(file.begin(), file.end(), file.begin(), ::tolower);
    if (file.length() < extinsion.length()+1)
    {
        return "DEADSTRING";
        
    }
    else
    {
        if (file.substr(file.find_last_of("."))  == extinsion)
        {
            return file;  
        }
        else
        {
            return "DEADSTRING";
        }
    }
}


static void printQueue(std::string& input)
{
    std::cout << "Your string is " << input << '\n';
}

static void mp3ToWaveConverter(std::string& wavInput)
{
    static int count = 0;
    int read, write;
    std::string mp3Output = wavInput.substr(0, wavInput.find_last_of('.')) + ".mp3";
    FILE* wav = fopen(wavInput.c_str(), "rb");
    FILE* mp3 = fopen(mp3Output.c_str(), "wb");
    if (wav != NULL && mp3 != NULL)
    {
        short int* wav_buffer = new short int[WAV_SIZE*2];
        unsigned char* mp3_buffer = new unsigned char[MP3_SIZE];
        lame_t lame = lame_init();
        lame_set_in_samplerate(lame, SAMPLE_RATE);
        lame_set_VBR(lame, vbr_default);
        lame_set_VBR_q(lame, LAME_GOOD);
        lame_set_num_channels(lame, 1);
        lame_set_mode(lame, JOINT_STEREO);
        lame_set_brate(lame, 128);
        lame_init_params(lame);  

        do 
        {
            read = fread(wav_buffer, 2 * sizeof(short int), WAV_SIZE, wav);
            if (read == 0)
            {
                write = lame_encode_flush(lame, mp3_buffer, MP3_SIZE);
            }
            else
            {
                write = lame_encode_buffer_interleaved(lame, wav_buffer, read, mp3_buffer, MP3_SIZE);
            }     
            fwrite(mp3_buffer, write, 1, mp3);
        } while (read != 0);

        lame_close(lame);
        fclose(mp3);
        fclose(wav);
        delete [] wav_buffer;
        delete[] mp3_buffer;
        std::cout<<"Converted items: "<<++count<<"\n";
    }
    else
    {
        std::cout << "Unable to open read/write files'\n'";
        return;
    }
}