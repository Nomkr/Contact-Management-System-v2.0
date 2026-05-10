# 通讯录管理系统 v2.0 — 使用教程

## 目录

1. [项目简介](#项目简介)
2. [命令行版本 (CLI)](#命令行版本-cli)
3. [网页版界面](#网页版界面)
4. [Qt 桌面版](#qt-桌面版)
5. [单元测试](#单元测试)
6. [数据文件说明](#数据文件说明)
7. [常见问题](#常见问题)

---

## 项目简介

通讯录管理系统 v2.0 是一个企业级 C++ 项目，提供三种交互方式：

| 版本 | 适用场景 | 技术栈 |
|---|---|---|
| 命令行版 (CLI) | 开发调试、服务器环境 | C++20 标准控制台程序 |
| 网页版 (Web) | 日常使用、多设备访问 | Python Flask + HTML/CSS/JS |
| 桌面版 (Qt) | Windows/macOS/Linux 桌面 | C++ Qt6 Widgets |

所有版本共享同一份数据文件 `address_book.json`，数据互通。

---

## 命令行版本 (CLI)

### 编译

```bash
cd address_book
cmake -B cmake-build-debug
cmake --build cmake-build-debug
```

### 运行

```bash
./cmake-build-debug/address_book.exe
```

### 功能菜单

```
============================================
        Address Book Management System
============================================
  1. Add Contact         添加联系人
  2. Show All Contacts   显示所有联系人
  3. Delete Contact      删除联系人
  4. Search Contacts     模糊搜索联系人（支持多关键字）
  5. Modify Contact      修改联系人
  6. Clear All Contacts  清空所有联系人
  7. Export to CSV       导出为 CSV 文件
  8. Manage Tags         管理标签
  0. Save & Exit         保存并退出
============================================
```

### 各功能说明

#### 1. 添加联系人
输入姓名、性别（1-男/2-女）、年龄、电话、邮箱、地址，以及标签（逗号分隔，如 `家人,同事`）。

#### 4. 模糊搜索
支持**多关键字联合搜索**，关键字之间用空格分隔，系统会在姓名、电话、邮箱、地址、标签等所有字段中匹配。

示例：
- 输入 `张 138` → 找到姓"张"且电话包含"138"的联系人
- 输入 `北京 家人` → 找到地址含"北京"且标签为"家人"的联系人

#### 7. 导出 CSV
将通讯录导出为 CSV 文件（带 UTF-8 BOM，Excel 可直接打开），默认文件名为 `address_book_export.csv`。

#### 8. 标签管理
- **按标签筛选**：查看某个标签下的所有联系人
- **添加标签**：给指定联系人添加标签
- **删除标签**：移除某个联系人的标签

---

## 网页版界面

网页版是本项目**推荐日常使用的方式**，界面现代化，操作方便。

### 第一步：安装 Python 依赖

确保已安装 Python 3.10+，然后：

```bash
cd web
pip install -r requirements.txt
```

### 第二步：启动后端服务器

```bash
cd web
python server.py
```

启动后会显示：

```
Address Book Web Server starting at http://localhost:5000
 * Running on http://0.0.0.0:5000
```

### 第三步：打开浏览器

在浏览器地址栏输入：

```
http://localhost:5000
```

### 网页版功能说明

打开后会看到一个完整的通讯录管理界面：

```
┌─────────────────────────────────────────────────┐
│  Address Book Manager          [3 contacts]     │
├─────────────────────────────────────────────────┤
│  [🔍 搜索联系人...          ]  [所有标签 ▾]    │
│  [+ 添加联系人]  [导出 CSV]                     │
├─────────────────────────────────────────────────┤
│  姓名  │性别│年龄│  电话  │  邮箱  │地址│标签  │
│  ──────┼────┼────┼────────┼────────┼────┼──────│
│  张三  │ 男 │ 28 │138...  │z@m.com │北京│家人   │
│  李四  │ 女 │ 22 │139...  │l@m.com │上海│同事   │
├─────────────────────────────────────────────────┤
│                               [编辑] [删除]     │
└─────────────────────────────────────────────────┘
```

#### 操作说明

| 操作 | 方式 |
|---|---|
| **搜索** | 在搜索框输入关键字，实时过滤，支持多关键字（空格分隔） |
| **标签筛选** | 点击"所有标签"下拉框选择特定标签 |
| **添加** | 点击"+ 添加联系人"按钮，弹出表单填写后保存 |
| **编辑** | 点击行尾的"编辑"按钮或**双击表格行** |
| **删除** | 点击"删除"按钮，确认后删除 |
| **导出** | 点击"导出 CSV"，浏览器自动下载 |
| **关闭弹窗** | 点击遮罩区域或按 `Esc` 键 |

#### 局域网访问

如果想在**手机或其他电脑**上访问，启动时绑定所有网卡后，用本机 IP 访问：

```
http://你的IP地址:5000
```

例如：`http://192.168.1.100:5000`

---

## Qt 桌面版

Qt 版本提供原生桌面体验（需要安装 Qt6）。

### 编译

```bash
cd qt_gui
cmake -B build
cmake --build build
```

### 运行

```bash
./build/address_book_qt.exe
```

### 界面功能

| 功能 | 操作方式 |
|---|---|
| 查看联系人 | 主表格显示所有字段，支持列排序 |
| 添加联系人 | 点击"Add Contact"按钮，弹出表单 |
| 编辑联系人 | 选中行后点击"Edit"，或双击行 |
| 删除联系人 | 选中行后点击"Delete"，确认后删除 |
| 模糊搜索 | 搜索框实时过滤，支持多关键字 |
| 标签筛选 | 下拉框选择标签过滤 |
| 导出 CSV | 点击"Export CSV"，选择保存路径 |

---

## 单元测试

项目包含 4 个测试套件，使用 Google Test 框架。

### 编译并运行

```bash
cmake -B cmake-build-debug -DBUILD_TESTS=ON
cmake --build cmake-build-debug
cd cmake-build-debug && ctest --output-on-failure
```

### 预期输出

```
Test project address_book/cmake-build-debug
    Start 1: test_fuzzy_search
1/4 Test #1: test_fuzzy_search ................   Passed
    Start 2: test_service
2/4 Test #2: test_service .....................   Passed
    Start 3: test_export
3/4 Test #3: test_export ......................   Passed
    Start 4: test_file_io
4/4 Test #4: test_file_io .....................   Passed

100% tests passed, 0 tests failed out of 4
```

### 测试覆盖范围

| 测试文件 | 覆盖内容 |
|---|---|
| `test_fuzzy_search.cpp` | 大小写不敏感搜索、多关键字匹配、中文搜索、跨字段搜索 |
| `test_service.cpp` | 增删改查、重复姓名检测、标签操作、模糊搜索 |
| `test_export.cpp` | CSV 导出、空数据导出、特殊字符转义 |
| `test_file_io.cpp` | JSON 保存/加载、空文件、特殊字符、文件不存在 |

---

## 数据文件说明

所有数据存储在 `address_book.json` 文件中（位于项目根目录），格式如下：

```json
[
  {
    "name": "张三",
    "gender": 1,
    "age": 28,
    "phone": "13800138000",
    "email": "zhangsan@example.com",
    "address": "北京市朝阳区",
    "tags": ["家人", "同事"]
  },
  {
    "name": "李四",
    "gender": 2,
    "age": 22,
    "phone": "13900139000",
    "email": "lisi@example.com",
    "address": "上海市浦东新区",
    "tags": ["朋友"]
  }
]
```

字段说明：

| 字段 | 类型 | 说明 |
|---|---|---|
| `name` | string | 姓名（必填，不可重复） |
| `gender` | int | 性别，1=男，2=女 |
| `age` | int | 年龄，范围为 1-149 |
| `phone` | string | 电话号码 |
| `email` | string | 邮箱地址 |
| `address` | string | 地址 |
| `tags` | array | 标签列表，如 `["家人", "同事"]` |

---

## 常见问题

### Q: 网页版启动报错 `ModuleNotFoundError: No module named 'flask'`
```bash
pip install -r requirements.txt
```

### Q: 网页版启动后浏览器打不开
检查控制台输出是否正确，确认访问的是 `http://localhost:5000`（注意是 http 不是 https）。

### Q: 命令行版本编译报错
确保使用 CMake 3.21+ 和支持 C++20 的编译器（GCC 11+ / Clang 14+ / MSVC 2022+）。

### Q: Qt 版本无法编译
需要安装 Qt6（Widgets 模块）。可以从 [qt.io](https://www.qt.io/download) 下载，或通过包管理器安装：
```bash
# MSYS2
pacman -S mingw-w64-x86_64-qt6

# macOS
brew install qt@6

# Ubuntu
sudo apt install qt6-base-dev
```

### Q: 如何在手机上访问网页版？
1. 确保手机和电脑在同一个局域网
2. 查看电脑的 IP 地址（Windows 上用 `ipconfig`，macOS/Linux 上用 `ifconfig`）
3. 手机浏览器输入 `http://电脑IP:5000`

### Q: 三个版本的数据互通吗？
互通。CLI、Qt 桌面版、网页版都读写同一份 `address_book.json` 文件。
