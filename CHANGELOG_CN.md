# 改动日志 — 通讯录 v1.0 → v2.0

## 概述

从单文件 C++ 学习项目**重构为多层次企业级应用**，具备命令行、Qt 桌面端、Web 网页三种交互界面，支持数据持久化、模糊搜索、标签分组，并有完整的单元测试覆盖。

---

## 1. 拆分多文件架构

**改造前**：所有代码集中在单个 `main.cpp`（约 337 行）。

**改造后**：16 个源文件，分为 4 层：

```
src/
├── main.cpp                        # CLI 入口（仅 6 行）
├── model/
│   ├── person.h / person.cpp       # Person 结构体及标签操作
│   └── group.h                     # 分组/标签结构体
├── service/
│   ├── address_book_service.h/cpp  # 核心业务逻辑（增删改查、搜索、标签、持久化）
│   └── export_service（集成在 service 中）  # CSV 导出
├── ui/
│   ├── console_view.h/cpp          # 控制台界面（纯展示层）
└── utils/
    ├── validator.h/cpp             # 输入校验（姓名、电话、邮箱、年龄、地址）
    ├── fuzzy_search.h/cpp          # 大小写不敏感多关键字模糊搜索
    └── file_io.h/cpp               # JSON 持久化（手写解析器，无需外部库）

tests/
├── CMakeLists.txt                  # 测试构建配置
├── test_fuzzy_search.cpp           # 模糊搜索测试
├── test_service.cpp                # 业务逻辑测试
├── test_export.cpp                 # CSV 导出测试
└── test_file_io.cpp                # 文件读写测试

qt_gui/
├── main.cpp                        # Qt 程序入口
├── mainwindow.h/cpp                # 主窗口（表格、搜索、弹窗）
└── CMakeLists.txt                  # Qt 构建配置

web/
├── server.py                       # Flask REST API 后端
├── requirements.txt                # Python 依赖
├── templates/index.html            # 网页前端
└── static/
    ├── style.css                   # 样式表
    └── app.js                      # 前端逻辑
```

架构原则：**Model → Utils → Service → UI → main**，上层依赖下层，下层不感知上层。

---

## 2. `std::vector` 替代固定数组（动态扩容）

| 改造前 | 改造后 |
|---|---|
| `Person personArr[1000]` + `#define MAX_SIZE 1000` | `std::vector<Person> m_persons` |
| 联系人上限硬编码为 1000 | 无限制（动态分配内存） |
| 手动维护 `size` 变量 | `vector.size()` 自动维护 |

通讯录不再有"已满"的情况。

---

## 3. 多关键字模糊搜索

**改造前**：仅能通过姓名精确匹配（`isExist` 函数逐字符比较）。

**改造后**：在 `src/utils/fuzzy_search.cpp` 中实现三级模糊匹配：

| 函数 | 匹配逻辑 |
|---|---|
| `fuzzy::contains()` | 单个关键字大小写不敏感子串匹配 |
| `fuzzy::matchAll()` | 所有空格分隔的关键字**同时匹配**（AND 逻辑） |
| `fuzzy::matchAny()` | **任意**关键字匹配即可（OR 逻辑） |

搜索范围覆盖**所有字段**：姓名、电话、邮箱、地址、标签。

使用示例：
- `"张 138"` → 找到姓"张"且电话包含"138"的联系人
- `"北京 家人"` → 找到地址含"北京"且标签是"家人"的联系人

---

## 4. 联系人标签/分组

每个联系人现在支持**多个标签**进行分类管理：

- `person.tags` — `std::vector<std::string>` 字段
- `Person::addTag()` / `removeTag()` / `hasTag()` — 标签操作
- `AddressBookService::addTagToPerson()` / `removeTagFromPerson()` — 业务层标签管理
- `AddressBookService::findByTag(tag)` — 按标签筛选
- `AddressBookService::allTags()` — 枚举所有标签
- 三种界面（CLI / Qt / Web）均支持标签管理

---

## 5. 单元测试

4 个测试套件，使用 **Google Test** 框架，通过 CMake `FetchContent` 自动下载：

| 测试文件 | 覆盖内容 |
|---|---|
| `tests/test_fuzzy_search.cpp` | 大小写不敏感搜索、多关键字匹配、中文文本、跨字段搜索 |
| `tests/test_service.cpp` | 增删改查、重复检测、标签 CRUD、模糊搜索 |
| `tests/test_export.cpp` | CSV 导出内容、空数据导出、特殊字符转义 |
| `tests/test_file_io.cpp` | JSON 保存/加载往返、空文件处理、不存在的文件、转义字符 |

编译并运行：

```bash
cmake -B cmake-build-debug -DBUILD_TESTS=ON
cmake --build cmake-build-debug
cd cmake-build-debug && ctest
```

