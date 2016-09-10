#include "mainwindow.h"


using namespace std;

void mainWindow::openForm()
{
    addSerieForm *form = new addSerieForm();
}

void mainWindow::runClick()
{
    emit run(l_folder->text());
}

void mainWindow::run(QString folder)
{
    if(folder != s_folder)
    {
        //l_files->setText(l_files->text() + "\n" + folder);
        SerieList series_list(NULL, 0);
        series_list = fillSerieList(series_list);
        series_list.printSerieList();

        string directory(folder.toStdString());
        //strcpy(directory, ".");
        vector<string> file_list;
        file_list = renameFiles(directory, series_list);
        cout << "Size : " << file_list.size() << endl;
        for (int i(0);i<file_list.size();i++)
        {
            updateFileList(file_list[i]);
        }
    }
}

void mainWindow::getFolder()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    l_folder->setText(dir);
}

void mainWindow::updateFileList(string filename)
{
    l_files->setText(l_files->text() + QString::fromStdString("\n" + filename));
}

mainWindow::mainWindow() : QWidget()
{
    s_title       = new QString("Rename Application");
    s_files       = new QString("Computed files");
    s_choice      = new QString("Choose Folder");
    s_folder      = new QString("Chosen Folder");
    s_valid       = new QString("Run");
    s_openForm    = new QString("Add Serie");

    l_title       = new QLabel(s_title->toStdString().c_str(), this);
    l_files       = new QLabel(s_files->toStdString().c_str(), this);

    l_files->setStyleSheet("border: 2px solid grey");

    pb_choice     = new QPushButton(s_choice->toStdString().c_str(), this);
    l_folder      = new QLabel(s_folder->toStdString().c_str(), this);
    pb_valid      = new QPushButton(s_valid->toStdString().c_str(), this);
    pb_openForm   = new QPushButton(s_openForm->toStdString().c_str(), this);

    layout        = new QGridLayout;

    layout->addWidget(l_title, 0, 0, 1, 3);
    layout->addWidget(l_files, 1, 0, 1, 3);
    layout->addWidget(pb_openForm, 0, 2);
    layout->addWidget(pb_choice, 2, 0);
    layout->addWidget(l_folder, 2, 1);
    layout->addWidget(pb_valid, 2, 2);

    this->setLayout(layout);

    // Buttons connnexions
    QObject::connect(pb_choice, SIGNAL(clicked()), this, SLOT(getFolder()));
    QObject::connect(pb_openForm, SIGNAL(clicked()), this, SLOT(openForm()));
    QObject::connect(pb_valid, SIGNAL(clicked()), this, SLOT(runClick()));
}


