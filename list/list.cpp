#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

struct list_el {
    int data;
    list_el *addr;    
};

void setcur(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void hide_cursor() {
	CONSOLE_CURSOR_INFO cursor;    
	cursor.bVisible = FALSE;    
	cursor.dwSize = sizeof(cursor);    
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);    
	SetConsoleCursorInfo(handle, &cursor);
}

void confirm() {
    short confirm = 0;
    printf("===================================\n");
    printf("Нажмите Enter, чтобы продолжить...\n");
    while (confirm != 13) {
        confirm = getch();
    }
}

void warning(int list_size, short &option) {
    if (list_size == 0) {
        cout << endl << "===================================" << endl;
        cout << "Для работы с редактором вам необходимо создать список..." << endl;
        confirm();
        option = -option;
    }
    system("cls");
}

list_el* create_list(short size, short mode) {
    //if value "mode" != 0, it initializes the list (makes it in order)
    //if value "mode" == 0, it creates the list with zeros
    list_el *curr = 0, *next = 0;
    for(int i = 1; i <= size; ++i) {
        curr = new list_el;
        curr -> addr = next;
        if (mode == 0) {
            curr -> data = (size - i) + 1;
        } else {
            curr -> data = 0;
        }
        next = curr;
    }
    return curr; 
}

void print_list(list_el* head, short mode) {
    //if "mode" variabe == 1, it just outputs the list, nothing speacial
    //if "mode" variable == 2, it outputs the list with arrows connecting each node
    list_el* iterator = head;
    int i = 0;
    while (iterator != NULL) {
        if (mode == 1) {
            cout << iterator -> data;
        } else if (mode == 2) {
            cout << iterator -> data;
            if (iterator -> addr != NULL) {
                cout << " -> ";
            }
        }
        iterator = iterator -> addr;
        ++i;
    }
}

list_el* insert_el(list_el* head, int data, int index) {
    list_el* iterator = head;
    int i = 0;
    while (iterator != NULL) {
        if (index == 1 && i + 1 == index) {
            list_el* new_head = new list_el;
            new_head -> addr = head;
            new_head -> data = data; 
            head = new_head;
        } else if (i + 1 == index - 1 && index != 1) {
            list_el* following = iterator -> addr;
            iterator -> addr = new list_el;
            iterator = iterator -> addr;
            iterator -> data = data;
            iterator -> addr = following;
        } else {
            iterator = iterator -> addr;
        }
        ++i;
    } 
    return head;
}

list_el* delete_el(list_el* head, int index) {
    list_el* iterator = head;
    int i = 0;
    while (iterator != NULL) {
        if (index == 1 && i + 1 == index) {
            list_el* new_head = head -> addr;
            delete(head);
            return new_head;
        } else if (index != 1 && i + 1 == index - 1) {
            list_el* del_el = iterator -> addr;
            iterator -> addr = iterator -> addr -> addr;
            delete(del_el);
            return head;
        } else {
            iterator = iterator -> addr;
        }
        ++i;
    }
}

void delete_list(list_el* fake_head) {
    list_el* curr = fake_head;
    int i = 1;
    while (fake_head != NULL) {
        fake_head = fake_head -> addr;
        delete(curr);
        curr = fake_head;
    }
}

list_el* insert_some(list_el* head, int index, int values[], int amount) {
    list_el* iterator = head;
    list_el* following = 0;
    int i = 1, j = 0;
    while (iterator != NULL) { 
        if (i == index - 1) {
            following = iterator -> addr;
            list_el* new_node = new list_el;
            iterator -> addr = new_node;
            new_node -> data = values[j];
            ++j;
        } else if (i >= index && i < index + amount - 1) {
            list_el* new_node = new list_el;
            iterator -> addr = new_node;
            new_node -> data = values[j];
            ++j;
        } else if (i == index + amount - 1) {
            iterator -> addr = following;
        }
        ++i;
        iterator = iterator -> addr;
        }

    return head; 
}

list_el* insert_some_first(list_el* head, int index, int values[], int amount) {
    list_el* iterator = head;
    list_el* following = 0;
    list_el* new_head = new list_el;
    int i = 1, j = 0;
    while (iterator != NULL) { 
        if (i == 1) {
            following = iterator;
            iterator = new_head;
            iterator -> data = values[j];
            list_el* new_node = new list_el;
            iterator -> addr = new_node;
            ++j;
        } else if (i > 1 && i <= index + amount - 1) {
            iterator -> data = values[j];
            if (i == index + amount - 1) {
                iterator -> addr = following;
            } else {
                list_el* new_node = new list_el;
                iterator -> addr = new_node;
            }
            ++j;
        }
    
        if (iterator -> addr == NULL) {
            return new_head;
        }
        iterator = iterator -> addr;
        ++i;
        
    }
}

