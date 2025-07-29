#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QDesktopServices>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // кнопки, отвечающие за цифры
    QList<QPushButton *> Number_Buttons{
       ui->Button_1,
       ui->Button_2,
       ui->Button_3,
       ui->Button_4,
       ui->Button_5,
       ui->Button_6,
       ui->Button_7,
       ui->Button_8,
       ui->Button_9,
       ui->Button_A,
       ui->Button_B,
       ui->Button_C,
       ui->Button_D,
       ui->Button_E,
       ui->Button_F,
    };

    // подключаю обработку нажатий на цифры
    for (auto i : Number_Buttons) {
        connect(i, SIGNAL(clicked()), this, SLOT(AddSymButtonClicked()));
    }

    // кнопки бинарных операций
    QList<QPushButton *> Op_Buttons{
        ui->Button_Plus,
        ui->Button_Minus,
        ui->Button_Mul,
        ui->Button_Div,
    };

    // подключение обработки нажатий на Op_Buttons
    for (auto i : Op_Buttons) {
        connect(i, SIGNAL(clicked()), this, SLOT(OperationsButtonsClicked()));
    }

    connect(ui->Button_Sqr, SIGNAL(clicked()), this, SLOT(SqrButtonClicked()));
    connect(ui->Button_Rev, SIGNAL(clicked()), this, SLOT(RevButtonClicked()));
    connect(ui->Button_Execute, SIGNAL(clicked()), this, SLOT(ExecuteButtonClicked()));

    connect(ui->Button_Dot, SIGNAL(clicked()), this, SLOT(AddDotButtonClicked()));
    connect(ui->Button_0, SIGNAL(clicked()), this, SLOT(AddZeroButtonClicked()));
    connect(ui->Button_Sign, SIGNAL(clicked()), this, SLOT(SignButtonClicked()));

    connect(ui->Button_Delete, SIGNAL(clicked()), this, SLOT(DeleteButtonClicked()));
    connect(ui->Button_Clear_All, SIGNAL(clicked()), this, SLOT(ClearAllButtonClicked()));
    connect(ui->Button_Clear_Last, SIGNAL(clicked()), this, SLOT(ClearLastButtonClicked()));

    connect(ui->Button_MemoryClear, SIGNAL(clicked()), this, SLOT(MemoryClearButtonClicked()));
    connect(ui->Button_MemoryAdd, SIGNAL(clicked()), this, SLOT(MemoryAddButtonClicked()));
    connect(ui->Button_MemoryRead, SIGNAL(clicked()), this, SLOT(MemoryReadButtonClicked()));
    connect(ui->Button_MemoryWrite, SIGNAL(clicked()), this, SLOT(MemoryWriteButtonClicked()));

    // подключение обработки смены основания системы счисления
    connect(ui->spinBox_p, SIGNAL(valueChanged(int)), this, SLOT(OnPValueChanged(int)));

    // подключение обработки вызова справки
    connect(ui->menu_help, SIGNAL(aboutToShow()), this, SLOT(HelpButtonClicked()));

    // подключение обработки ввода с клавиатуры
    connect(ui->NumberLineEdit, SIGNAL(textEdited(QString)), this, SLOT(numberEdited(QString)));

    SetActiveButtons();
}

/*
    Устанавливает активные кнопки (цифры) в соотв. с системой счисления
 */
void MainWindow::SetActiveButtons() {
    QList<QPushButton *> Number_Buttons{
        ui->Button_0,
        ui->Button_1,
        ui->Button_2,
        ui->Button_3,
        ui->Button_4,
        ui->Button_5,
        ui->Button_6,
        ui->Button_7,
        ui->Button_8,
        ui->Button_9,
        ui->Button_A,
        ui->Button_B,
        ui->Button_C,
        ui->Button_D,
        ui->Button_E,
        ui->Button_F,
    };

    short unsigned p = controller.GetP();

    for (qsizetype i = 0; i < 16; i++) {
        if (i < p) {
            Number_Buttons[i]->setEnabled(true);
            Number_Buttons[i]->setStyleSheet("");
        } else {
            Number_Buttons[i]->setEnabled(false);
            Number_Buttons[i]->setStyleSheet("background-color: #dad5db");
        }
    }
}

/*
    operation buttons
*/

/*
    обработка нажатия на SQR
*/
void MainWindow::SqrButtonClicked() {
    controller.ProcessorExecuteFunc(NUM_SQR);
    ui->NumberLineEdit->setText(QString::fromStdString(controller.EditorGetNum()));
}

/*
    обработка нажатия на "1/x"
*/
void MainWindow::RevButtonClicked() {
    controller.ProcessorExecuteFunc(NUM_REV);
    ui->NumberLineEdit->setText(QString::fromStdString(controller.EditorGetNum()));
}

/*
    обработка нажатия на "="
*/
void MainWindow::ExecuteButtonClicked() {
    controller.ProcessorExecute();
    ui->NumberLineEdit->setText(QString::fromStdString(controller.EditorGetNum()));
}

/*
    обработка нажатия на кнопки бинарных оперций
*/
void MainWindow::OperationsButtonsClicked() {
    QPushButton *button = (QPushButton *) sender();
    controller.ProcessorSetOperation(button->text().toStdString()[0]);
    ui->NumberLineEdit->setText(QString::fromStdString(controller.EditorGetNum()));
}


