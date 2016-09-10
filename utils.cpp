#include "utils.h"
#include "file.h"

#include <dirent.h>
#include <vector>

#ifndef WIN32
    #include <sys/types.h>
#endif

using namespace std;

bool checkExtension(string s)
{
    int nbExt = 4;
    string ext[4] = {"avi", "mkv", "m4a", "mp4"};

    if (s.length() > 4)
    {
        for(int i=0;i<nbExt;i++)
        {
            if(s.substr(s.length()-3, 3).compare(ext[i]) == 0)
            {
               return true;
            }
        }
    }
    return false;
}

int countFiles(string directory)
{
    try
    {
        int nbFiles(0);
        unsigned char isFile = 0x8;
        DIR* rep = NULL;

        rep = opendir((char*)directory.c_str()); // Ouverture d'un dossier *

        struct dirent* fichierLu = NULL;

        if (rep == NULL) // Si le dossier n'a pas pu être ouvert
            exit(1);

        while ((fichierLu = readdir(rep)) != NULL)
        {
            if (fichierLu->d_type == isFile and checkExtension(fichierLu->d_name) and string(fichierLu->d_name).substr(0,1) != ".")
            {
                nbFiles++;
            }
        }

        return nbFiles;
    }
    catch (string const& e)
    {
        cout << endl << e << endl << endl;
        return -1;
    }
}

vector<string> renameFiles(string directory, SerieList serie_list)
{
    //try
    //{
        vector<string> file_list;
        unsigned char isFile = 0x8;
        unsigned char isFolder = 0x4;

        File *file;
        //renameFiles(files);
        DIR* rep = NULL;

        int nbFiles = countFiles(directory);
        File *files[nbFiles];
        if (nbFiles != 0)
            cout << "Nombre de fichiers : " << nbFiles << endl;
        rep = opendir((char*)directory.c_str()); // Ouverture d'un dossier

        struct dirent* fichierLu = NULL;

        int iterator(0);

        if (rep == NULL) // Si le dossier n'a pas pu être ouvert
            exit(1); // (mauvais chemin par exemple)

        //cout << "Le dossier a ete ouvert avec succes" << endl;

        string separator(directory);

        while ((fichierLu = readdir(rep)) != NULL)
        {
            if (string(fichierLu->d_name).substr(0,1) != ".")
            {
                if (fichierLu->d_type == isFile and checkExtension(fichierLu->d_name))
                {
                   // cout << "Le fichier lu s'appelle " << directory << "/" << fichierLu->d_name << " - Début du traitement " << endl;

                    string filename(fichierLu->d_name);

                    separator += string("/");
                    file = new File(filename, separator);

                    if (file->computeFile(serie_list))
                    {
                        //cout << "File added to the list : " << filename << endl;
                        files[iterator] = file;
                        iterator += 1;
                    }

                    //cout << "Fin du traitement " << endl;
                }
                else if (fichierLu->d_type == isFolder and string(fichierLu->d_name).substr(1,3) != "git" and string(fichierLu->d_name) != "Rename")
                {
                    renameFiles(directory + "/" + string(fichierLu->d_name), serie_list);
                }
            }
        }
        //cout << "End of printing" << endl << endl;
        if (closedir(rep) == -1) // S'il y a eu un souci avec la fermeture
            exit(-1);

        //cout << "Le dossier a ete ferme avec succes" << endl;

        file_list = renameFiles(files, serie_list, nbFiles, directory);
        return file_list;
    /*}
    catch (string const& e)
    {
        cout << e << endl;
        return null;
    }*/





}


// Serie's Methods
Serie::Serie(){}

Serie::Serie(int index, string* oldName, string name, int nbCharSeason, int trim_season_left, int trim_season_right, bool bool_season, string regex_season, int nbCharNumber, int trim_number_left, int trim_number_right, bool bool_number, string regex_number, string regex_extension, int nboldname, bool bool_zero) :
            s_index(index),
            s_name(name),
            s_nbCharSeason(nbCharSeason),
            s_regex_season_trim_left(trim_season_left),
            s_regex_season_trim_right(trim_season_right),
            s_bool_season(bool_season),
            s_regex_season(regex_season),
            s_nbCharNumber(nbCharNumber),
            s_regex_number_trim_left(trim_number_left),
            s_regex_number_trim_right(trim_number_right),
            s_bool_number(bool_number),
            s_regex_number(regex_number),
            s_regex_extension(regex_extension),
            s_nboldname(nboldname),
            s_bool_zero(bool_zero),
            s_nextSerie(NULL)
{
    s_oldname = new string[s_nboldname];
    for (int i=0;i<s_nboldname;i++)
    {
        s_oldname[i] = oldName[i];
    }

}

int Serie::getIndex(void)
{
    return s_index;
}

void Serie::setIndex(int index)
{
    s_index = index;
}

string* Serie::getOldName(void)
{
    return s_oldname;
}

void Serie::setOldName(string* oldNames)
{
    s_oldname = oldNames;
}

string Serie::getName(void)
{
    return s_name;
}

void Serie::setName(string name)
{
    s_name = name;
}

int Serie::getRegexSeasonTrimLeft(void)
{
    return s_regex_season_trim_left;
}

void Serie::setRegexSeasonTrimLeft(int trim)
{
    s_regex_season_trim_left = trim;
}

