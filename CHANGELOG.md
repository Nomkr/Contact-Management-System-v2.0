# Changelog — Address Book v1.0 → v2.0

## Overview

Complete architectural rewrite from a single-file C++ learning project to a **multi-layered enterprise-grade application** with CLI, Qt GUI, and Web interfaces, persistent storage, and unit tests.

---

## 1. Multi-File Architecture (拆分多文件架构)

**Before**: All code in a single `main.cpp` (~337 lines).

**After**: 16 source files across 4 layers:

```
src/
├── main.cpp                        # CLI entry point (6 lines)
├── model/
│   ├── person.h / person.cpp       # Person struct with tag operations
│   └── group.h                     # Group/Tag struct
├── service/
│   ├── address_book_service.h/cpp  # Core business logic (CRUD, search, tags, persistence)
│   └── export_service integrated   # CSV export inside service
├── ui/
│   ├── console_view.h/cpp          # Console UI (presentation only)
└── utils/
    ├── validator.h/cpp             # Input validation (name, phone, email, age, address)
    ├── fuzzy_search.h/cpp          # Case-insensitive multi-keyword fuzzy search
    └── file_io.h/cpp               # JSON persistence (hand-written, no external deps)
```

Separation of concerns: **Model → Utils → Service → UI → main**

---

## 2. `std::vector` Replaces Fixed Array (动态扩容)

| Before | After |
|---|---|
| `Person personArr[1000]` with `MAX_SIZE = 1000` | `std::vector<Person> m_persons` |
| Contact limit: 1000 (hard cap) | No limit (dynamic allocation) |
| Manual `size` tracking | `vector.size()` |

No more "address book full" errors.

---

## 3. Multi-Keyword Fuzzy Search (多关键字模糊匹配)

**Before**: Exact name match only via `isExist()`.

**After**: Three-tier fuzzy matching in `src/utils/fuzzy_search.cpp`:

- `fuzzy::contains()` — case-insensitive substring match
- `fuzzy::matchAll()` — **all** space-separated keywords must match (AND logic)
- `fuzzy::matchAny()` — **any** keyword matches (OR logic)

Searches across **all fields**: name, phone, email, address, and tags.

Examples:
- `"zhang 138"` → finds Zhang Wei with phone 13800138000
- `"beijing family"` → finds contacts in Beijing with "family" tag

---

## 4. Contact Tags / Groups (分组/标签功能)

Each contact now supports **multiple tags** for categorization:

- `person.tags` — `std::vector<std::string>` field on Person
- `Person::addTag()` / `removeTag()` / `hasTag()`
- `AddressBookService::addTagToPerson()` / `removeTagFromPerson()`
- `AddressBookService::findByTag(tag)` — filter by tag
- `AddressBookService::allTags()` — enumerate all tags in use
- Tag management UI in console, Qt, and web interfaces

---

## 5. Unit Tests (单元测试)

4 test suites using **Google Test (GTest)**, auto-downloaded via CMake `FetchContent`:

| Test file | Coverage |
|---|---|
| `tests/test_fuzzy_search.cpp` | Case-insensitive search, multi-keyword, Chinese text |
| `tests/test_service.cpp` | Add/delete/modify/find/clear, duplicates, tag CRUD, fuzzy search |
| `tests/test_export.cpp` | CSV export, empty export, special characters |
| `tests/test_file_io.cpp` | JSON save/load round-trip, empty save, non-existent file, escape chars |

Build & run: `cmake -DBUILD_TESTS=ON .. && cmake --build . && ctest`

---

## 6. CSV Export (导出为 CSV)

**Before**: No export capability.

**After**: Full CSV export in `AddressBookService::exportToCSV()`:

- UTF-8 BOM for Excel compatibility
- Proper CSV escaping (quotes, commas, newlines in fields)
- Tags serialized as semicolon-separated string
- Available in: CLI (`case 7`), Qt GUI (Export button), Web (download endpoint)
- Web API: `GET /api/export/csv` — one-click browser download

---

