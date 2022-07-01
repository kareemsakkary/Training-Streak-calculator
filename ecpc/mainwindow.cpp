#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <bits/stdc++.h>
#include <QFileDialog>
#include <QHBoxLayout>

using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

struct member{
    string name;
    int streak,solved,unsolved;
};
vector<member> getData(){
    vector<member> data;
    vector<string> row;
    string line,word;
    fstream file;
    file.open("data.csv");
    while (getline(file, line,'\n')) {
        row.clear();
       member mb;
       // used for breaking words
       stringstream s(line);
       // read every column data of a row and
       // store it in a string variable, 'word'
       while (getline(s, word,','))row.push_back(word);
       mb.name = row[0];
       mb.streak = stoi(row[1]);
       mb.solved = stoi(row[2]);
       mb.unsolved = stoi(row[3]);
       data.push_back(mb);
    }
    file.close();
    return data;
}
void lowercase(string& data){
    for (int i = 0; i < data.size(); i++) {
        data[i] = tolower(data[i]);
    }
}
void MainWindow::on_pushButton_2_clicked()
{
   vector<member> data = getData();
   ui->tableWidget->setRowCount(data.size());
   int c = 0;
   for(member mb : data){
       QString x = QString::fromStdString(mb.name);
       QTableWidgetItem *item = new QTableWidgetItem(x);
       ui->tableWidget->setItem(c,0,item);

       x = QString::fromStdString(to_string(mb.streak));
       item = new QTableWidgetItem(x);
       ui->tableWidget->setItem(c,3,item);

       x = QString::fromStdString(to_string(mb.solved));
       item = new QTableWidgetItem(x);
       ui->tableWidget->setItem(c,4,item);

       x = QString::fromStdString(to_string(mb.unsolved));
       item = new QTableWidgetItem(x);
       ui->tableWidget->setItem(c,5,item);

       QWidget* pWidget = new QWidget();
       QPushButton* btn_edit = new QPushButton();
       connect(btn_edit , &QPushButton::clicked, this, [&](){
           QWidget *w = qobject_cast<QWidget *>(sender()->parent());
           int row = ui->tableWidget->indexAt(w->pos()).row();
           QString a = ui->tableWidget->item(row,4)->text();
           QTableWidgetItem *item1 = new QTableWidgetItem(QString::fromStdString(to_string(stoi(a.toStdString())+1)));
           ui->tableWidget->setItem(row,4,item1);
           int b = ui->tableWidget->item(row,3)->text().toInt();
           string txt;
           if(b <0){
               txt = "1";
           }else{
               txt = to_string(b+1);
           }
           QTableWidgetItem *item2 = new QTableWidgetItem(QString::fromStdString(txt));
           ui->tableWidget->setItem(row,3,item2);
       });
       btn_edit->setText("Done");
       QHBoxLayout* pLayout = new QHBoxLayout(pWidget);
       pLayout->addWidget(btn_edit);
       pLayout->setAlignment(Qt::AlignCenter);
       pLayout->setContentsMargins(0, 0, 0, 0);
       pWidget->setLayout(pLayout);
       ui->tableWidget->setCellWidget(c,1,pWidget);

       QWidget* pWidget1 = new QWidget();
       QPushButton* btn_edit1 = new QPushButton();
       connect(btn_edit1 , &QPushButton::clicked, this, [&](){
           QWidget *w = qobject_cast<QWidget *>(sender()->parent());
           int row = ui->tableWidget->indexAt(w->pos()).row();
           QString a = ui->tableWidget->item(row,5)->text();
           QTableWidgetItem *item1 = new QTableWidgetItem(QString::fromStdString(to_string(stoi(a.toStdString())+1)));
           ui->tableWidget->setItem(row,5,item1);
           int b = ui->tableWidget->item(row,3)->text().toInt();
           string txt;
           if(b >0){
               txt = "0";
           }else{
               txt = to_string(b-1);
           }
           QTableWidgetItem *item2 = new QTableWidgetItem(QString::fromStdString(txt));
           ui->tableWidget->setItem(row,3,item2);
       });
       btn_edit1->setText("Not Done");
       QHBoxLayout* pLayout1 = new QHBoxLayout(pWidget1);
       pLayout1->addWidget(btn_edit1);
       pLayout1->setAlignment(Qt::AlignCenter);
       pLayout1->setContentsMargins(0, 0, 0, 0);
       pWidget1->setLayout(pLayout1);
       ui->tableWidget->setCellWidget(c,2,pWidget1);
       c++;
   }

}


