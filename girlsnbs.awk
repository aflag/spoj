function ceil(num) {
    return int(num) == num ? int(num) : int(num) + 1;
}

{
    if ($1 == -1 && $2 == -1) {
        exit 0;
    }
    min = $1 < $2 ? $1 : $2;
    max = $1 > $2 ? $1 : $2;
    if (min == 0) {
        print max;
    } else {
        min++;
        print ceil(max/min);
    }
}
