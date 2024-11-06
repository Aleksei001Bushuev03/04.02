#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

class Address {
private:
    std::string city;
    std::string street;
    int house_number;
    int apartment_number;

public:
    Address(const std::string& city, const std::string& street, int house_number, int apartment_number)
        : city(city), street(street), house_number(house_number), apartment_number(apartment_number) {}

    std::string get_output_address() const {
        return city + ", " + street + ", " + std::to_string(house_number) + ", " + std::to_string(apartment_number);
    }

    std::string get_city() const {
        return city;
    }
};

void sort(Address* addresses[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (addresses[i]->get_city() > addresses[j]->get_city()) {
                std::swap(addresses[i], addresses[j]);
            }
        }
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::ifstream input_file("in.txt");
    std::ofstream output_file("out.txt");

    if (!input_file.is_open()) {
        std::cerr << "Ошибка открытия входного файла!" << std::endl;
        return 1;
    }

    if (!output_file.is_open()) {
        std::cerr << "Ошибка открытия выходного файла!" << std::endl;
        return 1;
    }

    int address_count;
    input_file >> address_count;

    if (input_file.fail() || address_count <= 0) { 
        std::cerr << "Некорректное количество адресов в файле!" << std::endl;
        return 1;
    }
    input_file.ignore(); 

    Address** addresses = new(std::nothrow) Address * [address_count];
    if (addresses == nullptr) {
        std::cerr << "Ошибка выделения памяти для массива адресов!" << std::endl;
        return 1;
    }

    for (int i = 0; i < address_count; ++i) {
        std::string city, street;
        int house_number, apartment_number;

        std::getline(input_file, city);
        std::getline(input_file, street);
        input_file >> house_number >> apartment_number;

        if (input_file.fail()) { 
            std::cerr << "Ошибка чтения данных для адреса " << i + 1 << "!" << std::endl;
            for (int j = 0; j < i; ++j) {
                delete addresses[j];
            }
            delete[] addresses;
            return 1;
        }
        input_file.ignore(); 

        addresses[i] = new(std::nothrow) Address(city, street, house_number, apartment_number);
        if (addresses[i] == nullptr) {
            std::cerr << "Ошибка выделения памяти для адреса " << i + 1 << "!" << std::endl;
            for (int j = 0; j < i; ++j) {
                delete addresses[j];
            }
            delete[] addresses;
            return 1;
        }
    }

    sort(addresses, address_count);

    output_file << address_count << std::endl;

    for (int i = 0; i < address_count; ++i) {
        output_file << addresses[i]->get_output_address() << std::endl;
        delete addresses[i]; 
    }

    delete[] addresses;

    input_file.close();
    output_file.close();

    std::cout << "Адреса успешно записаны в файл out.txt в отсортированном порядке." << std::endl;

    return 0;
}
