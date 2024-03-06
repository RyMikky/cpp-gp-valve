/*
	Задание:
	Модель клапана. Среда: метан (100 %), параметры: 12-14МПа, 10-15 град С;
	Расположение: на участке трубы, сопротивлением трубы пренебрегаем,
	за трубой емкость «бесконечного» объема, в емкости поддерживается давление 12-14 МПа;
	Требуется: определить расход в зависимости от проходного сечения клапана.
*/

/*
	Принимаем в качестве условий рассчёта факты:
	1) Процесс протекания газа адиабатический (без изменения температуры)
	2) Поток находится в состоянии идеального газа
	3) Потерями на трение и сопрротивление кромки диафрагмы пренебрегаем
*/

/*
	Для работы приложения необходимы: 
	1) Система интерпретации языка Python 3.9+
	2) Библиотеки numpy и matplotlib 
	   - установка для Windows 
			- pip3 install numpy
			- pip3 install matplotlib
	   - установка для Linux (Ubuntu | .pyenv)
	   		- sudo apt-get python3-numpy
			- sudo apt-get python3-matplotlib
	3) Корректно прописанные пути для линковки хеддеров, библиотек и python
		Например:
		\dev\python\include
		\dev\python\Lib\site-packages\numpy\core\include
		\dev\python\libs

	Обёртка matplotlib-cpp работает только в конфигурации Release.
	Debug компилируется, но во время отладки PyImport_Import(PyObject*)
	возвращает nullptr, что приводит к возникновению исключения
*/

Аргументы командной строки
N  | Short | Large command     | Description
1  | -h    | --help            | Show console commands descriptions
2  |       | --atm             | Set pressure dimension unit as Atm
3  |       | --mpa             | Set pressure dimension unit as MPa (used by default)
4  |       | --kalvin          | Set temperature dimension unit as Kalvin
5  |       | --celsium         | Set temperature dimension unit as Celsium (used by default)
6  | -m    | --handler-mode    | Set programm hadler mode (optional parameter)
7  | -n    | --out-file-name   | Set handler report file name (used for txt/png output)
8  |       | --text            | Process handler report in to *.txt file
9  |       | --image           | Process handler report in to *.png file
10 |       | --console         | Process handler report in to system console (used by default)
11 | -g    | --gas-type-str    | Set gas type (print string)
12 | -t    | --gas-cel-temp    | Set gas temperature, in Celsium
13 | -i    | --gas-in-press    | Set gas input to pipe pressure, in MPa
14 | -o    | --gas-out-press   | Set gas output aperture pipe pressure, in MPa
15 | -d    | --gas-press-drop  | Set gas pressure drop on aperture, in MPa (used in package-mode as from-value)
16 | -l    | --gas-drop-limmit | Set gas pressure drop max_value, in MPa (used in package-mode as to-value)
17 | -e    | --gas-drop-step   | Set gas pressure drop step, in MPa (must be set on package-mode)
18 | -p    | --pipe-in-diam    | Set pipe inner diameter, in mm
19 | -s    | --pipe-stl-mark   | Set pipe steel mark (print string)
20 | -a    | --aper-diam       | Set aperture diameter, in mm
21 | -c    | --aper-scale      | Set aperture opened scale, in range 0.0 - 1.0

/*
	Варианты запуска для примера
	-t=15 -g=methane -s=15m -p=100 -a=75 -i=12 -o=11.95
	--text -n=report_file -t=15 -g=methane -s=15m -p=100 -a=75 -i=12 -o=11.95
	--image --text -n=report_file -t=15 -g=methane -s=15m -p=100 -a=75 -i=12 -o=11.95

	-t=0 -g=methane -s=15m -p=100 -a=75 -i=150 -d=0.0 -l=2.5 -e=0.5 --atm
	-t=0 -g=methane -s=15m --text -n=report_file -p=100 -a=75 -i=150 -d=0.0 -l=2.5 -e=0.5 --atm
	-t=0 -l=2.5 -s=15m --text -n=report_file -p=100 -a=75 --image -i=150 -d=0.0 -e=0.5 --atm -g=methane
*/
