#ifndef ADDSERIE_H
#define ADDSERIE_H

#include <vector>
#include <string>

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QFormLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QDialog>

class fieldContent {
    private:
            // field content
            std::string fc_value;
            // type of content ("str", "strlist", "int", "rgx"...)
            std::string fc_code;
            // mandadory field or not
            bool fc_mandatry;
    public:
            fieldContent();
            fieldContent(std::string value, std::string type, bool mandatory);

            std::string getValue(void);
            void setValue(std::string);
            std::string getCode(void);
            void setCode(std::string);
            bool getMandatory(void);
            void setMandatory(bool);
};

class addSerieForm : public QWidget
{
    Q_OBJECT
private:

    std::vector<fieldContent> fieldList;

    QPushButton *pb_validate;

    QLineEdit *le_oldName;
    QLineEdit *le_nbOldName;
    QLineEdit *le_index;
    QLineEdit *le_name;
    QLineEdit *le_nbCharSeason;
    QLineEdit *le_trim_season_left;
    QLineEdit *le_trim_season_right;
    QLineEdit *le_bool_season;
    QLineEdit *le_regexSeason;
    QLineEdit *le_nbCharNumber;
    QLineEdit *le_trim_number_left;
    QLineEdit *le_trim_number_right;
    QLineEdit *le_bool_number;
    QLineEdit *le_regexEpisode;
    QLineEdit *le_extension;
    QLineEdit *le_bool_zero;

    QGridLayout *mainLayout;
    QFormLayout *formLayout;
public:
    addSerieForm();

    bool integerValidator(std::string);
    bool notEmptyValidator(std::string);
    void uptdateWidgetListValues(void);
    void processFields(void);

public slots:
    void validateSerie(void);

};

#endif // ADDSERIE_H
