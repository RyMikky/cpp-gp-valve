#pragma once
#include "settings.h"

// Содержит методы для парсинга командной строки
namespace console {

    using SettingsSet = std::pair<settings::HandlerSettings, settings::ValveSettings>;

    // Возвращает подготовленную структуру с настройками для клапана
    settings::ValveSettings ParseCommandLine(int args, char** argv);

    // Возвращает пару настроек для обработчика и клапана
    SettingsSet GetSettingsSet(int args, char** argv);

} // namespace console