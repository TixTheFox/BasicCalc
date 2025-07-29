#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QClipboard>
#include <QApplication>
#include "processor.h"
#include "PNumEditor.h"
#include "PNum.h"
#include "memory.h"

// перечисление всех возможных состояний контроллера
enum class controller_states {
    CONTROLLER_START,               // начальное состояние (оно же устанавливается после нажатия на C)
    CONTROLLER_EDIT_LOP,            // редактирование левого операнда
    CONTROLLER_EDIT_ROP,            // редактирование правого операнда
    CONTROLLER_OP_SELECTED,         // выбрана операция (далее возможны либо редактирование правого операнда, либо исполнение без редактирования)
    CONTROLLER_OP_DONE,             // операция завершена
    CONTROLLER_FUNC_DONE,           // завершено вычисление функции
};

// перечисление возможных операций над числом (строкой) в редакторе
enum class Editor_Operations {
    AddSym,
    AddZero,
    AddDot,
    ChangeSign,
    ClearLast,
    ClearAll,
    Delete,
};


/*
    Класс controller управляет логикой приложения, обрабатывает сигналы от интерфейса.
    Содержит редактор чисел, процессор вычислений и память.
*/
class Controller
{
private:
    PNumEditor editor;
    Processor<PNum> processor;
    Memory<PNum> memory;

    short unsigned int p = 10;                                                 // начальное основание системы счисления (совпадает с интерфейсом)
    controller_states state = controller_states::CONTROLLER_START;             // состояние контроллера

    void OnEditorChangeState();
    void EditorSetNum(const std::string num);

public:
    Controller();

    short unsigned GetP() { return p; }
    void SetP(short unsigned val);

    void EditorOperation(Editor_Operations op, char sym = 0);
    std::string EditorGetNum() { return editor.GetNum(); }

    void EditorKeyboardSetNum(std::string num);

    void ProcessorSetOperation(char op);
    void ProcessorExecuteFunc(short int op);
    void ProcessorExecute();

    void MemoryWrite();
    void MemoryAdd();
    void MemoryRead();
    void MemoryClear();
    bool MemoryIsUsed() { return memory.GetIsUsed(); }

    /*
        копирование в буфер обмена
    */
    void ClipboardCopy() {
        QApplication::clipboard()->setText(QString::fromStdString(EditorGetNum()));
    }

    /*
        вставка из буфера обмена
    */
    void ClipboardPaste() {
        EditorSetNum(QApplication::clipboard()->text().toStdString());
        OnEditorChangeState();
    }

};

#endif // CONTROLLER_H
