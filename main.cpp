#include <iostream>
using namespace std;
#define MAX_SIZE 1000

//设计联系人结构体
struct Person
{
    string name;
    string sex; //1-男， 2-女
    int age;
    string phone;
    string addr;
};

//设计通讯录结构体
struct AddressBook
{
    //联系人数组
    struct Person personArr[MAX_SIZE];

    //联系人数量
    int size;
};

//1、添加联系人
void addPerson(struct AddressBook *abs)  //需要用指针传递而不是值传递，因为这样才能修改实参
{
    //判断通讯录是否已满，如果满了就不再添加
    if (abs->size == MAX_SIZE)
    {
        cout << "通讯录已满，无法添加" << endl;
        return;
    }
    else
    {    //添加联系人

        //姓名
        string name;
        cout << "请输入姓名：" << endl;
        cin >> name;
        abs->personArr[abs->size].name = name; //为什么长这样，因为abs是通讯录结构体，而这个结构体里面是一个成员数组，数组元素又是联系人结构体

        //性别
        int bi_sex = 0;
        while (true) {
            cout << "请输入性别：" << endl;
            cout << "1-男， 2-女" << endl;
            cin >> bi_sex;
            if (bi_sex == 1) {
                abs->personArr[abs->size].sex = "男";
                break;
            } else if (bi_sex == 2) {
                abs->personArr[abs->size].sex = "女";
                break;
            } else {
                cout << "输入错误，请重新输入：" << endl;
            }
        }

        //年龄
        cout << "请输入年龄：" << endl;
        int age = 0;
        while (1) {
            cin >> age;
            //如果输入正确的数字
            if (0< age && age < 150) {
                abs->personArr[abs->size].age = age;
                break;
            }
            cout << "输入错误，请重新输入：" << endl;
        }

        //电话
        cout << "请联系人输入电话：" << endl;
        string p_phone;
        cin >> p_phone;
        abs->personArr[abs->size].phone = p_phone;

        //地址
        cout << "请联系人输入地址：" << endl;
        string p_addr;
        cin >> p_addr;
        abs->personArr[abs->size].addr = p_addr;

        //更新通讯录人数
        abs->size++;

        cout << "添加成功" << endl;

        system("pause");//按任意键继续
        //system("cls");//清屏
    }
}

//2.显示所有联系人的函数
void showPerson(struct AddressBook * abs) {
    //判断通讯录中人数是否为0，若是0，则提示人数为0
    //不为0，显示记录的联系人信息
    if (abs->size == 0) {
        cout << "当前通讯录人数为0，无数据" << endl;
    }else {
        for (int i = 0; i < abs->size; i++) {
            cout << "姓名：" << abs->personArr[i].name << "\t";
            cout << "性别：" << abs->personArr[i].sex << "\t";
            cout << "年龄：" << abs->personArr[i].age << "\t";
            cout << "电话：" << abs->personArr[i].phone << "\t";
            cout << "地址：" << abs->personArr[i].addr << endl;
        }
    }
    system("pause");//按任意键继续
    system("cls");//清屏
}

//检测联系人是否存在，如果存在，返回联系人索引，不存在则返回-1
//参数：通讯录结构体指针，联系人姓名
int isExist(struct AddressBook *abs, string name)
{
    for (int i = 0; i < abs->size; i++)
    {
        if (abs->personArr[i].name == name) {
            return i; //return 语句的作用是立即结束函数并返回值。所以只要在循环中找到匹配项，函数会立刻返回，不会继续执行也就是不会再返回-1
        }

    }
    return -1;
}

//3.删除联系人
void deletePerson(AddressBook * abs) {
    cout << "请输入要删除的联系人" << endl;
    string name;
    cin >> name;

    //ret == -1   未查到
    //ret != -1   找到
    int ret = isExist(abs, name);
    if (ret != -1) {
        //查找到人，要进行删除操作
        for (int i = ret; i < abs->size; i++) {
            //数据前移
            abs->personArr[i] = abs->personArr[i+1];
        }
        abs->size--;  //更新通讯录人数
        cout << "删除成功" << endl;
    }else {
        cout << "查无此人" << endl;

    }
    system("pause");
    system("cls");
}

//4.查找联系人
void findPerson(AddressBook * abs) {
    cout << "请输入要查找的姓名" << endl;
    string name;
    cin >> name;
    int ret = isExist(abs, name);
    if (ret != -1) {
        cout << "姓名：" << abs->personArr[ret].name << "\t";
        cout << "性别：" << abs->personArr[ret].sex << "\t";
        cout << "年龄：" << abs->personArr[ret].age << "\t";
        cout << "电话：" << abs->personArr[ret].phone << "\t";
        cout << "地址：" << abs->personArr[ret].addr << endl;
    }else {
        cout << "查无此人" << endl;
    }
    system("pause");
    system("cls");
}

