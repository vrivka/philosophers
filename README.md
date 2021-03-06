# Philosophers

Учебный проект на языке C для понимания многопоточности и решения "[Задачи об обедающих философах](https://ru.wikipedia.org/wiki/%D0%97%D0%B0%D0%B4%D0%B0%D1%87%D0%B0_%D0%BE%D0%B1_%D0%BE%D0%B1%D0%B5%D0%B4%D0%B0%D1%8E%D1%89%D0%B8%D1%85_%D1%84%D0%B8%D0%BB%D0%BE%D1%81%D0%BE%D1%84%D0%B0%D1%85)".

# Описание

Цель проекта научиться работать с множеством потоков, понять проблему взаимного блокирования в многопоточных программах. Для этих целей использована "Задача об обедающих философах".

- Один или несколько философов сидят за круглым столом. В центре стола стоит большая тарелка со спагетти.
- Философы попеременно едят, думают или спят. Пока они едят, они не думают и не спят; пока думают, они не едят и не спят; и, конечно, пока спят, они не едят и не думают.
- На столе также лежат вилки. Вилок столько же, сколько философов.
- Поскольку подавать и есть спагетти только одной вилкой не очень удобно, философ берет правую и левую вилки, по одной в каждую руку.
- Покончив с едой, философ кладет вилки обратно на стол и засыпает. Проснувшись, начинает думать. Симуляция останавливается, когда философ умирает от голода.
- Каждый философ должен есть и никогда не должен голодать.
- Философы не разговаривают друг с другом.
- Философы не знают, что другой философ вот-вот умрет.
- Программа должна принимать следующие аргументы:
  - `number_of_philosophers`: количество философов, а также количество вилок;
  - `time_to_die` (в миллисекундах): если философ не начал есть `time_to_die` с начала своего последнего приема пищи или начала симуляции, он умирает;
  - `time_to_eat` (в миллисекундах): время, которое требуется философу, чтобы поесть. Во время этого им нужно будет держать две вилки.
  - `time_to_sleep` (в миллисекундах): время, которое философ проведет во сне.
  - `number_of_times_each_philosopher_must_eat` (необязательный аргумент): если все философы съели хотя бы `number_of_times_each_philosopher_must_eat` раз симуляция останавливается. Если не указано, симуляция останавливается, когда философ умирает.
- У каждого философа есть число от `1` до `number_of_philosophers`.
- Любое изменение состояния философа должно быть оформлено следующим образом:
  - `timestamp_in_ms X has taken a fork`
  - `timestamp_in_ms X is eating`
  - `timestamp_in_ms X is sleeping`
  - `timestamp_in_ms X is thinking`
  - `timestamp_in_ms X died`
> `timestamp_in_ms` - текущая метка времени в миллисекундах
> 
> `X` - номер философа.

Особые правила:
- Каждый философ должен быть потоком.
- Между каждой парой философов есть одна вилка. Следовательно, если философов несколько, то у каждого философа есть вилка слева и вилка справа. Если есть только один философ, на столе должна быть только одна вилка.

## Примеры запуска программы
Все философы живы:
```
./philo 4 410 200 200
```
Всем философам хватает времени для еды и сна, и теоретически симуляция никогда не остановится.

Все философы живы, и симуляция остановится, когда каждый философ поест как минимум `7` раз:
```
./philo 5 800 200 200 7
```

Случай, когда один из философов умирает:
```
./philo 4 310 200 100
```
В этом случае философу не хватает времени для взятия вилок и еды.

Интересный случай, когда есть всего один философ:
```
./philo 1 1000 200 100
```
В этом случае неважно сколько времени философ ест или спит, так как у него всего одна вилка, и он никогда не сможет начать есть. Симуляция остановится через `1000` милисекунд, когда истечет время смерти.