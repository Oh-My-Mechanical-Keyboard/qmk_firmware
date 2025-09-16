/* Copyright 2021 JasonRen(biu)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

cal_z_rgb = function gen_rgb_matrix_1(rownum, colnum) {
	    function get_x(col, colnum){
	    	var x = 224 / (colnum - 1) * col;
	    	return Math.round(x);
	    }
	    function get_y(row, rownum) {
	    	var y =  64 / (rownum - 1) * row;
	    	return Math.round(y);
	    }
	    var gen_rgb_matrix_text = new String();
	    for (var i = 0; i < rownum; i++) {
	    	var row_rgb_text = new String();
	    	var yy = get_y(i, rownum).toString();
	    	for (var j = 0; j < colnum; j++) {
	    		var xx = get_x(j, colnum).toString();
	    		row_rgb_text += '{' + xx + ',' + yy + '}'
	    		if (i != rownum -1 | j != colnum - 1) {
	    			row_rgb_text += ', ';
	    		}
	    	}
	    	if (i != rownum - 1) {
	    		row_rgb_text += '\n';
	    	}
	    	gen_rgb_matrix_text += row_rgb_text
	    }
	    return gen_rgb_matrix_text
	}

cal_u_rgb = function gen_rgb_matrix_2(rownum, colnum, reverse) {
    function get_x(col, colnum){
        var x = 224 / (colnum - 1) * col;
        return Math.round(x);
    }
    function get_y(row, rownum) {
        var y =  64 / (rownum - 1) * row;
        return Math.round(y);
    }
    var gen_rgb_matrix_text = new String();
    for (var i = 0; i < rownum; i++) {
        var row_rgb_text = new String();
        var yy = get_y(i, rownum).toString();
        var cnd = 0;
        if (reverse) {
            cnd = 1;
        }
        if (i % 2 == cnd) {
            for (var j = 0; j < colnum; j++) {
                var xx = get_x(j, colnum).toString();
                row_rgb_text += '{' + xx + ',' + yy + '}'
                if (i != rownum -1 | j != colnum - 1) {
                    row_rgb_text += ', ';
                }
            }
        } else {
            for (var j = colnum-1; j >= 0; j--) {
                var xx = get_x(j, colnum).toString();
                row_rgb_text += '{' + xx + ',' + yy + '}'
                if (i != rownum -1 | j != 0) {
                    row_rgb_text += ', ';
                }
            }
        }

        if (i != rownum - 1) {
            row_rgb_text += '\n';
        }
        gen_rgb_matrix_text += row_rgb_text
    }
    return gen_rgb_matrix_text
}


cal_u_rgb_sb_l = function gen_rgb_matrix_3(rownum, colnum, reverse) {
    function get_x(col, colnum){
        var x = 224 / (colnum - 1) * col;
        return Math.round(x);
    }
    function get_y(row, rownum) {
        var y =  64 / (rownum - 1) * row;
        return Math.round(y);
    }
    var gen_rgb_matrix_text = new String();
    for (var i = 0; i < rownum; i++) {
        var row_rgb_text = new String();
        var yy = get_y(i, rownum).toString();
        var cnd = 0;
        if (reverse) {
            cnd = 1;
        }
        if (i % 2 == cnd) {
            for (var j = 0; j < colnum/2; j++) {
                var xx = get_x(j, colnum).toString();
                row_rgb_text += '{' + xx + ',' + yy + '}'
                if (i != rownum -1 | j != colnum - 1) {
                    row_rgb_text += ', ';
                }
            }
        } else {
            for (var j = colnum/2-1; j >= 0; j--) {
                var xx = get_x(j, colnum).toString();
                row_rgb_text += '{' + xx + ',' + yy + '}'
                if (i != rownum -1 | j != 0) {
                    row_rgb_text += ', ';
                }
            }
        }

        if (i != rownum - 1) {
            row_rgb_text += '\n';
        }
        gen_rgb_matrix_text += row_rgb_text
    }
    return gen_rgb_matrix_text
}

cal_u_rgb_sb_r = function gen_rgb_matrix_4(rownum, colnum, reverse) {
    function get_x(col, colnum){
        var x = 224 / (colnum - 1) * col;
        return Math.round(x);
    }
    function get_y(row, rownum) {
        var y =  64 / (rownum - 1) * row;
        return Math.round(y);
    }
    var gen_rgb_matrix_text = new String();
    for (var i = 0; i < rownum; i++) {
        var row_rgb_text = new String();
        var yy = get_y(i, rownum).toString();
        var cnd = 0;
        if (reverse) {
            cnd = 1;
        }
        if (i % 2 == cnd) {
            for (var j = colnum/2; j < colnum; j++) {
                var xx = get_x(j, colnum).toString();
                row_rgb_text += '{' + xx + ',' + yy + '}'
                if (i != rownum -1 | j != colnum - 1) {
                    row_rgb_text += ', ';
                }
            }
        } else {
            for (var j = colnum-1; j >= colnum/2; j--) {
                var xx = get_x(j, colnum).toString();
                row_rgb_text += '{' + xx + ',' + yy + '}'
                if (i != rownum -1 | j != 0) {
                    row_rgb_text += ', ';
                }
            }
        }

        if (i != rownum - 1) {
            row_rgb_text += '\n';
        }
        gen_rgb_matrix_text += row_rgb_text
    }
    return gen_rgb_matrix_text
}



cal_a_row_rgb = function gen_rgb_matrix_5(row, rownum, colnum, reverse) {
    function get_x(col, colnum){
        var x = 224 / (colnum - 1) * col;
        return Math.round(x);
    }
    function get_y(row, rownum) {
        var y =  64 / (rownum - 1) * row;
        return Math.round(y);
    }
    var row_rgb_text = new String();
    var yy = get_y(row, rownum).toString();

    if (reverse) {
        for (var j = colnum-1; j >= 0; j--) {
            var xx = get_x(j, colnum).toString();
            row_rgb_text += '{' + xx + ',' + yy + '},'
        }
    } else {
        for (var j = 0; j < colnum; j++) {
            var xx = get_x(j, colnum).toString();
            row_rgb_text += '{' + xx + ',' + yy + '},'
        }
    }

    return row_rgb_text
}



cal_a_row_rgb_with_skip = function gen_rgb_matrix_6(row, rownum, colnum, reverse, skip_col) {
    function get_x(col, colnum){
        var x = 224 / (colnum - 1) * col;
        return Math.round(x);
    }
    function get_y(row, rownum) {
        var y =  64 / (rownum - 1) * row;
        return Math.round(y);
    }
    function is_in(jj, skip) {
        for (var i = 0; i < skip.length; ++i) {
            if (jj == skip[i]) {
                return true
            }
        }
        return false
    }
    var row_rgb_text = new String();
    var yy = get_y(row, rownum).toString();

    if (reverse) {
        for (var j = colnum-1; j >= 0; j--) {
            var xx = get_x(j, colnum).toString();
            if (is_in(j,skip_col)) {
                row_rgb_text += '       '
            } else {
                row_rgb_text += '{' + xx + ',' + yy + '},'
            }
        }
    } else {
        for (var j = 0; j < colnum; j++) {
            var xx = get_x(j, colnum).toString();
            if (is_in(j,skip_col)) {
                row_rgb_text += '       '
            } else {
                row_rgb_text += '{' + xx + ',' + yy + '},'
            }
        }
    }
    return row_rgb_text
}


cal_a_row_rgb_index_with_skip = function gen_rgb_index_6(start_num, col_num, reverse, skip_col) {
    var row_rgb_text = new String();
    function is_in(jj, skip) {
        for (var i = 0; i < skip.length; ++i) {
            if (jj == skip[i]) {
                return true
            }
        }
        return false
    }
    if (reverse) {
        for (var j = col_num-1; j >= 0; j--) {
            var xx = start_num.toString();
            if (is_in(j,skip_col)) {
                row_rgb_text = ' NO_LED,  ' + row_rgb_text
            } else {
                row_rgb_text = xx + ',  ' + row_rgb_text
                start_num += 1
            }
        }
    } else {
        for (var j = 0; j < col_num; j++) {
            var xx = start_num.toString();
            if (is_in(j, skip_col)) {
                row_rgb_text += ' NO_LED,  '
            } else {
                row_rgb_text += xx + ',  '
                start_num += 1
            }
        }
    }
    row_rgb_text = row_rgb_text.substring(0,row_rgb_text.length-3)
    return [row_rgb_text, start_num]
}

cal_rgb_index_all = function (row_num, col_num, reverse, skip_pair, is_z, last_start) {
    var rgb_index = new String();
    var start_rgb_index = 0;
    if (is_z) {
        if (last_start) {
            for (var i = row_num-1; i >= 0; --i) {
                var rgb_index_row = new String()
                var t = cal_a_row_rgb_index_with_skip(start_rgb_index, col_num, reverse, skip_pair[i])
                rgb_index_row = t[0]
                start_rgb_index = t[1]
                rgb_index = '{' + rgb_index_row + '},' + '\n' + rgb_index
            }
        } else {
            for (var i = 0; i < row_num; ++i) {
                var rgb_index_row = new String()
                var t = cal_a_row_rgb_index_with_skip(start_rgb_index, col_num, reverse, skip_pair[i])
                rgb_index_row = t[0]
                start_rgb_index = t[1]
                rgb_index += '{' + rgb_index_row + '}, \n'
            }
        }
    } else {
        if (last_start) {
            for (var i = row_num-1; i >= 0; --i) {
                var rgb_index_row = new String()
                var t = cal_a_row_rgb_index_with_skip(start_rgb_index, col_num, reverse, skip_pair[i])
                reverse = !reverse
                rgb_index_row = t[0]
                start_rgb_index = t[1]
                rgb_index = '{' + rgb_index_row + '},' + '\n' + rgb_index
            }
        } else {
            for (var i = 0; i < row_num; ++i) {
                var rgb_index_row = new String()
                var t = cal_a_row_rgb_index_with_skip(start_rgb_index, col_num, reverse, skip_pair[i])
                reverse = !reverse
                rgb_index_row = t[0]
                start_rgb_index = t[1]
                rgb_index += '{' + rgb_index_row + '}, \n'
            }
        }
    }
    return rgb_index
}


cal_rgb_matrix_all = function (row_num, col_num, reverse, skip_pair, is_z, last_start) {
    var rgb_position = new String();
    var start_rgb_index = 0;
    if (is_z) {
        if (last_start) {
            for (var i = row_num-1; i >= 0; --i) {
                var rgb_position_row = new String()
                var t = cal_a_row_rgb_with_skip(i, row_num, col_num, reverse, skip_pair[i])
                rgb_position_row = t
                rgb_position += rgb_position_row + '\n'
            }
        } else {
            for (var i = 0; i < row_num; ++i) {
                var rgb_position_row = new String()
                var t = cal_a_row_rgb_with_skip(i, row_num, col_num, reverse, skip_pair[i])
                rgb_position_row = t
                rgb_position += rgb_position_row + '\n'
            }
        }
    } else {
        if (last_start) {
            for (var i = row_num-1; i >= 0; --i) {
                var rgb_position_row = new String()
                var t = cal_a_row_rgb_with_skip(i, row_num, col_num, reverse, skip_pair[i])
                reverse = !reverse
                rgb_position_row = t
                rgb_position += rgb_position_row + '\n'
            }
        } else {
            for (var i = 0; i < row_num; ++i) {
                var rgb_position_row = new String()
                var t = cal_a_row_rgb_with_skip(i, row_num, col_num, reverse, skip_pair[i])
                reverse = !reverse
                rgb_position_row = t
                rgb_position += rgb_position_row + '\n'
            }
        }
    }
    return rgb_position
}


cal_rgb_all = function (row_num, col_num, reverse, skip_pair, is_z, last_start) {
    var str_index = cal_rgb_index_all(row_num, col_num, reverse, skip_pair, is_z, last_start)
    var str_position = cal_rgb_matrix_all(row_num, col_num, reverse, skip_pair, is_z, last_start)
    console.log(str_index)
    console.log(str_position)
}
