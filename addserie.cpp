#include "addserie.h"
#include <iostream>
#include <regex>
#include <string>

using namespace std;

std::string fieldContent::getValue(void)
{
    return fc_value;
}

void fieldContent::setValue(std::string value)
{
    fc_value = value;
}

std::string fieldContent::getCode(void)
{
    return fc_code;
}

void fieldContent::setCode(std::string code)
{
    fc_code = code;
}

bool fieldContent::getMandatory(void)
{
    return fc_mandatry;
}

void fieldContent::setMandatory(bool mandatory)
{
    fc_mandatry = mandatory;
}

fieldContent::fieldContent(std::string value, std::string code, bool mandatory): fc_value(value), fc_code(code), fc_mandatry(mandatory){}


bool integerValidator(std::string str)
{
    regex rgx ("^-?\\d+$");
    if(regex_match (str,rgx))
        return true;
    return false;
}

bool notEmptyValidator(std::string str)
{
    if (str != "")
        return true;
    return false;
}
void addSerieForm::processfields()
{
    for (unsigned i=0;i<fieldList.size();i++)
    {
        // Compute cases : "str", "strlist", "int", "rgx"
        switch (fieldList[i].getCode())
        {
            case "str":
                break;
            case "strlist":
                break;
            case "int":
                break;
            case "rgx":
                break;
            default:
                break;
        }
    }
}

void addSerieForm::uptdateWidgetListValues()
{
    fieldList.clear();
    fieldList.push_back(fieldContent(le_oldName->text().toStdString(), "strlist", true));
    fieldList.push_back(fieldContent(le_name->text().toStdString(), "", true));
    fieldList.push_back(fieldContent(le_nbCharSeason->text().toStdString(), "", true));
    fieldList.push_back(fieldContent(le_trim_season_left->text().toStdString(), "", true));
    fieldList.push_back(fieldContent(le_trim_season_right->text().toStdString(), "", true));
    fieldList.push_back(fieldContent(le_bool_season->text().toStdString(), "", true));
    fieldList.push_back(fieldContent(le_regexSeason->text().toStdString(), "", true));
    fieldList.push_back(fieldContent(le_nbCharNumber->text().toStdString(), "", true));
    fieldList.push_back(fieldContent(le_trim_number_left->text().toStdString(), "", true));
    fieldList.push_back(fieldContent(le_trim_number_right->text().toStdString(), "", true));
    fieldList.push_back(fieldContent(le_bool_number->text().toStdString(), "", true));
    fieldList.push_back(fieldContent(le_regexEpisode->text().toStdString(), "", true));
    fieldList.push_back(fieldContent("."+le_extension->text().toStdString(), "", true));
    fieldList.push_back(fieldContent(le_bool_zero->text().toStdString(), "", true));

    processFields();
}

void addSerieForm::validateSerie(void)
{
    uptdateWidgetListValues();
}

addSerieForm::addSerieForm() : QWidget()
{
    //QApplication app(argc, argv);

    QDialog window;

    pb_validate          = new QPushButton("Validate");

    le_oldName           = new QLineEdit;
    /* Count old names */
    le_nbOldName         = new QLineEdit;
    /* Automatically filled */
    le_index             = new QLineEdit;
    le_name              = new QLineEdit;
    le_nbCharSeason      = new QLineEdit;
    le_trim_season_left  = new QLineEdit;
    le_trim_season_right = new QLineEdit;
    le_bool_season       = new QLineEdit;
    le_regexSeason       = new QLineEdit;
    le_nbCharNumber      = new QLineEdit;
    le_trim_number_left  = new QLineEdit;
    le_trim_number_right = new QLineEdit;
    le_bool_number       = new QLineEdit;
    le_regexEpisode      = new QLineEdit;
    le_extension         = new QLineEdit;
    le_bool_zero         = new QLineEdit;

    QString s_oldName("Old possible names");
    QString s_name("Serie name");
    QString s_nbCharSeason("Number of char (season)");
    QString s_trim_season_left("Trim left (season)");
    QString s_trim_season_right("Trim right (season)");
    QString s_bool_season("Add character \"S\" (season)");
    QString s_regexSeason("Regex season");
    QString s_nbCharNumber("Number of char (episode)");
    QString s_trim_number_left("Trim left (episode)");
    QString s_trim_number_right("Trim right (episode)");
    QString s_bool_number("Add character \"E\" (episode)");
    QString s_regexEpisode("Regex episode");
    QString s_extension("Extension");
    QString s_bool_zero("Add \"0\" (episode number)");

    mainLayout          = new QGridLayout;
    formLayout          = new QFormLayout;

    formLayout->addRow(s_oldName, le_oldName);
    formLayout->addRow(s_name, le_name);
    formLayout->addRow(s_nbCharSeason, le_nbCharSeason);
    formLayout->addRow(s_trim_season_left, le_trim_season_left);
    formLayout->addRow(s_trim_season_right, le_trim_season_right);
    formLayout->addRow(s_bool_season, le_bool_season);
    formLayout->addRow(s_regexSeason, le_regexSeason);
    formLayout->addRow(s_nbCharNumber, le_nbCharNumber);
    formLayout->addRow(s_trim_number_left, le_trim_number_left);
    formLayout->addRow(s_trim_number_right, le_trim_number_right);
    formLayout->addRow(s_bool_number, le_bool_number);
    formLayout->addRow(s_regexEpisode, le_regexEpisode);
    formLayout->addRow(s_extension, le_extension);
    formLayout->addRow(s_bool_zero, le_bool_zero);

    mainLayout->addLayout(formLayout, 0,0);
    mainLayout->addWidget(pb_validate, 1,0);


    window.setLayout(mainLayout);

    QObject::connect(pb_validate, SIGNAL(clicked()), this, SLOT(validateSerie()));

    window.exec();

    //return app.exec();
}
