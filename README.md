# Тестовое задание для AI People

В тестовом задании требовалось реализовать 3 способа хранения данных:
* Массив пар
* std::map
* АВЛ-дерево

Данные типа long long находились в 4 датасетах записанные парами price-amount

Также требовалось протестировать в "симуляции realtime" работу контейнеров, построчно добавляя записи, а также проверить время выполнения операций.

Был создан шаблонный класс-родитель Container, в котором были объявлены требуемые функции, три класса-потомка (PairArray, PairMap и AVLTree)

Скорости выполнения операций в наносекундах приведены в файлах 

**cmake-build-debug/time_test_dataset4_array.log**,  **cmake-build-debug/time_test_dataset4_map.log** и 

**cmake-build-debug/time_test_dataset4_tree.log**

Примеры вывода операций для построчной работы с наборами данных приведены в файлах 

**cmake-build-debug/realtime_dataset4_array.log**,  **cmake-build-debug/realtime_dataset4_map.log** и 

**cmake-build-debug/realtime_dataset4_tree.log**