list_el* delete_some(list_el* head, int index, int amount) {
    list_el* iterator = head;
    list_el* previous = 0;
    list_el* new_head = 0;
    int i = 1;
    while (iterator != NULL) {
        if (index == 1) {
            for (int j = 0; j < amount; ++j) {
                list_el* del_node = iterator;
                iterator = iterator -> addr;
                new_head = iterator;
                delete(del_node);
               
            }
            return new_head;
        } else {
            if (i == index - 1) {
                previous = iterator;
                iterator = iterator -> addr;
            } else if (i >= index && i < index + amount) {
                list_el* del_node = iterator;
                iterator = iterator -> addr;
                delete(del_node);
                if (i == index + amount - 1) {
                    previous -> addr = iterator;
                    return head;
                }
            } else {
                iterator = iterator -> addr;
            }
            ++i;
        }
    }
}

list_el* reverse(list_el* head)
{
    list_el *prev = NULL, *curr = head, *next;
  
    while (curr) {
        next = curr->addr;
        curr->addr = prev;
        prev = curr;
        curr = next;
    }
    head = prev;

    return head;
}

list_el* sort(list_el* head, int list_size) {
    list_el* iterator = head;
    int sorted_values[list_size];
    int values[list_size];
    int index = 0;
    int min = 100;

    while (iterator != NULL) {
        values[index] = iterator -> data;
        iterator = iterator -> addr;
        ++index;
    }

    iterator = head;

    for (int i = 0; i < list_size; ++i) {
        for (int j = 0; j < list_size; ++j) {
            if (values[j] <= min) {
                min = values[j];
                index = j;
            }
            if (j == list_size - 1) {
                sorted_values[i] = min;
                values[index] = 100;
                min = 100;
            }
        }
    }

    index = 0;

    while (iterator != NULL) {
        iterator -> data = sorted_values[index];
        iterator = iterator -> addr;
        ++index;
    }

    return head;
    
}

short get_option(short option) {
    int max = 8;
    short input = getch();
    if (input >= 49 && input <= 56) {
        return input - '0';
    //escape    
    } else if (input == 27) {
        return -10;
     } else if (input == 13) {
        if (option >= 1 && option <= 8) {
            return -option;
        }
    //стрелка вниз
    } else if (input == 'H' + 8) {
        option += 1;
        if (option > max) {
            option = 1;
        }
        return option;
    //стрелка вверх
    } else if (input == 'H') {
        option -= 1;
        if (option < 1) {
            option = max;
        }
        return option;
    } else {
        return option;
    }
}

void menu(int option, list_el* head) {
    cout << "Добро пожаловать в редактор списков" << endl;
    cout << "===================================" << endl;

    if (option == 1) {
        cout << " 1) Создать список с n элементами <--" << endl;
    } else {
        cout << "1) Создать список с n элементами     " << endl;
    } 

    if (option == 2) {
        cout << " 2) Добавить элемент в список <--" << endl;
    } else {
        cout << "2) Добавить элемент в список     " << endl;
    }

    if (option == 3) {
        cout << " 3) Удалить элемент по индексу <--" << endl;
    } else {
        cout << "3) Удалить элемент по индексу     " << endl;
    }

    if (option == 4) {
        cout << " 4) Удалить список <--" << endl;
    } else {
        cout << "4) Удалить список     " << endl;
    }

    if (option == 5) {
        cout << " 5) Вставить часть списка <--" << endl;
    } else {
        cout << "5) Вставить часть списка     " << endl;
    }

    if (option == 6) {
        cout << " 6) Удалить часть списка <--" << endl;
    } else {
        cout << "6) Удалить часть списка     " << endl;
    }

    if (option == 7) {
        cout << " 7) Перевернуть список <--" << endl;
    } else {
        cout << "7) Перевернуть список     " << endl;
    }

    if (option == 8) {
        cout << " 8) Отсортировать список <--" << endl;
    } else {
        cout << "8) Отсортировать список     " << endl;
    }

    cout << "Escape - выйти" << endl;
    cout << "===================================" << endl;
    cout << "Ваш список: ";

    print_list(head, 2);
}

