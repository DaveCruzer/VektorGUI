#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    searchThread = new WordSearch();
    connect(searchThread, &WordSearch::searchResult, this, &MainWindow::searchResult);
    connect(ui->lineEdit, &QLineEdit::textChanged, searchThread, &WordSearch::search);
    searchThread->start();
}


void MainWindow::searchResult(const std::string& search, std::shared_ptr<const SearchResult> result)
{
    if(result->prefix == ui->lineEdit->text().toStdString())
    {
        ui->listWidget->clear();
        if(result->result.size() <= 100)
        {
            auto sortedResult = result->result;
            std::sort(sortedResult.begin(), sortedResult.end());
            QStringList words;
            for(const auto& word: sortedResult)
            {
                words.push_back(QString(word.c_str()));
            }
            ui->listWidget->addItems(words);
        }
        else
        {
            ui->listWidget->addItem(QStringLiteral("%1 results").arg(result->result.size()));
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete searchThread;
}