void MainWindow::on_pushButton_clicked()
{
    fstream file;
    file.open("C://Users//karee//OneDrive//Documents//GitHub//ECPC-Practice//data.csv",ios::out);
    int rowCount = ui->tableWidget->rowCount();
    for(int i = 0 ; i < rowCount;i++){
        file << ui->tableWidget->item(i,0)->text().toStdString() << ","
             << ui->tableWidget->item(i,3)->text().toStdString() << ","
             << ui->tableWidget->item(i,4)->text().toStdString() << ","
             << ui->tableWidget->item(i,5)->text().toStdString() << "\n";
    }
    file.close();
}


void MainWindow::on_pushButton_3_clicked()
{
    int rowCount = ui->tableWidget->rowCount();
    fstream file;
    file.open("C://Users//karee//OneDrive//Documents//GitHub//ECPC-Practice//streak.txt",ios::out);
    for(int i = 0 ; i < rowCount;i++){
        int streak = stoi(ui->tableWidget->item(i,3)->text().toStdString() );
        file << ui->tableWidget->item(i,0)->text().toStdString() << "  " <<
                streak<<" ";
        if(streak > 0){
            file << "🔥";
        }else if(streak<0){
            file << "😡";
        }
        file << endl;
    }
    file.close();
}

bool exist(vector<int> ve , int x){
    for(int i : ve){
        if(x==i)return true;
    }
    return false;
}

void MainWindow::on_pushButton_4_clicked()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile );
    dialog.setNameFilter(tr("*.txt"));
    dialog.setViewMode(QFileDialog::Detail);
    QStringList fileNames;
    if (dialog.exec())
        fileNames = dialog.selectedFiles();

    string file = fileNames.last().toStdString();
    string str;
    ifstream Myfile;
    stringstream Output;
    // Names will be printed into the champions file  , You dant have to create it , it will be automatically created

    // Put the copied text in the Generate File >> You have to create it manually
    Myfile.open(file);
    vector<int> done;
    while (!Myfile.eof())
    {

        getline(Myfile, str);

        lowercase(str);
        if (str.find("daily problem solved") != string::npos)
        {
            string name;
            int spaces = 0;
            for (int i = 10; i < str.length(); i++)
            {
                if (str[i] == ':')
                {
                    break;
                }

                if (isalpha(str[i]))
                {
                    name += str[i];

                    if (str[i + 1] == ' ')
                    {
                        name += ' ';
                    }

                }
            }
            cout << name << endl;
            for(int i = 0 ; i < ui->tableWidget->rowCount();i++){
                string x =ui->tableWidget->item(i,0)->text().toStdString();
                lowercase(x);
                if(x==name){
                    if(!exist(done,i)){
                        int row = i;
                        QString a = ui->tableWidget->item(row,4)->text();
                        QTableWidgetItem *item1 = new QTableWidgetItem(QString::fromStdString(to_string(stoi(a.toStdString())+1)));
                        ui->tableWidget->setItem(row,4,item1);
                        int b = ui->tableWidget->item(row,3)->text().toInt();
                        string txt;
                        if(b <0){
                            txt = "1";
                        }else{
                            txt = to_string(b+1);
                        }
                        QTableWidgetItem *item2 = new QTableWidgetItem(QString::fromStdString(txt));
                        ui->tableWidget->setItem(row,3,item2);
                        done.push_back(i);
                    }
                }
            }
        }
    }
    for(int i = 0 ;i < ui->tableWidget->rowCount();i++){
        if(!exist(done,i)){
            int row = i;
            QString a = ui->tableWidget->item(row,5)->text();
            QTableWidgetItem *item1 = new QTableWidgetItem(QString::fromStdString(to_string(stoi(a.toStdString())+1)));
            ui->tableWidget->setItem(row,5,item1);
            int b = ui->tableWidget->item(row,3)->text().toInt();
            string txt;
            if(b >0){
                txt = "0";
            }else{
                txt = to_string(b-1);
            }
            QTableWidgetItem *item2 = new QTableWidgetItem(QString::fromStdString(txt));
            ui->tableWidget->setItem(row,3,item2);
        }
    }

}

