# Triangles-Intersection
C++ реализация поиска пересекающихся треугольников в трёхмерном пространстве.

## Использование
- **Формат ввода:**
```
<количество треугольников>
<координаты 3 вершин треугольника>
...
```
- **Формат вывода:**
```
<номера пересекающихся треугольников>
```

## Сборка
**Зависимости:**
```
- python3 (для тестирования)
```
Чтобы собрать проект, запустите в папке проекта
```
cmake -S . -B build
cmake --build build
```
После этого в папке build будет доступен исполняемый файл - `triangles`.
Для тестирования проекта с использованием тестов из папки `tests` запустите
```
cmake --build build --target test
или
cd build ; ctest
```
Доступны следующие дополнительные опции компиляции:
1. `WITH_DEBUG_OUTPUT` - включить дополнительный вывод в stdout (дамп кэша при каждом запросе). Влияет на обе цели (`lirs` и `ideal`)
2. `WITH_SET_HIRS_SIZE` - для цели `lirs`. С этой опцией вместо одного размера кэша `lirs` принимает на вход два: общий размер кэша и размер списка HIR блоков.
Для их использования при сборке воспользуйтесь следующей командой:
```
cmake -D<название опции> -S . -B build
```
