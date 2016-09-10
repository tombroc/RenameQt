#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <vector>

class Serie
{
    public:

        Serie();
        Serie(int, std::string*, std::string, int, int, int, bool, std::string, int, int, int, bool, std::string, std::string, int, bool);

        //~Serie();
        int getIndex(void);
        void setIndex(int);

        std::string* getOldName(void);
        void setOldName(std::string*);

        std::string getName(void);
        void setName(std::string);

        int getRegexSeasonTrimLeft(void);
        void setRegexSeasonTrimLeft(int);

        int getRegexSeasonTrimRight(void);
        void setRegexSeasonTrimRight(int);

        bool getBoolSeason(void);
        void setBoolSeason(bool);

        std::string getRegexSeason(void);
        void setRegexSeason(std::string);

        int getRegexNumberTrimLeft(void);
        void setRegexNumberTrimLeft(int);

        int getRegexNumberTrimRight(void);
        void setRegexNumberTrimRight(int);

        bool getBoolNumber(void);
        void setBoolNumber(bool);

        std::string getRegexNumber(void);
        void setRegexNumber(std::string);

        std::string getRegexExtension(void);
        void setRegexExtension(std::string);

        Serie* getNext(void);
        void setNext(Serie*);

        int getNbOldName(void);
        void setNbOldName(int);

        bool getBoolZero(void);
        void setBoolZero(bool);

        int getNbCharSeason(void);
        void setNbCharSeason(int);

        int getNbCharNumber(void);
        void setNbCharNumber(int);

        //Check if an "old name" is part of this serie
        bool isSerie(std::string);
        void printSerie(void);

    private:
        int s_index;
        int s_nboldname;
        std::string* s_oldname = new std::string;
        std::string s_name;
        int s_nbCharSeason;
        int s_regex_season_trim_left;
        int s_regex_season_trim_right;
        bool s_bool_season;
        std::string s_regex_season;
        int s_nbCharNumber;
        int s_regex_number_trim_left;
        int s_regex_number_trim_right;
        bool s_bool_number;
        std::string s_regex_number;
        std::string s_regex_extension;
        bool s_bool_zero;
        Serie *s_nextSerie;
};

class SerieList
{
    public:
        SerieList();
        SerieList(Serie*, int);
        //~SerieList();
        // Go through all the series and look for the good one
        int getMatchSerie(std::string);
        // Return the number of series in the list
        int getLength();
        void setLength(int);
        Serie* getSerieList(void);
        void setSerieList(Serie* seriesList);
        Serie* getNextSerie(Serie* s);
        void setNextSerie(Serie*);
        void addSerie(Serie* serie);
        void printSerieList(void);
        Serie* getSerieFromIndex(int);
    private:
        int sl_length;
        Serie *sl_seriesList;

};

bool checkExtension(std::string);
std::vector<std::string> renameFiles(std::string, SerieList);
SerieList parseSeriesCSV(void);

#endif
