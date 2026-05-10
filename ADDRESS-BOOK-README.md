# 1、main函数

```cpp
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
```



## 2、菜单功能



**功能描述：** 用户选择功能的界面

菜单界面效果如下图：

[![1544149559893](D:\Projects\Clion\address_book\image\Quicker_20260503_093221.png)](https://github.com/Blitzer207/C-Resource/blob/master/第2阶段实战-通讯录管理/通讯录管理系统讲义/assets/1544149559893.png)

**步骤：**

- 封装函数显示该界面 如 `void showMenu()`
- 在main函数中调用封装好的函数

**代码：**

```cpp
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
```



## 3、退出功能



功能描述：退出通讯录系统

思路：根据用户不同的选择，进入不同的功能，可以选择switch分支结构，将整个架构进行搭建

当用户选择0时候，执行退出，选择其他先不做操作，也不会退出程序





## 4、添加联系人

功能描述：

实现添加联系人功能，联系人上限为1000人，联系人信息包括（姓名、性别、年龄、联系电话、家庭住址）

添加联系人实现步骤：

- 设计联系人结构体
- 设计通讯录结构体
- main函数中创建通讯录
- 封装添加联系人函数
- 测试添加联系人功能

### 4.1 设计联系人结构体



联系人信息包括：姓名、性别、年龄、联系电话、家庭住址

设计如下：

```cpp
//设计联系人结构体
struct Person
{
    string name;
    string sex; //1-男， 2-女
    int age;
    string phone;
    string addr;
};
```



### 4.2 设计通讯录结构体



设计时候可以在通讯录结构体中，维护一个容量为1000的存放联系人的数组，并记录当前通讯录中联系人数量

设计如下

```cpp
#define MAX 1000 //最大人数

//设计通讯录结构体
struct AddressBook
{
    //联系人数组
    struct Person personArr[MAX_SIZE];

    //联系人数量
    int size;
};
```



### 4.3 main函数中创建通讯录



添加联系人函数封装好后，在main函数中创建一个通讯录变量，这个就是我们需要一直维护的通讯录

```
mian函数起始位置添加：

	//创建通讯录
	Addressbooks abs;
	//初始化通讯录中人数
	abs.m_Size = 0;
```



### 4.4 封装添加联系人函数



思路：添加联系人前先判断通讯录是否已满，如果满了就不再添加，未满情况将新联系人信息逐个加入到通讯录

添加联系人代码：

```cpp
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
        //用0/1来代替男女输入
        while (true) {
            cout << "请输入性别：" << endl;
            cout << "1-男， 2-女" << endl;
            cin >> bi_sex;
            if (bi_sex == 1) {
                abs->personArr[abs->size].sex = "男";
                break;//break跳出循环
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
```



### 4.5在main函数中使用功能

```cpp
case 1:  //1、添加联系人
                addPerson(& abs);  //利用地址传递，可以修饰实参
                break;
```





## 5、显示联系人



功能描述：显示通讯录中已有的联系人信息

显示联系人实现步骤：

- 封装显示联系人函数
- 测试显示联系人功能

### 5.1 封装显示联系人函数



思路：判断如果当前通讯录中没有人员，就提示记录为空，人数大于0，显示通讯录中信息

显示联系人代码：

```cpp
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


```



### 5.2 测试显示联系人功能



在switch case语句中，case 2 里添加

```cpp
case 2:  //2、显示联系人
                showPerson(& abs);
                break;
```





## 6、删除联系人



功能描述：按照姓名进行删除指定联系人

删除联系人实现步骤：

- 封装检测联系人是否存在
- 封装删除联系人函数
- 测试删除联系人功能

### 6.1 封装检测联系人是否存在



设计思路：

删除联系人前，我们需要先判断用户输入的联系人是否存在，如果存在删除，不存在提示用户没有要删除的联系人

因此我们可以把检测联系人是否存在封装成一个函数中，如果存在，返回联系人在通讯录中的位置，不存在返回-1

检测联系人是否存在代码：

```cpp
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
```



### 6.2 封装删除联系人函数



根据用户输入的联系人判断该通讯录中是否有此人

查找到进行删除，并提示删除成功

查不到提示查无此人。

```cpp
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
            //数据前移——————一个巧妙的“删除”方法！！！
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
```



### 6.3 main函数中调用删除联系人功能



在switch case 语句中，case3里添加：

```
case 3:  //删除联系人
	deletePerson(&abs);
	break;
```





## 7、查找联系人



功能描述：按照姓名查看指定联系人信息

查找联系人实现步骤

- 封装查找联系人函数
- 测试查找指定联系人

### 7.1 封装查找联系人函数



实现思路：判断用户指定的联系人是否存在，如果存在显示信息，不存在则提示查无此人。

查找联系人代码：

```cpp
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
```



### 7.2 main函数实现查找指定联系人



在switch case 语句中，case4里添加：

```
case 4:  //查找联系人
	findPerson(&abs);
	break;
```





## 8、修改联系人



功能描述：按照姓名重新修改指定联系人

修改联系人实现步骤

- 封装修改联系人函数
- 测试修改联系人功能

### 8.1 封装修改联系人函数



实现思路：查找用户输入的联系人，如果查找成功进行修改操作，查找失败提示查无此人

实现仅修改想修改的信息，不用把某个联系人的信息全部再输入一遍

修改联系人代码：

```cpp
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
```



### 8.2 测试修改联系人功能



在switch case 语句中，case 5里添加：

```
case 5:  //修改联系人
	modifyPerson(&abs);
	break;
```



## 9、清空联系人



功能描述：清空通讯录中所有信息

清空联系人实现步骤

- 封装清空联系人函数
- 测试清空联系人

### 9.1 封装清空联系人函数



实现思路： 将通讯录所有联系人信息清除掉，只要将通讯录记录的联系人数量置为0，做逻辑清空即可。

清空联系人代码：

```cpp
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
```



### 9.2 测试清空联系人



在switch case 语句中，case 6 里添加：

```
case 6:  //清空联系人
	cleanPerson(&abs);
	break;
```



**至此，通讯录管理系统完成！**



### 关键算法

#### 查找算法
- **线性搜索**：遍历数组查找匹配姓名的联系人
- **返回值**：找到返回索引，未找到返回 `-1`

#### 删除算法
- **数据前移**：删除后将后续元素依次向前移动一位
- **更新计数**：`size--` 减少联系人数量

### 指针传递

所有修改通讯录的函数都使用**指针传递**（`AddressBook*`），原因：
- 避免拷贝整个结构体（性能优化）
- 允许函数修改原始数据（值传递无法修改实参）

## 🎯 学习

通过本项目可以掌握：

1. **结构体设计与嵌套** - `Person` 和 `AddressBook` 的组合使用
2. **指针与引用** - 理解为什么需要指针传递
3. **数组操作** - 插入、删除、遍历、查找
4. **输入验证** - while 循环 + 条件判断确保数据合法性
5. **模块化编程** - 每个功能封装为独立函数
6. **菜单驱动设计** - switch-case 构建交互式界面
7. **系统命令调用** - `system("pause")` 和 `system("cls")` 的使用

## 🔧 代码规范

- 使用中文注释说明关键逻辑
- 函数命名采用驼峰式（如 `addPerson`, `showPerson`）
- 常量使用宏定义（`#define MAX_SIZE 1000`）

## ⚠️ 已知限制

1. **数据持久化**：程序关闭后数据丢失（未实现文件存储）
2. **内存固定分配**：使用静态数组而非动态扩容
3. **单文件架构**：所有代码在 `main.cpp` 中，未分模块
4. **不支持重名**：同名联系人只能存储第一个
5. **控制台界面**：仅支持命令行交互，无图形界面

## 🚧 未来改进方向

- [ ] 添加文件保存/加载功能（JSON 或二进制格式）
- [ ] 使用 `vector` 替代固定数组实现动态扩容
- [ ] 支持多关键字搜索（模糊匹配）
- [ ] 添加联系人分组/标签功能
- [ ] 拆分多文件架构（头文件 + 源文件）
- [ ] 添加单元测试
- [ ] 支持导出为 CSV/Excel 格式
- [ ] 图形界面版本（Qt 或 ImGui）





## 🙏 致谢

感谢黑马程序员！

---

**⭐ 如果这个项目对你的c++入门学习有帮助，请给个 Star 支持一下！**