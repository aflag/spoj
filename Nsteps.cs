using System;

public class Nsteps {
    public static long CoordsToNumber(long x, long y) {
        if (y != (x-2) && y != x) {
            return -1;
        }
        if (x % 2 == 0) {
            return x + y;
        } else {
            return x + y - 1;
        }
    }

    public static void Main() {
        int lines = Convert.ToInt32(Console.ReadLine());
        while (lines-- > 0) {
            string[] tuple = Console.ReadLine().Split(' ');
            long number = CoordsToNumber(Convert.ToInt64(tuple[0]), Convert.ToInt64(tuple[1]));
            if (number < 0)  {
                Console.WriteLine("No Number");
            } else {
                Console.WriteLine(number);
            }
        }
    }
}