测试结果：**4/4 全部通过**。

---

## 6. CSV 导出

**改造前**：不支持任何导出功能。

**改造后**：`AddressBookService::exportToCSV()` 实现完整 CSV 导出：

- UTF-8 BOM 头（确保 Excel 正确识别中文）
- 正确的 CSV 转义（引号、逗号、换行符）
- 标签以分号分隔序列化
- 三种界面均可导出：
  - CLI：选择菜单选项 7
  - Qt：点击"Export CSV"按钮，选择保存路径
  - Web：点击"导出 CSV"按钮，浏览器自动下载（`GET /api/export/csv`）

---

## 7. Qt 桌面版（图形界面）

位于 `qt_gui/` — 完整的 Qt6 桌面应用：

| 功能 | 实现方式 |
|---|---|
| 联系人表格 | `QTableWidget`，支持排序、交替行颜色 |
| 添加/编辑 | 模态对话框 + 表单布局 |
| 删除 | 行选择 + 确认对话框 |
| 搜索 | 实时模糊搜索 + 标签下拉过滤 |
| 标签过滤 | `QComboBox` 动态列出所有标签 |
| CSV 导出 | 文件保存对话框 |
| 双击编辑 | 双击表格行直接编辑 |

构建方式：`cd qt_gui && cmake -B build && cmake --build build`（需要 Qt6）

---

## 8. Web 网页版

位于 `web/` — 完整的 REST API + 单页应用（SPA）前端：

### 后端 (`web/server.py`)
- **Flask** 框架 REST API
- `GET /api/contacts` — 列表查询（支持搜索和标签筛选参数）
- `POST /api/contacts` — 添加（含校验）
- `GET /api/contacts/<name>` — 获取单个
- `PUT /api/contacts/<name>` — 修改
- `DELETE /api/contacts/<name>` — 删除
- `GET /api/tags` — 列出所有标签
- `GET /api/export/csv` — 下载 CSV 文件
- 已启用 CORS，支持跨域访问

### 前端
- 现代化响应式 SPA（HTML5 + CSS3 + 原生 JS）
- 实时搜索（输入即过滤，支持多关键字）
- 标签下拉筛选
- 添加/编辑模态弹窗
- Toast 提示消息
- 动画效果（弹窗滑入、提示淡入）
- 移动端适配
- 无前端框架依赖，纯原生 JavaScript

启动方式：

```bash
cd web
pip install -r requirements.txt
python server.py
# 浏览器打开 http://localhost:5000
```

---

## 9. 其他改进

### 现代 C++ 实践
- `constexpr` 替代 `#define` 宏定义
- `enum class Gender` 替代数字代号（1/2）
- 全局删除 `using namespace std`
- `std::optional<Person*>` 替代 "返回 -1 表示未找到"
- 用 Win32 Console API + ANSI 转义序列替代 `system("pause")` / `system("cls")`，实现跨平台

### 数据持久化
- JSON 格式存储到 `address_book.json`
- 每次增删改操作后自动保存
- 启动时自动加载
- 手写 JSON 解析器，无需外部库依赖

### 输入校验 (`src/utils/validator.cpp`)
- 姓名：1-50 字符，允许字母数字空格及 UTF-8 多字节字符
- 电话：5-20 字符，数字 + 破折号 + 空格 + 前导 `+`
- 邮箱：标准正则校验
- 年龄：1-149 范围
- 地址：非空，最长 200 字符

### 新增邮箱字段
- Person 结构体新增 `email` 字段（v1.0 中没有）

### 构建系统
- CMake 分层库：`ab_model`、`ab_utils`、`ab_service`、`ab_ui`
- C++20 标准
- Google Test 通过 `FetchContent` 自动下载
- Qt 构建独立配置，启用 `AUTOMOC`

---

## 版本对比一览

| 指标 | v1.0 | v2.0 |
|---|---|---|
| 源文件数 | 1 | 16 个 C++ + 5 个 Web 文件 |
| C++ 代码量 | ~337 行 | ~1500+ 行 |
| 构建目标 | 1 个 exe | 1 个主程序 + 3 个静态库 + 4 个测试 + Qt 应用 |
| 数据结构 | 固定数组 [1000] | `std::vector`（动态） |
| 持久化 | 无 | JSON 自动保存/加载 |
| 搜索 | 姓名精确匹配 | 多关键字跨字段模糊搜索 |
| 标签 | 无 | 标签增删查筛选 |
| 单元测试 | 0 | 4 套测试（GTest），100% 通过 |
| 用户界面 | 仅控制台 | 控制台 + Qt 桌面 + Web 网页 |
| 导出 | 无 | CSV（含 Excel BOM） |
| 数据校验 | 基础 | 姓名/电话/邮箱/年龄/地址完整校验 |