int get_value(int value, short &option, int max) {
    int add = 0;
    add = getch();

    if (add >= 49 && add <= 58 && (value * 10 + add - '0' <= max)) {
        value = value * 10 + add - '0';
        return value;
    } else if (add == 48 && (value * 10 <= max)) {
        value = value * 10;
        return value;
    } else if (add == 13 && value >= 1) {
        if (value != 0) {
            option = -option;
        }
        return value;
    } else if (add == 8) {
        value = value / 10;
        return value;
    } else {
        return value;
    }
    
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    short option = 1, quit = 0, flag_1 = 0;
    int list_size = 0;
    list_el* head = 0;

    while (quit == 0) {
        hide_cursor();
        setcur(0, 0);
        menu(option, head);
        option = get_option(option);

        if (option == -10) {
            quit = 1;

        } else if (option == -1) {
            if (list_size != 0) {
                cout << endl << "===================================" << endl;
                cout << "Сперва удалите существующий список..." << endl;
                option = 1;
                confirm();
                system("cls");
                continue;
            }

            while (option == -1) {
                setcur(0, 0);
                menu(1, head);
                cout << endl << "===================================" << endl;
                cout << "Введите длину списка: " << list_size << " ";
                list_size = get_value(list_size, option, 20);
            }
            head = create_list(list_size, 0);
            system("cls");

        } else if (option == -2) {
            warning(list_size, option);
            if (option == 2) {
                continue;
            }

            int index = 0, data = 0, flag = 0;
            while (option == -2) {
                setcur(0, 0);
                menu(2, head);
                cout << endl << "===================================" << endl;
                cout << "Введите номер элемента, который вы хотите добавить: " << index << " ";
                if (flag == 0) {
                    index = get_value(index, option, list_size + 1);
                    if (option == 2) {
                        option = -option;
                        flag = 1;
                    }
                } else {
                    cout << endl << "===================================" << endl;
                    cout << "Введите значение, которое вы хотите вставить: " << data << " ";
                    data = get_value(data, option, 100);
                } 
            }

            head = insert_el(head, data, index);
            list_size += 1;
            system("cls");

        } else if (option == -3) {
            warning(list_size, option);
            if (option == 3) {
                continue;
            }

            int index = 0, data = 0, flag = 0;
            while (option == -3) {
                setcur(0, 0);
                menu(3, head);
                cout << endl << "===================================" << endl;
                cout << "Введите номер элемента, который вы хотите удалить: " << index << " ";
                index = get_value(index, option, list_size);
            }

            head = delete_el(head, index);
            list_size -= 1;
            system("cls");

        } else if (option == -4) {
            warning(list_size, option);
            if (option == 4) {
                continue;
            }

            list_el* pepe_laugh = head;
            head = 0;
            delete_list(pepe_laugh);

            list_size = 0;
            option = -option;
        } else if (option == -5) {
            warning(list_size, option);
            if (option == 5) {
                continue;
            }

            int index = 0, amount = 0, flag = 0, cntr = 0, el = 0, value[21];
            while (option == -5) {
                setcur(0, 0);
                menu(5, head);
                cout << endl << "===================================" << endl;

                if (flag == 0) {
                    cout << "Введите количество элементов, которые вы хотите добавить: " << amount << " ";
                    amount = get_value(amount, option, 20);
                    if (option == 5) {
                        option = -option;
                        flag = 1;
                        system("cls");
                    }

                } else if (flag == 1) {
                    while (cntr != amount) {
                        setcur(0, 0);
                        menu(5, head);
                        cout << endl << "===================================" << endl;
                        cout << "Введите " << cntr + 1 << " элемент: " << el << " ";
                        el = get_value(el, option, 100);
                        if (option == 5) {
                            option = -option;
                            value[cntr] = el;
                            el = 0;
                            ++cntr;
                        } 
                    }
                    flag = 2;
                    system("cls");

                } else if (flag == 2) {
                    cout << "Введите номер элемента, с которого вы хотите вставить значения: " << index << " ";
                    index = get_value(index, option, list_size + 1);
                    if (option == 5) {
                        system("cls");
                    }
                }
            } 
            //the end of the monstrosity
            if (index == 1) {
                if (amount == 1) {
                    head = insert_el(head, value[0], index);
                } else {
                    head = insert_some_first(head, index, value, amount);
                }
            } else {
                head = insert_some(head, index, value, amount);
            }   
            list_size += amount;

        } else if (option == -6) {
            warning(list_size, option);
            if (option == 6) {
                continue;
            }

            int index = 0, amount = 0, flag = 0;
            while (option == -6) {
                setcur(0, 0);
                menu(6, head);
                cout << endl << "===================================" << endl;

                if (flag == 0) {
                    cout << "Введите количество элементов, которые вы хотите удалить: " << amount << " ";
                    amount = get_value(amount, option, list_size);
                    if (option == 6) {
                        option = -option;
                        flag = 1;
                        system("cls");
                    }

                } else if (flag == 1) {
                    cout << "Введите номер элемента, с которого начнется удаление: " << index << " ";
                    index = get_value(index, option, list_size - amount + 1);
                    if (option == 6) {
                        system("cls");
                    }
                }
            }
            
            if (amount == list_size) {
                list_el* pepe_laugh = head;
                delete_list(pepe_laugh);
                head = 0;
            } else {
                head = delete_some(head, index, amount);
            }

            list_size -= amount;

        } else if (option == -7) {
            warning(list_size, option);
            if (option == 7) {
                continue;
            }

            head = reverse(head);
            option = 7;
        } else if (option == -8) {
            warning(list_size, option);
            if (option == 8) {
                continue;
            }

            head = sort(head, list_size);
            option = 8;
        } 
    }
return 0;
}