#include "mainwindow.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
    inputEdit_(nullptr),
    fromBaseEdit_(nullptr),
    toBaseEdit_(nullptr),
    outputEdit_(nullptr),
    errorLabel_(nullptr),
    convertButton_(nullptr),
    loadButton_(nullptr),
    saveButton_(nullptr) {
    setupUi();
}

void MainWindow::setupUi() {
    setWindowTitle("Universal Converter");
    resize(900, 550);

    QWidget* central = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(central);

    QLabel* titleLabel = new QLabel("Universal Converter");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 26px; font-weight: bold;");

    QLabel* subtitleLabel = new QLabel("Точный перевод рациональных чисел между системами счисления");
    subtitleLabel->setAlignment(Qt::AlignCenter);
    subtitleLabel->setStyleSheet("font-size: 14px; color: #4b5563;");

    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(subtitleLabel);

    QHBoxLayout* contentLayout = new QHBoxLayout;

    QVBoxLayout* leftLayout = new QVBoxLayout;
    QLabel* inputTitle = new QLabel("Ввод данных");
    inputTitle->setStyleSheet("font-size: 18px; font-weight: bold; color: white;");

    inputEdit_ = new QLineEdit;
    fromBaseEdit_ = new QLineEdit;
    toBaseEdit_ = new QLineEdit;

    inputEdit_->setPlaceholderText("Например: 0.12(34)");
    fromBaseEdit_->setPlaceholderText("2.500");
    toBaseEdit_->setPlaceholderText("2.500");

    QFormLayout* formLayout = new QFormLayout;
    formLayout->addRow("Исходное число:", inputEdit_);
    formLayout->addRow("Основание p:", fromBaseEdit_);
    formLayout->addRow("Основание q:", toBaseEdit_);

    QHBoxLayout* buttonLayout = new QHBoxLayout;

    convertButton_ = new QPushButton("Convert");
    loadButton_ = new QPushButton("Load File");
    saveButton_ = new QPushButton("Save Result");

    buttonLayout->addWidget(convertButton_);
    buttonLayout->addWidget(loadButton_);
    buttonLayout->addWidget(saveButton_);

    leftLayout->addWidget(inputTitle);
    leftLayout->addLayout(formLayout);
    leftLayout->addLayout(buttonLayout);
    leftLayout->addStretch();

    QVBoxLayout* rightLayout = new QVBoxLayout;
    QLabel* outputTitle = new QLabel("Результат");
    outputTitle->setStyleSheet("font-size: 18px; font-weight: bold; color: white;");

    outputEdit_ = new QTextEdit;
    outputEdit_->setReadOnly(true);
    outputEdit_->setPlaceholderText("Здесь появится результат");

    rightLayout->addWidget(outputTitle);
    rightLayout->addWidget(outputEdit_);

    contentLayout->addLayout(leftLayout, 1);
    contentLayout->addLayout(rightLayout, 1);

    mainLayout->addLayout(contentLayout);

    errorLabel_ = new QLabel;
    errorLabel_->setWordWrap(true);
    errorLabel_->setStyleSheet("color: red; font-weight: bold;");
    mainLayout->addWidget(errorLabel_);

    setCentralWidget(central);


        setStyleSheet(R"(

    QMainWindow {
        background-color: #0f172a;
    }

    QWidget {
        color: #e2e8f0;
        font-size: 14px;
    }

    QLabel {
        color: #e2e8f0;
    }

    QLineEdit, QTextEdit {
        background-color: #1e293b;
        color: #f8fafc;

        border: 1px solid #334155;
        border-radius: 10px;

        padding: 8px;
        font-size: 14px;
    }

    QLineEdit:focus, QTextEdit:focus {
        border: 1px solid #3b82f6;
    }

    QPushButton {
        background-color: #2563eb;
        color: white;

        border: none;
        border-radius: 10px;

        padding: 10px 18px;

        font-size: 14px;
        font-weight: bold;
    }

    QPushButton:hover {
        background-color: #3b82f6;
    }

    QPushButton:pressed {
        background-color: #1d4ed8;
    }

    QScrollBar:vertical {
        background: #1e293b;
        width: 12px;
        margin: 0px;
    }

    QScrollBar::handle:vertical {
        background: #475569;
        border-radius: 6px;
        min-height: 20px;
    }

    QScrollBar::handle:vertical:hover {
        background: #64748b;
    }

    )");

    connect(convertButton_, &QPushButton::clicked,
            this, &MainWindow::onConvertClicked);

    connect(loadButton_, &QPushButton::clicked,
            this, &MainWindow::onLoadClicked);

    connect(saveButton_, &QPushButton::clicked,
            this, &MainWindow::onSaveClicked);
}
void MainWindow::onConvertClicked() {

}

void MainWindow::onLoadClicked() {

}

void MainWindow::onSaveClicked() {

}

void MainWindow::showError(const QString& message) {
    errorLabel_->setText(message);
}

void MainWindow::clearError() {
    errorLabel_->clear();
}

QString MainWindow::convertStub(const QString& input, int p, int q) {
    return "input = " + input +
           "\np = " + QString::number(p) +
           "\nq = " + QString::number(q);
}