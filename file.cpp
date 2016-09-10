#include "file.h"
#include <iostream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

vector<string> renameFiles(File *files[], SerieList serie_list, int nbFiles, string directory)
{
    int counter(0);
    vector<string> file_list;
    if (nbFiles != 0)
    {
        //cout << endl << "----- List of computed files -----" << endl << endl;
        for (int i=0;i<nbFiles;i++)
        {
            if (files[i] != NULL)
            {
                //cout << "files[i]->getCharSeason() : " << files[i]->getCharSeason() << " - " << "files[i]->getSeason() : " << files[i]->getSeason() << " - "  << "files[i]->getCharNumber() : " << files[i]->getCharNumber() << " - " << "files[i]->getNumber() : " << files[i]->getNumber() << endl;
                // IMPROVE THE CONDITION
                if (files[i]->getNumber() != "")
                {
                    //cout << "File : " << files[i]->getSerie() << " (name) - " << files[i]->getNumber() << " (number) - " << files[i]->getSeason() << " (season)" << endl;
                    // If some 0 are missing in the season number string
                    int lengthdiff = serie_list.getSerieFromIndex(files[i]->getSerieIndex())->getNbCharSeason() - files[i]->getSeason().length();
                    for (int j=0;j<lengthdiff;j++)
                    {
                        files[i]->setSeason("0" + files[i]->getSeason());
                    }

                    // If some 0 are missing in the number number string
                    lengthdiff = serie_list.getSerieFromIndex(files[i]->getSerieIndex())->getNbCharNumber() - files[i]->getNumber().length();
                    for (int j=0;j<lengthdiff;j++)
                    {
                        files[i]->setNumber("0" + files[i]->getNumber());
                    }

                    string newname = files[i]->getSerie() + " " + files[i]->getCharSeason() + files[i]->getSeason() + files[i]->getCharZero() + files[i]->getCharNumber() + files[i]->getNumber() + "." + files[i]->getExtension();
                    if (newname == files[i]->getName())
                    {
                        //cout << "File    : " << files[i]->getName() << " (already done)" << endl;
                        file_list.push_back("File    : " + files[i]->getName() + " (already done)");
                    }
                    else
                    {
                        /*cout << "File    : " << files[i]->getName() << endl;
                        cout << "Newname : " << newname << endl << endl;*/
                        file_list.push_back("File    : " + files[i]->getName() + "\nNewname : " + newname);
                        rename(string(directory + "/" + files[i]->getName()).c_str(), string(directory + "/" + newname).c_str());
                    }
                    counter++;
                }
                else
                {
                    file_list.push_back("Error : File not computed properly : " + files[i]->getName());
                    //cout << "Error : File not computed properly : " << files[i]->getName() << endl << endl;
                }
            }

        }
        /*cout << "----------------------------------" << endl;
        if (counter != nbFiles)
            cout << "  Warning : " << nbFiles-counter << " files not computed" << endl;
        else
            cout << "       All files computed" << endl;
        cout << "----------------------------------" << endl << endl;*/

    }
    return file_list;

}

File::File(string name, string folder) : f_name(name), f_char_number(""), f_char_zero(""), f_number(""), f_char_season(""), f_season(""), f_extension(""), f_serie(""), f_folder(folder), f_nextFile(NULL){}

string File::getName()
{
    return f_name;
}

void File::setName(string name)
{
    f_name = name;
}

string File::getSerie()
{
    return f_serie;
}

void File::setSerie(string serie)
{
    f_serie = serie;
}

int File::getSerieIndex(void)
{
    return f_serie_index;
}

void File::setSerieIndex(int index)
{
    f_serie_index = index;
}

string File::getCharNumber(void)
{
    return f_char_number;
}

void File::setCharNumber(string char_number)
{
    f_char_number = char_number;
}

string File::getCharZero(void)
{
    return f_char_zero;
}

void File::setCharZero(string char_zero)
{
    f_char_zero = char_zero;
}

string File::getNumber()
{
    return f_number;
}

void File::setNumber(string number)
{
    f_number = number;
}

string File::getCharSeason(void)
{
    return f_char_season;
}

void File::setCharSeason(string char_season)
{
    f_char_season = char_season;
}

string File::getSeason()
{
    return f_season;
}

void File::setSeason(string season)
{
    f_season = season;
}

string File::getExtension()
{
    return f_extension;
}

void File::setExtension(string extension)
{
    f_extension = extension;
}

File* File::getNextFile()
{
    return f_nextFile;
}

void File::setNextFile(File* file)
{
    f_nextFile = file;
}

string File::getFolder()
{
    return f_folder;
}

void File::setFolder(string folder)
{
    f_folder = folder;
}

void File::computeNumber(Serie serie)
{
    string s (f_name);
    if(serie.getBoolNumber())
        f_char_number = "E";
    if(serie.getBoolZero())
        f_char_zero = "0";
    string value;
    smatch m;
    regex rgx (serie.getRegexNumber());

    while (regex_search (s,m,rgx))
    {
        for (auto x:m)
        {
            string value(x);

            if (value != "720")
            {
                f_number = value.substr(serie.getRegexNumberTrimLeft(), value.length() - serie.getRegexNumberTrimRight());
            }
        }
        s = m.suffix().str();
    }
}

void File::computeSeason(Serie serie)
{
    string s (f_name);
    if(serie.getBoolSeason())
        f_char_season = "S";
    if (serie.getRegexSeason() != "")
    {
        string value;
        smatch m;
        regex rgx (serie.getRegexSeason());
        while (regex_search (s,m,rgx))
        {
            for (auto x:m)
            {
                string value(x);
                f_season = value.substr(serie.getRegexSeasonTrimLeft(), value.length() - serie.getRegexSeasonTrimRight());
            }
            //cout << "f_season " << f_season << endl;
            s = m.suffix().str();
        }
    }
}

bool File::computeExtension(Serie serie)
{
    if (f_name.length() > 4)
    {
        if(serie.getRegexExtension().compare(f_name.substr(f_name.length()-3, 3)) == 0)
        {
           f_extension = f_name.substr(f_name.length()-3, 3);
           return true;
        }
    }
    return false;
}

int File::computeSerie(SerieList series_list)
{
    string str (f_name);
    return series_list.getMatchSerie(str);
}

bool File::computeFile(SerieList series_list)
{
    int index = computeSerie(series_list);

    if (index != -1){
        Serie *s = series_list.getSerieFromIndex(index);
        f_serie_index = index;
        f_serie = s->getName();

        //cout << endl << "Compute Season" << endl;
        computeSeason(*s);
        //cout << "Compute Number" << endl;
        computeNumber(*s);
        //cout << "Compute Extension" << endl;
        computeExtension(*s);
        return true;
    }
    return false;
}









