leds = {
    # index: (row, col, flag)
	0: (0, 13, 4),
	1: (0, 12, 4)
}
def gen_s(a):
    ps = ""
    fs = ""
    for i in a:
        t = a[i]
        x = 224*t[1]//(13)
        xs = str(x)
        y = 64*t[0]//(4)
        ys = str(y)
        ps += "{"+xs+","+ys+"},"
        fs += str(t[2])+","
    return (ps, fs)