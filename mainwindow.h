#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "wordsearch.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void searchResult(const std::string& search, std::shared_ptr<const SearchResult> results);
private:
    Ui::MainWindow *ui;
    WordSearch* searchThread;
};
#endif // MAINWINDOW_H
