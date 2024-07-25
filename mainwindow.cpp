#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRandomGenerator>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QVBoxLayout>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , scene(new QGraphicsScene(this))
    , timer(new QTimer(this))
    , currentIndex(0)
    , currentRow(0)
{
    ui->setupUi(this);
    button = new QPushButton("Nytt Spill", this);
    button->setFixedSize(150, 60); 
    QFont font("Arial", 11, QFont::Bold);
    button->setFont(font);
    QPalette palette = button->palette();
    palette.setColor(QPalette::ButtonText, Qt::black);
    button->setPalette(palette);	
    button->setGeometry(10, 10, 150, 30);
    connect(button, &QPushButton::clicked, this, &MainWindow::Button_clicked);
    QLabel *label = new QLabel("Lotto", this);  
    label->setAlignment(Qt::AlignCenter);  
    label->setGeometry(300, 0, 180, 80);
    label->setStyleSheet("QLabel { color : red; }");
    QFont fontlabel("Arial", 18, QFont::Bold);
    label->setFont(fontlabel);
    graphicsView = new QGraphicsView(this);
    graphicsView->setGeometry(10, 10, 100, 100);    
    graphicsView->setScene(scene);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(button);
    layout->addWidget(graphicsView);
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
    connect(timer, &QTimer::timeout, this, &MainWindow::lottoNumbers);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Button_clicked()
{
    scene->clear();
    currentIndex = 0;
    currentRow = 0;
    Numbers.clear();
    QList<int> numbers;
   
    for (int i = 0; i < 1; ++i) {
        while (numbers.size() < 7) {
            int number = QRandomGenerator::global()->bounded(1, 35); 
            if (!numbers.contains(number)) {
                numbers.append(number);
            }
        }
        int extraNumber;
        do {
            extraNumber = QRandomGenerator::global()->bounded(1, 35);
        } while (numbers.contains(extraNumber));
        numbers.append(extraNumber);
        Numbers.append(numbers);
    }
    timer->start(500); 
}

void MainWindow::lottoNumbers()
{
    QGraphicsView view(this);
    if (currentRow < Numbers.size()) {
        const QList<int>& numbers = Numbers[currentRow];
        if (currentIndex < numbers.size()) {
            int x = currentIndex * 60; 
            int y = currentRow * 60; 
            QPen pen(Qt::red); 
            pen.setWidth(3); 
            QPen pen2(Qt::black); 
            pen.setWidth(3);
            QGraphicsEllipseItem *circle;
            if (currentIndex == numbers.size() - 1) {
               circle = scene->addEllipse(x, y, 50, 50, QPen(), QBrush(Qt::black));
               circle->setPen(pen2);
	    } else {
               circle = scene->addEllipse(x, y, 50, 50, QPen(), QBrush(Qt::red	));
               circle->setPen(pen);
	    }
			
            QGraphicsTextItem *text = scene->addText(QString::number(numbers[currentIndex]));
	    if(numbers[currentIndex] < 10) 
	    {
		text->setPos(x + 15, y + 10);
	    }
	    else  {
		text->setPos(x + 9, y + 9);
	    }			
	    text->setDefaultTextColor(Qt::white);
            QFont font("Avenir", 15, QFont::Bold);
            text->setFont(font);
	    currentIndex++;
        } else {
            currentIndex = 0;
            currentRow++;
        }
    } else {
        timer->stop();
    }
}

