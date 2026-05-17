#pragma once

#include <QMainWindow>

class QLineEdit;
class QTextEdit;
class QLabel;
class QPushButton;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

private slots:
    void onConvertClicked();
    void onLoadClicked();
    void onSaveClicked();

private:
    QLineEdit* inputEdit_;
    QLineEdit* fromBaseEdit_;
    QLineEdit* toBaseEdit_;

    QTextEdit* outputEdit_;
    QLabel* errorLabel_;

    QPushButton* convertButton_;
    QPushButton* loadButton_;
    QPushButton* saveButton_;

    void setupUi();
    void showError(const QString& message);
    void clearError();

    QString convertStub(const QString& input, int p, int q);
};