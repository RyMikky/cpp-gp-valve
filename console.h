#pragma once
#include "settings.h"

// �������� ������ ��� �������� ��������� ������
namespace console {

    // ���������� �������������� ��������� � ����������� ��� �������
    settings::Settings ParseCommandLine(int args, char** argv);

} // namespace console