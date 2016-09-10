#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <string>

#include "utils.h"

class File
{
    public:

        File();
        File(std::string, std::string);

        //~File();

        std::string getName(void);
        void setName(std::string name);

        std::string getSerie(void);
        void setSerie(std::string serie);

        int getSerieIndex(void);
        void setSerieIndex(int);

        std::string getCharNumber(void);
        void setCharNumber(std::string);

        std::string getCharZero(void);
        void setCharZero(std::string);

        std::string getNumber(void);
        void setNumber(std::string number);

        std::string getCharSeason(void);
        void setCharSeason(std::string);

        std::string getSeason(void);
        void setSeason(std::string season);

        std::string getExtension(void);
        void setExtension(std::string extension);

        std::string getFolder(void);
        void setFolder(std::string);

        File* getNextFile(void);
        void setNextFile(File* file);



        int computeSerie(SerieList);

        void computeNumber(Serie);

        void computeSeason(Serie);

        bool computeExtension(Serie);

        bool computeFile(SerieList);

    private:

        std::string f_name;
        std::string f_serie;
        int f_serie_index;
        std::string f_char_number;
        std::string f_char_zero;
        std::string f_number;
        std::string f_char_season;
        std::string f_season;
        std::string f_extension;
        std::string f_folder;
        File* f_nextFile;
};


std::vector<std::string> renameFiles(File**, SerieList, int, std::string);

#endif
