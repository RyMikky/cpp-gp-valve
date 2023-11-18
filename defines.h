#pragma once

namespace fittings {

#define PRESSURE float                                       // давление
#define PRESSURE_PTR float*                                  // давление
#define RADIUS float                                         // радиус 
#define DENSITY float                                        // плотность
#define KTEMP float                                          // температура в кельвинах          
#define CTEMP float                                          // темераатура в цельсиях  
#define CTEMP_PTR float*                                     // темераатура в цельсиях  
#define MASS float                                           // масса килограмм / моль
#define EFFECTIVENESS float                                  // эффективность клапана
#define FLAG bool                                            // флагсостояния
#define PRECENT float                                        // процент открытия
#define CONSUMPTION float                                    // расход
#define VOID void
#define VSQARE float                                         // площадь сечения 

#define R physics::constants::_R                             // универсальная газовая постоянная
#define PI math::constants::_PI                              // число Пи

#define STREAM_PREASSURE PRESSURE* _pres;                    // давление потока газа
#define STREAM_MOL_MASS MASS _m_mass;                        // молярная масса газа
#define STREAM_С_TEMP CTEMP* _c_temp;						 // температур потока в цельсиях
#define VALVE_RADIUS RADIUS _v_rad;                          // радиус клапана
#define PIPE_RADIUS RADIUS _p_rad;                           // радиус труб
#define VALVE_STATUS FLAG _is_closed;                        // состояние клапана
#define VALVE_STANCE PRECENT _scale;                         // процент открытия клапана

}