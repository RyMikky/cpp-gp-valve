#pragma once

// Определения и константы для работы системы
namespace defines {

#define PRESSURE float                                       // давление
#define PRESSURE_PTR float*                                  // давление
#define RADIUS float                                         // радиус 
#define DIAMETER float                                       // диаметер
#define DENSITY float                                        // плотность
#define KTEMP float                                          // температура в кельвинах          
#define CTEMP float                                          // темераатура в цельсиях  
#define CTEMP_PTR float*                                     // темераатура в цельсиях  
#define MASS float                                           // масса килограмм / моль
#define EFFECTIVENESS float                                  // эффективность клапана
#define FLAG bool                                            // флагсостояния
#define PRECENT float                                        // процент открытия
#define CONSUMPTION float                                    // расход
#define VSQARE float                                         // площадь сечения 

#define VOID void
#define FALSE false
#define TRUE true
#define TEXT std::string
#define NOAP_STR std::string(detail::_NOAP)
#define PAIR_TSW std::pair<std::string_view, std::string_view>

#define R physics::constants::_R                             // универсальная газовая постоянная
#define PI math::constants::_PI                              // число Пи


}