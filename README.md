# Фильтр Блума
Реализация фильтра Блума, позволяющая дать быстрый, но вероятностный ответ, присутствует ли объект в коллекции.

Реализация самой структуры данных инкапуслирована, т.е. не зависит от форматов входных/выходных данных и непосредственно ввода/вывода.

Реализация битового массива также инкапсулирована. Массив битов эффективно расположен в памяти (хранится ввиде массива char'ов, в каждом из которых 8 элементов битового массива).

Параметрами структуры данных являются n - приблизительное количество элементов, P - вероятность ложноположительного ответа.

Размер структуры, *m_size*, вычисляется как *-n \* log2 P / ln 2*, а количество хэш-функций (*m_numHashes*) - как *-log2 P*. Оба значения округляются до ближайшего целого.

В качестве семейства функций используется семейство хэш-функций вида

hi(x) = (((i + 1)*x + Pi+1) mod M) mod m,

где - *x* - ключ, *i* - номер хэш-функции, *Pi* - i-тое по счету простое число, а *M*- 31ое число Мерсенна.

## Формат входных данных
На стандартном потоке ввода задаётся последовательность команд. Пустые строки игнорируются.

Первая строка содержит команду вида set n P.

Каждая последующая строка содержит ровно одну команду: add K, search K или print, где K - неотрицательное число (64 бита вам хватит), ключ.

## Формат результата
* Команда set инициализирует структуру и выводит вычисленные параметры в формате "m k".
* Команда add добавляет в структуру ключ K.
* Команда search выводит либо "1", если элемент возможно присутствует в структуре, либо "0", если он там отсутствует.
* Команда print выводит внутреннее состояние струтуры - последовательность из 0 и 1, не разделенную пробелами.

В любой непонятной ситуации результатом работы любой команды будет "error".

Результат работы программы выводится в стандартный поток вывода.

**Пример:**

Входные данные | Результат работы |
-------------- |:-----------------|
set 2 0.250    |6 2               |
add 7          |010111            |
add 5          |1                 |
add 14         |0                 |
print          |1                 |
search 7       |1                 |
search 10      |1                 |
search 15      |1                 |
search 14      |                  |
search 5       |                  |
search 13      |                  |
