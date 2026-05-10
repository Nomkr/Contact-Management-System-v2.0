# Contact Management System-v2.0
第一次使用vibe coding来完成项目，拿之前手敲的通讯录小项目来练手
# 通讯录管理系统 v2.0

> C++20 企业级通讯录管理系统，支持 CLI / Qt 桌面 / Web 网页三种交互方式。

[![C++ Standard](https://img.shields.io/badge/C%2B%2B-20-blue.svg)](https://en.cppreference.com/w/cpp/20)
[![CMake](https://img.shields.io/badge/CMake-3.21%2B-green.svg)](https://cmake.org/)
[![Qt](https://img.shields.io/badge/Qt-6.x-brightgreen.svg)](https://www.qt.io/)
[![Flask](https://img.shields.io/badge/Flask-3.x-lightgrey.svg)](https://flask.palletsprojects.com/)
[![Tests](https://img.shields.io/badge/tests-4%2F4%20passed-success.svg)](tests/)

---

## 项目简介

从单文件 C++ 学习项目重构为**分层架构的企业级应用**，具备：

- **数据持久化** — JSON 文件自动保存/加载
- **模糊搜索** — 多关键字跨字段大小写不敏感匹配
- **标签分组** — 联系人支持多标签分类管理
- **CSV 导出** — 含 UTF-8 BOM，Excel 直接打开
- **三种界面** — 命令行 / Qt 桌面端 / Web 网页端
- **单元测试** — 4 套 GTest 测试，100% 通过
- **现代 C++** — C++20 标准，`std::vector` 动态扩容，无硬编码上限

### 界面预览

**网页版** — 推荐日常使用：

![Web界面](https://via.placeholder.com/800x450/4a90d9/ffffff?text=Address+Book+Web+Interface)

**Qt 桌面版**：

![Qt界面](https://via.placeholder.com/800x450/27ae60/ffffff?text=Address+Book+Qt+Interface)

---

## 项目结构

```
address_book/
├── src/
│   ├── main.cpp                        # CLI 入口
│   ├── model/                          # 数据模型层
│   │   ├── person.h / person.cpp       # 联系人结构体 + 标签操作
│   │   └── group.h                     # 分组结构体
│   ├── service/                        # 业务逻辑层
│   │   └── address_book_service.h/cpp  # CRUD / 搜索 / 标签 / 导出
│   ├── ui/                            # 表示层
│   │   └── console_view.h/cpp         # 控制台界面
│   └── utils/                         # 工具层
│       ├── validator.h/cpp            # 输入校验
│       ├── fuzzy_search.h/cpp         # 模糊搜索算法
│       └── file_io.h/cpp             # JSON 文件读写
├── tests/                             # 单元测试
│   ├── test_fuzzy_search.cpp
│   ├── test_service.cpp
│   ├── test_export.cpp
│   └── test_file_io.cpp
├── qt_gui/                            # Qt6 桌面应用
│   ├── main.cpp
│   └── mainwindow.h/cpp
├── web/                               # Web 网页版
│   ├── server.py                      # Flask REST API
│   ├── requirements.txt
│   ├── templates/index.html
│   └── static/
│       ├── style.css
│       └── app.js
├── CMakeLists.txt                     # 构建配置
├── USER_GUIDE_CN.md                   # 中文使用教程
├── CHANGELOG_CN.md                    # 中文改动日志
└── README.md
```

---

## 快速开始

### 环境要求

| 版本 | 最低要求 |
|---|---|
| 编译器 | GCC 11+ / Clang 14+ / MSVC 2022+ |
| CMake | 3.21+ |
| Python（仅 Web 版） | 3.10+ |
| Qt（仅桌面版） | 6.x（Widgets 模块） |

### 命令行版（CLI）

```bash
# 配置
cmake -B cmake-build-debug \
  -DCMAKE_CXX_COMPILER=g++ \
  -DCMAKE_C_COMPILER=gcc

# 编译
cmake --build cmake-build-debug

# 运行
cd cmake-build-debug && ./address_book
```

### 网页版（推荐）

```bash
cd web
pip install -r requirements.txt
python server.py
# 浏览器打开 → http://localhost:5000
```

### Qt 桌面版

```bash
cd qt_gui
cmake -B build
cmake --build build
./build/address_book_qt
```

### 运行测试

```bash
cmake -B cmake-build-debug -DBUILD_TESTS=ON
cmake --build cmake-build-debug
cd cmake-build-debug && ctest --output-on-failure
```

---

## 功能清单

| 功能 | CLI | Qt | Web |
|---|---|---|---|
| 添加联系人 | ✅ | ✅ | ✅ |
| 显示所有联系人 | ✅ | ✅ | ✅ |
| 删除联系人 | ✅ | ✅ | ✅ |
| 模糊搜索（多关键字） | ✅ | ✅ | ✅ |
| 修改联系人 | ✅ | ✅ | ✅ |
| 清空通讯录 | ✅ | ✅ | ✅ |
| 标签管理（分组/筛选） | ✅ | ✅ | ✅ |
| CSV 导出 | ✅ | ✅ | ✅ |
| JSON 持久化 | ✅ | ✅ | ✅ |
| 输入校验 | ✅ | ✅ | ✅ |

---

## 数据格式

联系人数据以 JSON 格式存储在 `address_book.json`：

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
  }
]
```

`gender`: `1` = 男，`2` = 女

---

## 搜索语法

支持**多关键字模糊搜索**（空格分隔），匹配范围包括姓名、电话、邮箱、地址、标签：

```
张 138        → 姓"张"且电话含"138"
北京 家人     → 地址含"北京"且标签为"家人"
```

---

## 从 v1.0 升级的主要改动

详见 [CHANGELOG_CN.md](CHANGELOG_CN.md)

- 单文件 → 16 文件分层架构
- 固定数组 `[1000]` → `std::vector` 动态扩容
- 精确匹配 → 多字段模糊搜索
- 新增标签分组功能
- 新增 JSON 数据持久化
- 新增 CSV 导出
- 新增 Qt 桌面版 + Web 网页版
- 新增 4 套单元测试
- 无持久化 → JSON 自动保存

---

## 使用教程

详细中文教程见 [USER_GUIDE_CN.md](USER_GUIDE_CN.md)

---

## 开源协议

MIT License
