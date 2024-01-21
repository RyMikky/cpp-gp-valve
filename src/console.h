#pragma once
#include "settings.h"

// Содержит методы для парсинга командной строки
namespace console {

    // Возвращает подготовленную структуру с настройками для клапана
    settings::Settings ParseCommandLine(int args, char** argv);

} // namespace console