int Serie::getRegexSeasonTrimRight(void)
{
    return s_regex_season_trim_right;
}

void Serie::setRegexSeasonTrimRight(int trim)
{
    s_regex_season_trim_right = trim;
}

bool Serie::getBoolSeason(void)
{
    return s_bool_season;
}

void Serie::setBoolSeason(bool bool_season)
{
    s_bool_season = bool_season;
}

string Serie::getRegexSeason(void)
{
    return s_regex_season;
}

void Serie::setRegexSeason(string regex)
{
    s_regex_season = regex;
}

int Serie::getRegexNumberTrimLeft(void)
{
    return s_regex_number_trim_left;
}

void Serie::setRegexNumberTrimLeft(int trim)
{
    s_regex_number_trim_left = trim;
}

int Serie::getRegexNumberTrimRight(void)
{
    return s_regex_number_trim_right;
}

void Serie::setRegexNumberTrimRight(int trim)
{
    s_regex_number_trim_right = trim;
}

bool Serie::getBoolNumber(void)
{
    return s_bool_number;
}

void Serie::setBoolNumber(bool bool_number)
{
    s_bool_number = bool_number;
}

string Serie::getRegexNumber(void)
{
    return s_regex_number;
}

void Serie::setRegexNumber(string regex)
{
    s_regex_number = regex;
}

string Serie::getRegexExtension(void)
{

    return s_regex_extension;
}

void Serie::setRegexExtension(string regex)
{
    s_regex_extension = regex;
}

int Serie::getNbOldName(void)
{
    return s_nboldname;
}

Serie* Serie::getNext(void)
{
    return s_nextSerie;
}

void Serie::setNext(Serie* s)
{
    s_nextSerie = s;
}

void Serie::setNbOldName(int nb)
{
    s_nboldname = nb;
}

bool Serie::getBoolZero(void)
{
    return s_bool_zero;
}
void Serie::setBoolZero(bool bool_zero)
{
    s_bool_zero = bool_zero;
}

int Serie::getNbCharSeason(void)
{
    return s_nbCharSeason;
}

void Serie::setNbCharSeason(int nbChar)
{
    s_nbCharSeason = nbChar;
}


int Serie::getNbCharNumber(void)
{
    return s_nbCharNumber;
}

void Serie::setNbCharNumber(int nbChar)
{
    s_nbCharSeason = nbChar;
}

//Check if an "old name" is part of this serie
bool Serie::isSerie(string)
{
    return true;
}

void Serie::printSerie()
{
    cout << "Serie name         : " << s_name << endl;
    cout << "Regex Season       : " << s_regex_season << endl;
    cout << "Regex Number       : " << s_regex_number << endl;
    cout << "Regex Extension    : " << s_regex_extension << endl;

    cout << "Possible old names : ";
    for (int i=0;i<s_nboldname;i++)
    {
        cout << s_oldname[i] << " ";
        if (i != s_nboldname-1)
            cout << "/ ";
    }
    cout << endl << endl;
}
// SerieList's Methods
SerieList::SerieList(){}

SerieList::SerieList(Serie* seriesList, int length) : sl_seriesList(seriesList), sl_length(length){}

// Go through all the series and look for the good one

int SerieList::getMatchSerie(string filename)
{
    bool cont = false;
    string value;
    int i;
    Serie* series = getSerieList();

    int maxIteration = 0;

    string* oldNames;

    while (series != NULL and not cont)
    {
        maxIteration = series->getNbOldName();

        oldNames = series->getOldName();
        i = 0;
        while (i < maxIteration and not cont)
        {
            //cout << "Test du nom : " << oldNames[i] << " Pour : " << filename << endl;
            size_t found = filename.find(string(oldNames[i]));

            if (found!=string::npos)
            {
                //cout << "La série a été trouvé " << endl;
                cont = true;
            }
            else
            {
                //cout << "La série n'a pas été trouvé..." << endl;

            }
            i++;

        }
        if (not cont)
            series = series->getNext();
    }

    if (cont)
        return series->getIndex();
    return -1;
}

// Return the number of series in the list
int SerieList::getLength()
{
    return sl_length;
}

void SerieList::setLength(int newLength)
{
    sl_length = newLength;
}

Serie* SerieList::getSerieList(void)
{
    return sl_seriesList;
}

void SerieList::setSerieList(Serie* seriesList)
{
    sl_seriesList = seriesList;
}

Serie* SerieList::getNextSerie(Serie* s)
{
    return s->getNext();
}

void SerieList::setNextSerie(Serie* s)
{
    Serie* p = sl_seriesList;
    while (p->getNext() != NULL)
    {
        p = p->getNext();
    }
    p->setNext(s);
}

void SerieList::addSerie(Serie* serie)
{
    Serie* p = sl_seriesList;
    sl_seriesList = serie;
    sl_seriesList->setNext(p);
    sl_length += 1;

}

void SerieList::printSerieList(void)
{
    Serie *p = getSerieList();
    cout << endl << "-----  List of stored series -----" << endl << endl;
    while(p != NULL)
    {
        p->printSerie();
        p = p->getNext();
    }
    cout << "----------------------------------" << endl << endl;
}

Serie* SerieList::getSerieFromIndex(int index)
{
    Serie *p = getSerieList();
    while(p != NULL and p->getIndex() != index)
    {
        p = p->getNext();
    }
    return p;
}



