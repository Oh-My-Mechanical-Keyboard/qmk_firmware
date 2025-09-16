// Copyright 2022 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#if (DIODE_DIRECTION == COL2ROW)
void select_cols_595(void);
void unselect_cols_595(void);
#else
void select_rows_595(void);
void unselect_rows_595(void);
#endif
