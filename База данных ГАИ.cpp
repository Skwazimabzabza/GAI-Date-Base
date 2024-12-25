// База данных ГАИ.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>


struct Violation {
    std::string Description;
};

struct GAIDataBase{
    std::string CarNumber;
    std::vector<Violation> violations;
    GAIDataBase* LeftOffence;
    GAIDataBase* RightOffence;

    GAIDataBase(std::string CN): CarNumber(CN), LeftOffence(nullptr), RightOffence(nullptr){}
};

void AddViolation(GAIDataBase*& GDB, std::string carNumber, Violation violation) {
    if (GDB == nullptr) {
        GDB = new GAIDataBase(carNumber);
        GDB->violations.push_back(violation);
        return;
    }
    if (carNumber < GDB->CarNumber){
        AddViolation(GDB->LeftOffence, carNumber, violation);
    }
    else if (carNumber < GDB->CarNumber) {
        AddViolation(GDB->RightOffence, carNumber, violation);
    }
    else {
        bool violationExists = false;
        for (const auto& v : GDB->violations) {
            if (v.Description == violation.Description) {
                violationExists = true;
                break;
            }
        }
        if (!violationExists) {
            GDB->violations.push_back(violation);
        }
        else {
            std::cout << "Предупреждение: Нарушение для автомобиля " << carNumber << " уже существует.\n";
        }
    }
    
}

GAIDataBase* FindCar(GAIDataBase* GDB, std::string carNumber) {
    if (GDB == nullptr || GDB->CarNumber == carNumber) {
        return GDB;
    }
    if (carNumber < GDB->CarNumber) {
        return FindCar(GDB->LeftOffence, carNumber);
    }
    else {
        return FindCar(GDB->RightOffence, carNumber);
    }
}

int main()
{
    setlocale(LC_ALL, "Ru");

    GAIDataBase* GDB = nullptr;
    GAIDataBase* GDB1 = nullptr;

    
    Violation v1 = { "Превышение скорости" };
    AddViolation(GDB, "A123BB", v1);

    Violation v2 = { "Проезд на красный свет" };
    AddViolation(GDB, "A123BB", v2);

    Violation v3 = { "Неправильная парковка" };
    AddViolation(GDB1, "B456CC", v3);

  
    GAIDataBase* foundCar = FindCar(GDB1, "B456CC");
    if (foundCar != nullptr) {
        std::cout << "Нарушения для автомобиля " << foundCar->CarNumber << ":\n";
        for (const auto& v : foundCar->violations) {
            std::cout << "- " << v.Description << "\n";
        }
    }
    else {
        std::cout << "Автомобиль не найден.\n";
    }

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
