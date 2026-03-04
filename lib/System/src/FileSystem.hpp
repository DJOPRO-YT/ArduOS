/*
#ifndef ARDU_FS_H
#define ARDU_FS_H

#ifdef REMAKE_328
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <SD.h>
static const int ChipSelect = 7;
#elif defined(NATIVE)
#include <cstdint>
#endif

namespace FileSystem {
    const uint8_t WRITE = 0;
    const uint8_t READ = 1;
    
    void init();

    // Exist Statement
    bool FolderExist(const char* path);
    bool FileExist(const char* path);

    // Check Statements
    bool IsFolder(const char* path);
    bool IsFile(const char* path);

    void MKDIR(const char* path);
    class FileOpen
    {
        private:
        uint8_t mode;
        File root;
        const char* path;

        public:
        FileOpen(const char* path_,uint8_t mode_);
        void WriteFile(const char* file);
        const char* ReadFile();
        const char* ReadLine(uint16_t &index); //index starting from 0
        void Close();
    };
}

#endif
*/