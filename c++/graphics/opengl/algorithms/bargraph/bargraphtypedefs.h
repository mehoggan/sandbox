#ifndef BARGRAPHTYPEDEFS_H
#define BARGRAPHTYPEDEFS_H

#include "../../../include/fpstypedefs.h"

typedef std::pair<QString, QColor> BarLabelAndColor_t;
typedef std::pair<int32_t, int32_t> BarRange_t;
typedef std::pair<BarLabelAndColor_t, BarRange_t> ColumnData_t;
typedef std::vector<ColumnData_t > ColumnDataVector_t;

#endif//BARGRAPHTYPEDEFS_H
