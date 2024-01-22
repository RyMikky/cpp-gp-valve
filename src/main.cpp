#include "valve.h"
#include "console.h"

#include <cassert>
#include <iostream>

#include "handler.h"

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "../3rd_party/matplotlibcpp.h"

int main(char args, char** argv) {

	namespace plt = matplotlibcpp;
    // Prepare data.
    int n = 5000;
    std::vector<double> x(n), y(n), z(n), w(n, 2);
    for (int i = 0; i < n; ++i) {
        x.at(i) = i * i;
        y.at(i) = sin(2 * 3.14 * i / 360.0);
        z.at(i) = log(i);
    }

    // Set the size of output image to 1200x780 pixels
    plt::figure_size(1200, 780);
    // Plot line from given x and y data. Color is selected automatically.
    plt::plot(x, y);
    // Plot a red dashed line from given x and y data.
    plt::plot(x, w, "r--");
    // Plot a line whose name will show up as "log(x)" in the legend.
    plt::plot(x, z, { {"label", "log(x)"} });
    // Set x-axis to interval [0,1000000]
    plt::xlim(0, 1000 * 1000);
    // Add graph title
    plt::title("Sample figure");
    // Enable legend.
    plt::legend();
    // Save the image (file format is determined by the extension)
    plt::save("./basic.png");

    std::cout << "plot complete" << std::endl;

	/*
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

	// -t=15 -g=methane -s=15m -p=100 -a=75 -i=12 -o=11.95

	setlocale(LC_ALL, "Russian");
	setlocale(LC_NUMERIC, "English");

	handler::Handler handler(args, argv);

    std::cout << "handler complete" << std::endl;

	/*settings::Settings settings = console::ParseCommandLine(args, argv);
	fittings::Valve valve(settings);

	std::cout << "Gaz mass consumption is " << valve.GetMassConsumption() << " kg/sec" << std::endl;
	std::cout << "Gaz volume consumption is " << valve.GetVolumeConsumption() << " m3/sec" << std::endl;*/
}