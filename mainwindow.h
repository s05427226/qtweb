#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QLineEdit;
class QWebView;
class QStatusBar;
class QProgressBar;
class QLabel;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void redirect();
    void loadStart();
    void loadProgress(int iProgress);
    void loadFinished(bool bFinished);
private:
    Ui::MainWindow *ui;
    QLineEdit *m_addr;
    QWebView *m_webView;

    QStatusBar* m_statusBar;
    QProgressBar* m_webloadProgress;
    QLabel *m_labelProgress;
};

#endif // MAINWINDOW_H
