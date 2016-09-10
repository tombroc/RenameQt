#include "fill.h"
#include <string>

using namespace std;

/*
 * SerieList series_list		- List of stored series
 * string oldNameCommunity[]	- array of all possible old names for a serie
 * int nbOldName				- number of possible old names
 * int index					- serie's id
 * string name					- Valid serie's name
 * int nbCharSeason             - Nb necessary character for the SEASON number
 * int trim_season_left			- Number of character to delete on the LEFT with the SEASON regex
 * int trim_season_right		- Number of character to delete on the RIGHT with the SEASON regex
 * bool bool_season				- If a character has to be added before the SEASON number (ex : "S")
 * string regexSeason			- Regex to find the SEASON number
 * int nbCharNumber             - Nb necessary character for the NUMBER number
 * int trim_number_left			- Number of character to delete on the LEFT with the NUMBER regex
 * int trim_number_right		- Number of character to delete on the RIGHT with the SEASON regex
 * bool bool_number				- If a character has to be added before the NUMBER number (ex : "E")
 * string regexEpisode			- Regex to find the NUMBER number
 * string extension				- Extension of the serie
 * bool bool_zero				- If a 0 has to be added before the NUMBER number
*/
SerieList fillSerieList(SerieList series_list)
{

    /*********************** Community ***********************/

    string oldNameCommunity[2] = {"Community", "community"};
    int nbOldName(2);
    int index(0);
    string name("Community");
    int nbCharSeason(2);
    int trim_season_left(2);
    int trim_season_right(3);
    bool bool_season(true);
    string regexSeason("(.[Ss][0-9][0-9][Ee])");
    int nbCharNumber(2);
    int trim_number_left(1);
    int trim_number_right(2);
    bool bool_number(true);
    string regexEpisode("([Ee][0-9][0-9].)");
    string extension("avi");
    bool bool_zero(false);

    series_list.addSerie(new Serie(index, oldNameCommunity, name, nbCharSeason, trim_season_left, trim_season_right, bool_season, regexSeason, nbCharNumber, trim_number_left, trim_number_right, bool_number, regexEpisode, extension, nbOldName, bool_zero));

    /*********************************************************/

    /******************************* Dragon Ball Super *******************************/

    string oldNameDBS[3] = {"Dragon Ball Super", "DBS", "DBsuper"};
    nbOldName = 3;
    index = 1;
    name = "Dragon Ball Super";
    nbCharSeason = 0;
    trim_season_left = 0;
    trim_season_right = 0;
    bool_season = false;
    regexSeason = "";
    nbCharNumber = 3;
    trim_number_left = 0;
    trim_number_right = 0;
    bool_number = false;
    regexEpisode = "([0-9][0-9][0-9]?)";
    extension = "mp4";
    bool_zero = false;

    series_list.addSerie(new Serie(index, oldNameDBS, name, nbCharSeason, trim_season_left, trim_season_right, bool_season, regexSeason, nbCharNumber, trim_number_left, trim_number_right, bool_number,regexEpisode, extension, nbOldName, bool_zero));

    /*********************************************************************************/

    /********************** Mr Robot **********************/

    string oldNameMrR[1] = {"Mr.Robot"};
    nbOldName = 1;
    index = 2;
    name = "Mr Robot";
    nbCharSeason = 2;
    trim_season_left = 2;
    trim_season_right = 3;
    bool_season = true;
    regexSeason = "(.[Ss][0-9][0-9][Ee])";
    nbCharNumber = 2;
    trim_number_left = 1;
    trim_number_right = 2;
    bool_number = true;
    regexEpisode = "([Ee][0-9][0-9].)";
    extension = "avi";
    bool_zero = false;

    series_list.addSerie(new Serie(index, oldNameMrR, name, nbCharSeason, trim_season_left, trim_season_right, bool_season, regexSeason, nbCharNumber, trim_number_left, trim_number_right, bool_number,regexEpisode, extension, nbOldName, bool_zero));

    /******************************************************/

    /********************** Stranger Things **********************/

    string oldNameStangerT[1] = {"Stranger.Things"};
    nbOldName = 1;
    index = 3;
    name = "Stranger Things";
    nbCharSeason = 2;
    trim_season_left = 2;
    trim_season_right = 3;
    bool_season = true;
    regexSeason = "(.[Ss][0-9][0-9][Ee])";
    nbCharNumber = 2;
    trim_number_left = 1;
    trim_number_right = 2;
    bool_number = true;
    regexEpisode = "([Ee][0-9][0-9].)";
    extension = "avi";
    bool_zero = false;

    series_list.addSerie(new Serie(index, oldNameStangerT, name, nbCharSeason, trim_season_left, trim_season_right, bool_season, regexSeason, nbCharNumber, trim_number_left, trim_number_right, bool_number,regexEpisode, extension, nbOldName, bool_zero));

    /**********************************************************/

    return series_list;
}
