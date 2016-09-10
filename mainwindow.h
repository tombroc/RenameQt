#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "file.h"
#include "utils.h"
#include "fill.h"
#include "addserie.h"
#include <iostream>
#include <string.h>


#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QFileDialog>
#include <QGridLayout>
#include <QObject>
#include <QLabel>

class mainWindow : public QWidget
{
    Q_OBJECT

    public:
        mainWindow();
        void updateFileList(std::string);

    public slots:
        void getFolder(void);
        void openForm(void);
        void runClick();
        void run(QString);

    private:
        QString *s_title;
        QString *s_files;
        QString *s_choice;
        QString *s_folder;
        QString *s_valid;
        QString *s_openForm;

        QLabel *l_title;
        QLabel *l_files;
        QLabel *l_folder;

        QPushButton *pb_choice;
        QPushButton *pb_valid;
        QPushButton *pb_openForm;

        QGridLayout *layout;
};

#endif // MAINWINDOW_H
