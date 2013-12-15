/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.0.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew_Random;
    QAction *actionQuit;
    QAction *actionNew_Custom;
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QGridLayout *centralLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *me_label;
    QLabel *humanScore;
    QHBoxLayout *horizontalLayout_2;
    QLabel *computer_label;
    QLabel *computerScore;
    QGroupBox *human_words_box;
    QWidget *gridLayoutWidget_2;
    QGridLayout *human_words_grid;
    QListWidget *humanWords;
    QGridLayout *gridLayout;
    QGroupBox *comp_words_box;
    QWidget *gridLayoutWidget;
    QGridLayout *comp_words_grid;
    QListWidget *computerWords;
    QLabel *enter_word_label;
    QLineEdit *humanInput;
    QPushButton *computerPlayButton;
    QMenuBar *menuBar;
    QMenu *menuGame;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(639, 434);
        actionNew_Random = new QAction(MainWindow);
        actionNew_Random->setObjectName(QStringLiteral("actionNew_Random"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        actionNew_Custom = new QAction(MainWindow);
        actionNew_Custom->setObjectName(QStringLiteral("actionNew_Custom"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 11, 611, 361));
        centralLayout = new QGridLayout(layoutWidget);
        centralLayout->setSpacing(6);
        centralLayout->setContentsMargins(11, 11, 11, 11);
        centralLayout->setObjectName(QStringLiteral("centralLayout"));
        centralLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        me_label = new QLabel(layoutWidget);
        me_label->setObjectName(QStringLiteral("me_label"));

        horizontalLayout->addWidget(me_label);

        humanScore = new QLabel(layoutWidget);
        humanScore->setObjectName(QStringLiteral("humanScore"));

        horizontalLayout->addWidget(humanScore);


        centralLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        computer_label = new QLabel(layoutWidget);
        computer_label->setObjectName(QStringLiteral("computer_label"));

        horizontalLayout_2->addWidget(computer_label);

        computerScore = new QLabel(layoutWidget);
        computerScore->setObjectName(QStringLiteral("computerScore"));

        horizontalLayout_2->addWidget(computerScore);


        centralLayout->addLayout(horizontalLayout_2, 0, 2, 1, 1);

        human_words_box = new QGroupBox(layoutWidget);
        human_words_box->setObjectName(QStringLiteral("human_words_box"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(human_words_box->sizePolicy().hasHeightForWidth());
        human_words_box->setSizePolicy(sizePolicy);
        gridLayoutWidget_2 = new QWidget(human_words_box);
        gridLayoutWidget_2->setObjectName(QStringLiteral("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(9, 29, 171, 261));
        human_words_grid = new QGridLayout(gridLayoutWidget_2);
        human_words_grid->setSpacing(6);
        human_words_grid->setContentsMargins(11, 11, 11, 11);
        human_words_grid->setObjectName(QStringLiteral("human_words_grid"));
        human_words_grid->setContentsMargins(0, 0, 0, 0);
        humanWords = new QListWidget(gridLayoutWidget_2);
        humanWords->setObjectName(QStringLiteral("humanWords"));
        QSizePolicy sizePolicy1(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(humanWords->sizePolicy().hasHeightForWidth());
        humanWords->setSizePolicy(sizePolicy1);

        human_words_grid->addWidget(humanWords, 0, 0, 1, 1);


        centralLayout->addWidget(human_words_box, 1, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetFixedSize);

        centralLayout->addLayout(gridLayout, 1, 1, 1, 1);

        comp_words_box = new QGroupBox(layoutWidget);
        comp_words_box->setObjectName(QStringLiteral("comp_words_box"));
        sizePolicy.setHeightForWidth(comp_words_box->sizePolicy().hasHeightForWidth());
        comp_words_box->setSizePolicy(sizePolicy);
        gridLayoutWidget = new QWidget(comp_words_box);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(9, 29, 181, 261));
        comp_words_grid = new QGridLayout(gridLayoutWidget);
        comp_words_grid->setSpacing(6);
        comp_words_grid->setContentsMargins(11, 11, 11, 11);
        comp_words_grid->setObjectName(QStringLiteral("comp_words_grid"));
        comp_words_grid->setSizeConstraint(QLayout::SetNoConstraint);
        comp_words_grid->setContentsMargins(0, 0, 0, 0);
        computerWords = new QListWidget(gridLayoutWidget);
        computerWords->setObjectName(QStringLiteral("computerWords"));
        QSizePolicy sizePolicy2(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy2.setHorizontalStretch(1);
        sizePolicy2.setVerticalStretch(1);
        sizePolicy2.setHeightForWidth(computerWords->sizePolicy().hasHeightForWidth());
        computerWords->setSizePolicy(sizePolicy2);
        computerWords->setMaximumSize(QSize(16777215, 16777215));

        comp_words_grid->addWidget(computerWords, 0, 0, 1, 1);


        centralLayout->addWidget(comp_words_box, 1, 2, 1, 1);

        enter_word_label = new QLabel(layoutWidget);
        enter_word_label->setObjectName(QStringLiteral("enter_word_label"));
        enter_word_label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        centralLayout->addWidget(enter_word_label, 2, 0, 1, 1);

        humanInput = new QLineEdit(layoutWidget);
        humanInput->setObjectName(QStringLiteral("humanInput"));

        centralLayout->addWidget(humanInput, 2, 1, 1, 1);

        computerPlayButton = new QPushButton(layoutWidget);
        computerPlayButton->setObjectName(QStringLiteral("computerPlayButton"));

        centralLayout->addWidget(computerPlayButton, 2, 2, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 639, 22));
        menuGame = new QMenu(menuBar);
        menuGame->setObjectName(QStringLiteral("menuGame"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setEnabled(false);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuGame->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuGame->addAction(actionNew_Random);
        menuGame->addAction(actionNew_Custom);
        menuGame->addAction(actionQuit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "CSE100ggle", 0));
        actionNew_Random->setText(QApplication::translate("MainWindow", "New Random", 0));
        actionNew_Random->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", 0));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", 0));
        actionNew_Custom->setText(QApplication::translate("MainWindow", "New Custom", 0));
        actionNew_Custom->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+N", 0));
        me_label->setText(QApplication::translate("MainWindow", "Me", 0));
        humanScore->setText(QApplication::translate("MainWindow", "0", 0));
        computer_label->setText(QApplication::translate("MainWindow", "Computer", 0));
        computerScore->setText(QApplication::translate("MainWindow", "0", 0));
        human_words_box->setTitle(QApplication::translate("MainWindow", "Word List", 0));
        comp_words_box->setTitle(QApplication::translate("MainWindow", "Word List", 0));
        enter_word_label->setText(QApplication::translate("MainWindow", "Enter Human Word: ", 0));
        computerPlayButton->setText(QApplication::translate("MainWindow", "Computer Play!", 0));
        menuGame->setTitle(QApplication::translate("MainWindow", "Game", 0));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