## 7. Qt GUI (图形界面 Qt)

Located in `qt_gui/` — full-featured Qt6 desktop application:

| Feature | Implementation |
|---|---|
| Contact table | `QTableWidget` with sortable columns, alternating row colors |
| Add/Edit | Modal dialog with form layout |
| Delete | Row selection + confirmation dialog |
| Search | Real-time fuzzy search with tag filter combo |
| Tag filter | `QComboBox` dropdown with all tags |
| CSV Export | File save dialog |
| Double-click edit | Edit on double-click |

Build: `cd qt_gui && cmake -B build && cmake --build build` (requires Qt6)

---

## 8. Web Interface (网页显示)

Located in `web/` — complete REST API + SPA frontend:

### Backend (`web/server.py`)
- **Flask** REST API server
- `GET /api/contacts` — list with search & tag filter
- `POST /api/contacts` — add (with validation)
- `GET /api/contacts/<name>` — get single
- `PUT /api/contacts/<name>` — update
- `DELETE /api/contacts/<name>` — delete
- `GET /api/tags` — list all tags
- `GET /api/export/csv` — download CSV
- CORS enabled for external access

### Frontend
- Modern responsive SPA (HTML5 + CSS3 + Vanilla JS)
- Real-time search with debounced input
- Tag filter dropdown
- Modal dialogs for Add/Edit
- Toast notifications
- Animated UI (slide-up modals, fade-in toasts)
- Mobile-responsive design
- No JS framework dependencies — pure vanilla JS

Run: `cd web && pip install -r requirements.txt && python server.py`
Open: `http://localhost:5000`

---

## 9. Additional Improvements

### Modern C++ Practices
- `constexpr` instead of `#define` macros
- `enum class Gender` instead of magic numbers (1/2)
- No more `using namespace std` at global scope
- `std::optional<Person*>` for "not found" semantics
- Cross-platform `system("pause")` / `system("cls")` replacement using Win32 Console API + ANSI escapes

### Data Persistence
- JSON file storage in `address_book.json`
- Auto-save after each mutation
- Auto-load on startup
- Custom JSON parser (no external library needed)

### Input Validation (`src/utils/validator.cpp`)
- Name: 1-50 chars, alphanumeric + spaces + UTF-8
- Phone: 5-20 chars, digits + dashes + spaces + leading `+`
- Email: standard regex validation
- Age: 1-149 range
- Address: non-empty, max 200 chars

### Email Field
- Added `email` field to Person (not present in v1.0)

### Build System
- CMake with proper library targets: `ab_model`, `ab_utils`, `ab_service`, `ab_ui`
- C++20 standard
- Google Test via `FetchContent` (auto-download)
- Separate Qt build with `AUTOMOC` enabled

---

## File Comparison

| Metric | v1.0 | v2.0 |
|---|---|---|
| Source files | 1 | 16 C++ + 5 web files |
| Lines of C++ code | ~337 | ~1500+ |
| Build targets | 1 exe | 1 exe + 3 static libs + 4 test exes + Qt app |
| Data structure | Fixed array [1000] | `std::vector` (dynamic) |
| Persistence | None | JSON auto-save/load |
| Search | Exact name match | Multi-keyword fuzzy across all fields |
| Tags | None | Tag CRUD + filter |
| Tests | 0 | 4 test suites (GTest) |
| Interfaces | CLI only | CLI + Qt GUI + Web |
| Export | None | CSV (with Excel BOM) |

---

## Build Instructions

### CLI Version
```bash
cd address_book
cmake -B cmake-build-debug
cmake --build cmake-build-debug
```

### Tests
```bash
cmake -B cmake-build-debug -DBUILD_TESTS=ON
cmake --build cmake-build-debug
cd cmake-build-debug && ctest
```

### Qt GUI (requires Qt6)
```bash
cd qt_gui
cmake -B build
cmake --build build
```

### Web Interface (requires Python 3.10+)
```bash
cd web
pip install -r requirements.txt
python server.py
# Open http://localhost:5000
```
