#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QWebView>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStatusBar>
#include <QProgressBar>
#include <QLabel>
#include <QAction>
#include <QWebSettings>
#include <QWebHistory>
#include <QWebHistoryItem>
#include <QList>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWidget* widget = new QWidget(this);

    QHBoxLayout *hlayout = new QHBoxLayout;
    m_addr = new QLineEdit(QString("http://www.baidu.com"),widget);

    QPushButton *go = new QPushButton(QString("go"));
    QPushButton *history = new QPushButton(QString("history"));
    QString str = m_addr->text();

    hlayout->addWidget(m_addr);
    hlayout->addWidget(go);
    hlayout->addWidget(history);
    hlayout->stretch(0);

    connect(go,SIGNAL(clicked()),this,SLOT(redirect()));
    connect(history,SIGNAL(clicked()),this,SLOT(history()));
    connect(m_addr,SIGNAL(returnPressed()),this,SLOT(redirect()));

    QVBoxLayout *mainlayout = new QVBoxLayout;

    m_webView = new QWebView;
    QString string = "<html><body><h1>HTML Previewer</h1>"
                     " <p>This example shows you how to use QWebView to"
                     " preview HTML data written in a QPlainTextEdit.</p>"
                     " </body></html>";
    m_webView->setHtml(string);

   // m_webView->load(QUrl("http://www.baidu.com"));
    mainlayout->addLayout(hlayout);
    mainlayout->addWidget(m_webView);

    widget->setLayout(mainlayout);

    this->setCentralWidget(widget);

    QHBoxLayout *statusBar1Layout = new QHBoxLayout;

    m_statusBar = this->statusBar();
    m_webloadProgress = new QProgressBar;
    m_labelProgress = new QLabel("");

    m_webloadProgress->setRange(0,100);
    m_webloadProgress->setValue(0);
    m_statusBar->addWidget(m_labelProgress);
    m_statusBar->addWidget(m_webloadProgress);



    //m_statusBar->setFixedHeight(20);
   // m_statusBar->setLayout(statusBar1Layout);
    m_statusBar->setStyleSheet(QString("QStatusBar::item{border: 0px}"));

    connect(m_webView,SIGNAL(loadStarted()),this,SLOT(loadStart()));
    connect(m_webView,SIGNAL(loadProgress(int)),this,SLOT(loadProgress(int)));
    connect(m_webView,SIGNAL(loadFinished(bool)),this,SLOT(loadFinished(bool)));

    this->setWindowState(Qt::WindowMaximized);

    QWebSettings *websettings = m_webView->settings();
    websettings->setFontFamily(QWebSettings::StandardFont,"宋体");
}

MainWindow::~MainWindow()
{
    delete m_webView;
    delete ui;
}

void MainWindow::redirect()
{
    if(NULL != m_addr){
        QString strAddr = m_addr->text();
        if(strAddr.startsWith("http://") || strAddr.startsWith("https://")) {
            QUrl url(strAddr);
            m_webView->load(url);
        }else{
            QUrl url("http://" + strAddr);
            m_webView->load(url);
        }
    }else{
        QUrl url("http://www.baidu.cn");
        m_webView->load(url);
    }
}

void MainWindow::loadStart()
{
    this->m_labelProgress->setText(QString(tr("正在连接网站...")));
    this->m_webloadProgress->hide();
}

void MainWindow::loadProgress(int iProgress)
{
    this->m_labelProgress->setText(QString(tr("加载进度：")));
    this->m_webloadProgress->setValue(iProgress);
    this->m_webloadProgress->show();
}

void MainWindow::loadFinished(bool bSuccessed)
{
    if(bSuccessed) {
        this->m_labelProgress->setText(QString(tr("加载完成")));
        this->m_webloadProgress->hide();
    }else {
        this->m_labelProgress->setText(QString(tr("加载失败")));
        this->m_webloadProgress->hide();
    }

}


void MainWindow::history()
{
    QWebHistory *history = m_webView->history();
    QList<QWebHistoryItem> qql = history->items();
    QList<QWebHistoryItem>::iterator it;
    QString strHistory;
    for(it = qql.begin();it != qql.end();it++) {
        strHistory += it->title() + it->url().toString();
        strHistory += "\n";
    }

    QMessageBox::information(this,"history",strHistory);

}
