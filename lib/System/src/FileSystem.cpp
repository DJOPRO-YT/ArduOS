/*
#include "FileSystem.hpp"

static bool ready = false;

void FileSystem::init()
{
    #ifdef REMAKE_328
    if (!SD.begin(ChipSelect))
    {
        ready = false;
    }else{
        ready = true;
    }
    #endif
}

bool FileSystem::IsFile(const char* path)
{
    if (ready)
    {
        #ifdef REMAKE_328
        File h = SD.open(path);
        if (h.isDirectory())
        {
            return false;
        }
        else
        {
            return true;
        }

        #endif
    }
    return false;
}

bool FileSystem::IsFolder(const char* path)
{
    if (ready)
    {
        #ifdef REMAKE_328
        File h = SD.open(path);
        if (h.isDirectory())
        {
            return true;
        }
        else
        {
            return false;
        }
        
        #endif
    }
    return false;
}

void FileSystem::MKDIR(const char* path)
{
    if (!ready) {return;}

    #ifdef REMAKE_328
    SD.mkdir(path);
    #endif
}

FileSystem::FileOpen::FileOpen(const char* path_,uint8_t mode_)
{
    if (!ready) {return;}
    #ifdef REMAKE_328
    if (root) {root.close();}
    if (mode_ == WRITE) {
    root = SD.open(path_,FILE_WRITE);
    }
    else
    {
    root = SD.open(path_,FILE_READ);
    }
    this->path = path_;
    this->mode = mode_;
    #endif
}

void FileSystem::FileOpen::WriteFile(const char* file)
{
    if (!ready) {return;}
    #ifdef REMAKE_328
    if (mode == WRITE && root)
    {
        root.print(file);
    }
    #endif
}

void FileSystem::FileOpen::Close()
{
    if (!ready) {return;}
    #ifdef REMAKE_328
    if (root)
    {
        root.close();
    }
    #endif
}
const char* FileSystem::FileOpen::ReadLine(uint16_t &index)
{
    if (!ready) {return "";}
    #ifdef REMAKE_328
    if (mode != READ){return "";}
    this->root = SD.open(this->path,FILE_READ);
    uint16_t in = 0;
    static char l[60];
    while (root.available())
    {
        char c = root.read();
        if (in < index)
        {
            if (c == 10)
            {
                in++;
            }
        }
        else
        {
            if (c != 10 || c != 0)
            {
                if (strlen(l) < 60)
                {
                    l[strlen(l)] = c;
                }
                else
                {
                    return l;
                }
            }
            else
            {
                return l;
            }
        }
    }
    #endif
    return "";
}
*/