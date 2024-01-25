#pragma once

#include "settings.h"

namespace fittings {

	struct ValveResult {
		double _mass_consumption = NAN;
		double _volume_consumption = NAN;
	};

	/*
		Клапан представляет собой сужающее устройство (СУ)
		Выполненное в виде диафрагмы с переменным диаметром

		A  -------- >> --------- | ---------- >> --------  B 
		Сток                 Диафрагма                 Исток

		-- >> ------------------ | ------------------- >> --
		Датчик вх. давления             Датчик вых. давления     

		Отбор давления в измеряемом трубопроводе (ИТ) ведется
		С помощью фланцевой установки датчиков давления на
		расстоянии 25,4 мм от торцов диафрагмы до оси фланцев
	*/


	class Valve {
	private:
		settings::ValveSettings& _settings;
	public:
		explicit Valve(settings::ValveSettings&);

		// Возвращает массовый расход газа проходящего через клапан, в кг/с
		double GetMassConsumption();

		// Возвращает объемный расход газа проходящего через клапан, в м куб./с
		double GetVolumeConsumption();

		// Возвращает обобщённую структуру с данными по расходу
		ValveResult GetCalculationResult();

		// Возрвращает статус открытия клапана
		bool IsClosed() const;

	private:

		// Возвращает объемный расход газа проходящего через клапан, по переданному значению массового расхода в м куб./с
		double GetVolumeConsumption(double);

		// Получаем перепад давления на диафрагме. В данной редакции метод не используется
		physics::units::pressure::MPa GetPressureDropAtTheAperture();

		// Возвращает диаметер в зависимости от окружающей среды
		math::units::Diameter GetRealTimeDiameter(math::units::Diameter);

		// Возвращает диаметер трубы в зависимости от окружающей среды
		math::units::Diameter GetPipeRealInnerDiameter();

		// Возвращает диаметер диафрагмы в зависимости от окружающей среды
		math::units::Diameter GetApertureRealDiameter();

		// Возвращает отношение диаметра диаафрагмы к диаметру трубы, величина безразмерная
		double GetDiametersRatio() const;

		// Возвращает коэффициент скорости входа потока E, величина безразмерная
		double GetEntryCoefficient();

		// Возвращает коэффициент истечения С, величина безразмерная
		double GetFlowCoefficient();

		// Возвращает коэффициент расширения ε, величина безразмерная
		double GetExpansionCoefficient();

	};


} // namespace fittings