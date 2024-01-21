#pragma once

#include "valve.h"
#include "console.h"

namespace handler {

	// �����-���������� ���������� ������������ � ����� ������ �� ������� ���� ����������� ����� ������
	class Handler {
	private:
		settings::Settings _settings = {};
	public:
		Handler() = delete;
		Handler(int args, char** argv);

		Handler& Run();
		Handler& Save();

	private:
		std::unique_ptr<fittings::Valve> _valve = nullptr;
	};

} // namespace handler