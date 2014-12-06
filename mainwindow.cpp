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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWidget* widget = new QWidget(this);

    QHBoxLayout *hlayout = new QHBoxLayout;
    m_addr = new QLineEdit(QString("http://www.baidu.com"),widget);

    QPushButton *go = new QPushButton(QString("go"));
    QString str = m_addr->text();

    hlayout->addWidget(m_addr);
    hlayout->addWidget(go);
    hlayout->stretch(0);

    connect(go,SIGNAL(clicked()),this,SLOT(redirect()));
    connect(m_addr,SIGNAL(returnPressed()),this,SLOT(redirect()));

    QVBoxLayout *mainlayout = new QVBoxLayout;

    m_webView = new QWebView;
    m_webView->load(QUrl("http://www.baidu.com"));
    mainlayout->addLayout(hlayout);
    mainlayout->addWidget(m_webView);

    widget->setLayout(mainlayout);

    this->setCentralWidget(widget);

    QHBoxLayout *statusBar1Layout = new QHBoxLayout;

    m_statusBar = this->statusBar();
    m_webloadProgress = new QProgressBar;
    QLabel *labelProgress = new QLabel("加载进度：");

    m_webloadProgress->setRange(0,100);
    m_webloadProgress->setValue(0);
    m_statusBar->addWidget(labelProgress);
    m_statusBar->addWidget(m_webloadProgress);

    QAction *showProgressbar = new QAction;
    m_statusBar->addAction();


    //m_statusBar->setFixedHeight(20);
   // m_statusBar->setLayout(statusBar1Layout);
    m_statusBar->setStyleSheet(QString("QStatusBar::item{border: 0px}"));

    connect(m_webView,SIGNAL(loadProgress(int)),m_webloadProgress,SLOT(setValue(int)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::redirect()
{
    if(NULL != m_addr){
        QString strAddr = m_addr->text();
        if(strAddr.startsWith("http://")) {
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