//5. 修改联系人信息
void modifyePerson(AddressBook * abs) {
    cout << "请输入要修改信息的联系人姓名" << endl;
    string name;
    cin >> name;
    int ret = isExist(abs, name);
    if (ret != -1) {
        cout << "姓名：" << abs->personArr[ret].name << "\t";
        cout << "性别：" << abs->personArr[ret].sex << "\t";
        cout << "年龄：" << abs->personArr[ret].age << "\t";
        cout << "电话：" << abs->personArr[ret].phone << "\t";
        cout << "地址：" << abs->personArr[ret].addr << endl;
        //只挑要改的某个信息修改
        cout << "请输入要修改的信息：" << endl;
        cout << "1-姓名， 2-性别， 3-年龄， 4-电话， 5-地址， 0-退出修改" << endl;
        int choice;
        cout << "请输入选项：" << endl;
        cin >> choice;
        if (choice == 0) {
            cout << "退出成功" << endl;
            return;
        }
        int bi_sex, age;
        string phone;
        switch (choice) {
            case 1:
                cout << "请输入姓名：" << endl;
                cin >> name;
                abs->personArr[ret].name = name;
                cout << "修改成功" << endl;
                break;
            case 2:
                while (true) {
                    cout << "请输入性别：" << endl;
                    cout << "1-男， 2-女" << endl;
                    cin >> bi_sex;
                    if (bi_sex == 1) {
                        abs->personArr[ret].sex = "男";
                        break;
                    } else if (bi_sex == 2) {
                        abs->personArr[ret].sex = "女";
                        break;
                    } else {
                        cout << "输入错误，请重新输入：" << endl;
                    }
                }
                cout << "修改成功" << endl;
                break;

            case 3:
                cout << "请输入年龄：" << endl;
                cin >> age;
                abs->personArr[ret].age = age;
                cout << "修改成功" << endl;
                break;
            case 4:
                cout << "请输入电话：" << endl;
                cin >> phone;
                abs->personArr[ret].phone = phone;
                cout << "修改成功" << endl;
                break;
            case 5:
                cout << "请输入地址：" << endl;
                string addr;
                cin >> addr;
                abs->personArr[ret].addr = addr;
                cout << "修改成功" << endl;
                break;
        }
        cout << "姓名：" << abs->personArr[ret].name << "\t";
        cout << "性别：" << abs->personArr[ret].sex << "\t";
        cout << "年龄：" << abs->personArr[ret].age << "\t";
        cout << "电话：" << abs->personArr[ret].phone << "\t";
        cout << "地址：" << abs->personArr[ret].addr << endl;


    }else {
        cout << "查无此人" << endl;
    }
    system("pause");
    system("cls");
}

//6. 清空联系人
void clearPerson(AddressBook * abs) {
    cout << "确定要清空所有联系人吗？(1-确认，0-取消)" << endl;
    int confirm = 0;
    cin >> confirm;

    if (confirm == 1) {
        abs->size = 0;  // 将size重置为0
        cout << "通讯录已清空" << endl;
    } else {
        cout << "已取消清空操作" << endl;
    }

    system("pause");
    system("cls");
}

void ShowMenu() {
    cout << "***********************" << endl;
    cout << "***** 1、添加联系人 *****" << endl;
    cout << "***** 2、显示联系人 *****" << endl;
    cout << "***** 3、删除联系人 *****" << endl;
    cout << "***** 4、查找联系人 *****" << endl;
    cout << "***** 5、修改联系人 *****" << endl;
    cout << "***** 6、清空联系人 *****" << endl;
    cout << "***** 0、退出通讯录 *****" << endl;
    cout << "***********************" << endl;
}

int main() {
    //创建通讯录结构体变量
    struct AddressBook abs;
    //初始化通讯录人数
    abs.size = 0;

    int select = 0;

    while (1) {
        //封装函数显示界面，void ShowMenu()
        //在main中调用ShowMenu()
        ShowMenu();

        cin >> select;

        switch (select) {
            case 1:  //1、添加联系人
                addPerson(& abs);  //利用地址传递，可以修饰实参
                break;
            case 2:  //2、显示联系人
                showPerson(& abs);
                break;
            case 3:  //3、删除联系人
                deletePerson(& abs);
            /*测试代码{
                cout << "请输入要删除的联系人" << endl;
                string name;
                cin >> name;
                if (isExist(&abs, name) == -1) {
                    cout << "查无此人" << endl;
                }else {
                    cout << "找到此人" << endl;
                }
                break;
            } //switch case 语句的一个case要是太长，会报错，需要用大括号把这个case括起来
            */
            case 4:  //4、查找联系人
                findPerson(& abs);
                break;
            case 5:  //5、修改联系人
                modifyePerson(& abs);
                break;
            case 6:  //6、清空联系人
                clearPerson(&  abs);
                break;
            case 0:  //0、退出通讯录
                cout << "欢迎下次使用" << endl;
                return 0;
                break;
            default:
                break;
        }
    }
    return 0;
}