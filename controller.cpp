#include "controller.h"
#include <string>
#include <ctype.h>

Controller::Controller() {}

/*
    устанавливает новое основание системы счисления в Controller, Proccessor и Memory
    При этом проверяет его корректность
*/
void Controller::SetP(short unsigned val) {
    if (val >= 2 && val <= 16) {
        editor.SetNum(Converter::convert(editor.GetNum(), p, val, 7));
        p = val;
        processor.SetP(p);
        memory.SetP(p);
    }
    else
        throw std::invalid_argument("p must be in range [2, 16]");
}

/*
    Устанавливает операцию в процессоре
*/
void Controller::ProcessorSetOperation(char op) {
    short int op_int = 0;

    switch(op){
    case '+':
        op_int = NUM_SUM;
        break;
    case '-':
        op_int = NUM_SUB;
        break;
    case '*':
        op_int = NUM_MUL;
        break;
    case '/':
        op_int = NUM_DIV;
        break;
    }

    // если новая операция выбрана в момент редактуры второго операнда
    // то сначала вычисляется то, что в лежит в процессоре
    if (state == controller_states::CONTROLLER_EDIT_ROP) {
        ProcessorExecute();
    }

    processor.SetLop(PNum(editor.GetNum(), p));
    processor.SetOperation(op_int);

    // при выборе операции устанавливаем соотв. состояние контроллера
    state = controller_states::CONTROLLER_OP_SELECTED;
}

/*
    Функция вызывается всякий раз, когда меняется число в редакторе чисел
    Устанавливает состояние контроллера в зависимости от его предыдущего состояния
    Необходимо для обеспечения корректной логики работы
*/
void Controller::OnEditorChangeState() {
    if (state == controller_states::CONTROLLER_START)
        state = controller_states::CONTROLLER_EDIT_LOP;
    else if (state == controller_states::CONTROLLER_FUNC_DONE)
        state = controller_states::CONTROLLER_EDIT_LOP;
    else if (state == controller_states::CONTROLLER_OP_SELECTED)
        state = controller_states::CONTROLLER_EDIT_ROP;
}

/*
    Функция обеспечивает обработку изменения числа в редакторе
    через контроллер
*/
void Controller::EditorOperation(Editor_Operations op, char sym) {
    // если выбрана операция и произошло редактирование числа в строке ввода
    if (state == controller_states::CONTROLLER_OP_SELECTED){
        editor.Clear();
        // значит будет вводиться второй операнд
        state = controller_states::CONTROLLER_EDIT_ROP;
    // иначе если произведен рассчет и происходит редактирование
    } else if (state == controller_states::CONTROLLER_OP_DONE) {
        editor.Clear();
        // то состояние сбрасывается
        state = controller_states::CONTROLLER_START;
    }


    switch(op) {
    case(Editor_Operations::AddSym):
        editor.AddSym(sym);
        break;
    case(Editor_Operations::AddZero):
        editor.AddZero();
        break;
    case(Editor_Operations::AddDot):
        editor.AddDot();
        break;
    case(Editor_Operations::ChangeSign):
        editor.ChangeSign();
        break;
    case(Editor_Operations::ClearLast):
        editor.Clear();
        break;
    case(Editor_Operations::ClearAll):
        editor.Clear();
        break;
    case (Editor_Operations::Delete):
        editor.Delete();
        break;
    }

    // если ClearAll, то сброс состояния до начального
    if (op == Editor_Operations::ClearAll)
        state = controller_states::CONTROLLER_START;
    else
        OnEditorChangeState();
}

/*
    Устанавливает число в редакторе напрямую, проверяя его на корректность в заданной системе счисления
*/
void Controller::EditorSetNum(const std::string num) {
    if (PNumEditor::IsCorrect(num, p))
        editor.SetNum(num);
    else
        throw std::invalid_argument("Incorrect number in p-based number system");
}

/*
    Устанавливает число в редакторе в случае клавиатурного ввода. Проверяет ввод на корректность в заданной системе счисления
*/
void Controller::EditorKeyboardSetNum(std::string num) {
    qDebug() << num;
    if (PNumEditor::IsCorrect(num, p)){
        *(num.end() - 1) = toupper(*(num.end() - 1));
        qDebug() << num;
        editor.SetNum(num);
    }
}

/*
    Вычисление унарной функции процессором
    Производится над текущим операндом в редакторе и сразу же
    устанавливается на его место (в процессоре результат лежит в "правом операнде")
    Не меняет состояние контроллера
*/
void Controller::ProcessorExecuteFunc(short int op) {
    processor.SetRop(PNum(editor.GetNum(), p));
    processor.ExecuteFunction(op);
    editor.SetNum(processor.GetRop());
}

/*
    Вычисление бинарной операции процессором. Вызывается при нажатии на "="
    Логика вычисления зависит от состояния контроллера
    Результат вычисления бинарной операии лежит в "левом операнде"
*/
void Controller::ProcessorExecute() {
    //если состояние "выбрана операция" (но не введен второй аргумент)
    if (state == controller_states::CONTROLLER_OP_SELECTED){
        // устанавливаем флаг отсутсвия второго операнда
        processor.setSecondOperandFlag(false);
        processor.Execute();
        editor.SetNum(processor.GetLop());
        state = controller_states::CONTROLLER_OP_DONE;
    }
    //если состояние "введен второй аргумент"
    else if (state == controller_states::CONTROLLER_EDIT_ROP) {
        // устанавливаем флаг наличия второго операнда
        processor.setSecondOperandFlag(true);
        processor.SetRop(PNum(editor.GetNum(), p));
        processor.Execute();
        editor.SetNum(processor.GetLop());
        state = controller_states::CONTROLLER_OP_DONE;
    }
    //если состояние "операция завершена"
    else if (state == controller_states::CONTROLLER_OP_DONE){
        // делаем то же самое еще раз (левый операнд теперь - результат предыдущего выполнения)
        processor.Execute();
        editor.SetNum(processor.GetLop());
        state = controller_states::CONTROLLER_OP_DONE;
    }
}

/*
    Запись в память
*/
void Controller::MemoryWrite() {
    // если запись производится в момент редактуры второго операнда, то
    // в памяти окажется результат операции, а не редактируемое число
    if (state == controller_states::CONTROLLER_EDIT_ROP) {
        ProcessorExecute();
    }
    PNum tmp(editor.GetNum(), p);
    memory.Write(tmp);
}

/*
    Добавление к числу в памяти
*/
void Controller::MemoryAdd() {
    // если добавление производится в момент редактуры второго операнда, то
    // к памяти прибавится результат операции, а не редактируемое число
    if (state == controller_states::CONTROLLER_EDIT_ROP) {
        ProcessorExecute();
    }
    PNum tmp(editor.GetNum(), p);
    memory.Add(tmp);
}

/*
    Чтение из памяти
    Меняет состояние контроллера
*/
void Controller::MemoryRead() {
    if(memory.GetIsUsed()){
        editor.SetNum(memory.Read());
        switch(state){
        case(controller_states::CONTROLLER_OP_SELECTED):
            state = controller_states::CONTROLLER_EDIT_ROP;
            break;
        case(controller_states::CONTROLLER_OP_DONE):
            state = controller_states::CONTROLLER_EDIT_LOP;
            break;
        default:
            break;
        }
    }
}

/*
    Очистка памяти
*/
void Controller::MemoryClear() {
    memory.Clear();
}
