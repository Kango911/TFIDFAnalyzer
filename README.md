```markdown
# TF-IDF Text Analyzer

## Описание

Программа для анализа текстовых документов с использованием модели TF-IDF (Term Frequency - Inverse Document Frequency). Реализована на C++ с использованием STL-контейнеров и алгоритмов.

## Функциональность

- Загрузка документов из файлов
- Предобработка текста (приведение к нижнему регистру, удаление пунктуации)
- Вычисление TF, IDF и TF-IDF для всех слов
- Обработка запросов четырех типов

## Типы запросов

### 1. WORD <word>
Выводит статистику по слову во всех документах

**Пример:**
```
WORD learning
```

**Вывод:**
```
Word: learning
Documents total: 3
Documents with word: 2
IDF: 0.4055
Appears in:
- data/doc1.txt
- data/doc3.txt
```

### 2. WORD_IN_DOC <word> <document>
Выводит статистику слова в конкретном документе

**Пример:**
```
WORD_IN_DOC machine data/doc1.txt
```

**Вывод:**
```
Word: machine
Document: data/doc1.txt
Count: 3
TF: 0.0625
TF-IDF: 0.0253
```

### 3. DOC <document>
Выводит статистику по документу (топ-5 слов по TF-IDF)

**Пример:**
```
DOC data/doc1.txt
```

**Вывод:**
```
Document: data/doc1.txt
Total words: 48
Unique words: 28
Top words:
1. learning (0.0937)
2. machine (0.0625)
3. data (0.0625)
4. models (0.0417)
5. artificial (0.0208)
```

### 4. QUERY <word1> <word2> ...
Поиск документов, релевантных запросу

**Пример:**
```
QUERY machine learning
```

**Вывод:**
```
Query: machine learning
Results:
1. data/doc1.txt (0.1250)
2. data/doc3.txt (0.0625)
3. data/doc2.txt (0.0000)
```

## Структура проекта

```
TFIDFAnalyzer/
├── CMakeLists.txt              # Конфигурация сборки
├── documents.txt               # Список файлов документов
├── data/                       # Директория с документами
│   ├── doc1.txt
│   ├── doc2.txt
│   └── doc3.txt
├── src/
│   ├── main.cpp                # Точка входа
│   ├── TextProcessor.h         # Заголовок обработчика текста
│   ├── TextProcessor.cpp       # Реализация обработчика текста
│   ├── TFIDFCalculator.h       # Заголовок калькулятора TF-IDF
│   ├── TFIDFCalculator.cpp     # Реализация калькулятора TF-IDF
│   ├── QueryHandler.h          # Заголовок обработчика запросов
│   └── QueryHandler.cpp        # Реализация обработчика запросов
└── README.md                   # Документация
```

## Требования

- CMake 3.20 или выше
- C++17 совместимый компилятор (GCC, Clang, MSVC)

## Сборка и запуск

### Linux / macOS

```bash
# Клонирование проекта (или переход в директорию проекта)
cd TFIDFAnalyzer

# Создание директории для сборки
mkdir build
cd build

# Генерация файлов сборки
cmake ..

# Компиляция
cmake --build .

# Запуск
./TFIDFAnalyzer
```

### Windows (CLion)

1. Открыть проект в CLion
2. Настроить CMake (автоматически)
3. Нажать Build → Build Project
4. Запустить исполняемый файл

### Windows (Visual Studio)

```bash
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022"
cmake --build . --config Release
cd Release
TFIDFAnalyzer.exe
```

## Подготовка данных

1. Создайте файл `documents.txt` в корневой директории
2. В каждой строке укажите путь к файлу документа
3. Создайте текстовые файлы с документами

**Пример documents.txt:**
```
data/doc1.txt
data/doc2.txt
data/doc3.txt
```

## Пример полной сессии работы

```
TF-IDF Text Analyzer
====================
Loading 3 documents...
Documents loaded successfully!
Total unique words: 42

Available commands:
  WORD <word>
  WORD_IN_DOC <word> <document>
  DOC <document>
  QUERY <word1> <word2> ...
  EXIT

> WORD learning
Word: learning
Documents total: 3
Documents with word: 2
IDF: 0.4055
Appears in:
 - data/doc1.txt
 - data/doc3.txt

> WORD_IN_DOC machine data/doc1.txt
Word: machine
Document: data/doc1.txt
Count: 3
TF: 0.0625
TF-IDF: 0.0253

> DOC data/doc1.txt
Document: data/doc1.txt
Total words: 48
Unique words: 28
Top words:
 1. learning (0.0937)
 2. machine (0.0625)
 3. data (0.0625)
 4. models (0.0417)
 5. artificial (0.0208)

> QUERY natural language processing
Query: natural language processing
Results:
 1. data/doc3.txt (0.1875)
 2. data/doc1.txt (0.0000)
 3. data/doc2.txt (0.0000)

> EXIT
```

## Особенности реализации

### Использование STL
- **Контейнеры**: `std::vector`, `std::unordered_map`, `std::set`
- **Алгоритмы**: `std::sort`, `std::transform`, `std::copy_if`, `std::find_if`, `std::for_each`, `std::accumulate`, `std::count_if`
- **Лямбда-функции**: все предикаты и операции реализованы через лямбда-выражения

### Отсутствие явных циклов
Все итерационные процессы заменены алгоритмами STL:
- Нет `for` для перебора коллекций
- Нет `while` для обработки последовательностей
- Только алгоритмы высшего порядка

### Обработка текста
- Приведение всех символов к нижнему регистру
- Удаление знаков препинания и специальных символов
- Токенизация по пробельным символам

### Обработка ошибок
- Проверка существования файлов
- Валидация формата запросов
- Корректная обработка неизвестных команд
- Сообщения об ошибках при некорректных запросах

## Теоретическая справка

### TF (Term Frequency)
Частота слова в документе:
```
TF(w, d) = count(w, d) / |d|
```
где `count(w, d)` — количество вхождений слова w в документ d, `|d|` — общее количество слов в документе.

### IDF (Inverse Document Frequency)
Обратная частота документа:
```
IDF(w) = log(N / df(w))
```
где `N` — общее количество документов, `df(w)` — количество документов, содержащих слово w.

### TF-IDF
Итоговая метрика важности слова:
```
TF-IDF(w, d) = TF(w, d) × IDF(w)
```

Высокое значение TF-IDF получают слова, которые часто встречаются в документе, но редко — в других документах.

## Возможные проблемы и решения

### Проблема: Файл documents.txt не найден
**Решение:** Убедитесь, что файл `documents.txt` находится в той же директории, что и исполняемый файл.

### Проблема: Документы не загружаются
**Решение:** Проверьте пути к файлам в `documents.txt`. Пути должны быть корректными относительно рабочей директории программы.

### Проблема: Некорректные результаты поиска
**Решение:** Убедитесь, что тексты документов содержат слова на одном языке. TF-IDF чувствителен к стеммингу (отсутствует в данной реализации).

## Расширение функциональности

Возможные улучшения:
- Добавление стемминга (приведение слов к нормальной форме)
- Поддержка стоп-слов (игнорирование часто встречающихся слов)
- Кэширование результатов для ускорения повторных запросов
- Экспорт результатов в JSON/CSV
- Параллельная обработка документов

## Лицензия

Проект создан в рамках лабораторной работы №4 по курсу "Highload Systems Engineering".

## Контакты

По вопросам, связанным с лабораторной работой, обращайтесь к преподавателю курса.
```

Этот README.md файл содержит полную документацию по проекту, включая описание, инструкции по сборке и запуску, примеры использования, теоретическую справку и информацию о реализации.