/*
    text edit buttons
*/

/*
    обработка нажатия на кнопки цифр
*/
void MainWindow::AddSymButtonClicked() {
    QPushButton *button = (QPushButton *) sender();
    controller.EditorOperation(Editor_Operations::AddSym, button->text().toStdString()[0]);
    ui->NumberLineEdit->setText(QString::fromStdString(controller.EditorGetNum()));
}

/*
    обработка нажатия на кнопку добавления точки
*/
void MainWindow::AddDotButtonClicked() {
    controller.EditorOperation(Editor_Operations::AddDot);
    ui->NumberLineEdit->setText(QString::fromStdString(controller.EditorGetNum()));
}

/*
    обработка нажатия на кнопку добавления нуля
*/
void MainWindow::AddZeroButtonClicked() {
    controller.EditorOperation(Editor_Operations::AddZero);
    ui->NumberLineEdit->setText(QString::fromStdString(controller.EditorGetNum()));
}

/*
    обработка нажатия на кнопку смены знака числа
*/
void MainWindow::SignButtonClicked() {
    controller.EditorOperation(Editor_Operations::ChangeSign);
    ui->NumberLineEdit->setText(QString::fromStdString(controller.EditorGetNum()));
}

/*
    CLR/DEL buttons
*/

/*
    обработка нажатия на кнопку C
*/
void MainWindow::ClearAllButtonClicked() {
    controller.EditorOperation(Editor_Operations::ClearAll);
    ui->NumberLineEdit->setText(QString::fromStdString(controller.EditorGetNum()));
}

/*
    обработка нажатия на кнопку CE
*/
void MainWindow::ClearLastButtonClicked() {
    controller.EditorOperation(Editor_Operations::ClearLast);
    ui->NumberLineEdit->setText(QString::fromStdString(controller.EditorGetNum()));
}

/*
    обработка нажатия на кнопку DEL
*/
void MainWindow::DeleteButtonClicked() {
    controller.EditorOperation(Editor_Operations::Delete);
    ui->NumberLineEdit->setText(QString::fromStdString(controller.EditorGetNum()));
}

/*
    обработка смены основания системы счисления
*/
void MainWindow::OnPValueChanged(int value) {
    controller.SetP((unsigned short) value);
    ui->NumberLineEdit->setText(QString::fromStdString(controller.EditorGetNum()));
    SetActiveButtons();
}

/*
    MEMORY buttons
*/

/*
    обработка нажатия MC
*/
void MainWindow::MemoryClearButtonClicked() {
    controller.MemoryClear();
    MemoryLabelSet();
}

/*
    обработка нажатия M+
*/
void MainWindow::MemoryAddButtonClicked() {
    controller.MemoryAdd();
    ui->NumberLineEdit->setText(QString::fromStdString(controller.EditorGetNum()));
    MemoryLabelSet();
}

/*
    обработка нажатия MR
*/
void MainWindow::MemoryReadButtonClicked() {
    controller.MemoryRead();
    ui->NumberLineEdit->setText(QString::fromStdString(controller.EditorGetNum()));
    MemoryLabelSet();
}

/*
    обработка нажатия MS
*/
void MainWindow::MemoryWriteButtonClicked() {
    controller.MemoryWrite();
    ui->NumberLineEdit->setText(QString::fromStdString(controller.EditorGetNum()));
    MemoryLabelSet();
}

/*
    установка значка об использовании памяти
*/
void MainWindow::MemoryLabelSet() {
    if (controller.MemoryIsUsed()) {
        ui->Label_Memory->setText("M");
    } else {
        ui->Label_Memory->setText("");
    }
}

/*
    HElP menu
*/
void MainWindow::HelpButtonClicked() {
    QDesktopServices::openUrl(QUrl(QCoreApplication::applicationDirPath() + "/readme.txt"));
}

/*
    BUFFER menu
*/

/*
    обработка нажатия на "Правка" -> "Копировать"
*/
void MainWindow::on_action_copy_triggered(){
    controller.ClipboardCopy();
}

/*
    обработка нажатия на "Правка" -> "Вставить"
*/
void MainWindow::on_action_paste_triggered()
{
    try{
        controller.ClipboardPaste();
        ui->NumberLineEdit->setText(QString::fromStdString(controller.EditorGetNum()));
    } catch (const std::invalid_argument& e) {
        QMessageBox msg;
        msg.setText("Невозможно вставить число из буфера обмена - число не является корректным в заданной системе счисления");
        msg.setDefaultButton(QMessageBox::Ok);
        msg.setWindowTitle("Калькулятор p-ичных чисел");
        msg.setIcon(QMessageBox::Warning);
        msg.exec();
    }
}

/*
    Keyboard edit
*/

/*
    обработка редактирования числа с клавиатуры
*/
void MainWindow::numberEdited(const QString& num) {
    controller.EditorKeyboardSetNum(num.toStdString());
    ui->NumberLineEdit->setText(QString::fromStdString(controller.EditorGetNum()));
}



MainWindow::~MainWindow()
{
    delete ui;
}
