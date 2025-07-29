#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/*
    Класс MainWindow реализует интерфейс приложения и взаимодействует
    только с контроллером, передавая сигналы о нажатиях и устанавливая результаты операций
*/

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void OnPValueChanged(int value);

    void AddSymButtonClicked();
    void AddDotButtonClicked();
    void AddZeroButtonClicked();

    void SignButtonClicked();

    void ClearAllButtonClicked();
    void ClearLastButtonClicked();
    void DeleteButtonClicked();

    void OperationsButtonsClicked();
    void SqrButtonClicked();
    void RevButtonClicked();
    void ExecuteButtonClicked();

    void MemoryClearButtonClicked();
    void MemoryAddButtonClicked();
    void MemoryReadButtonClicked();
    void MemoryWriteButtonClicked();

    void HelpButtonClicked();

    void on_action_copy_triggered();

    void on_action_paste_triggered();

    void numberEdited(const QString& num);

private:
    Ui::MainWindow *ui;
    Controller controller;

    void SetActiveButtons();
    void MemoryLabelSet();
};
#endif // MAINWINDOW_H
