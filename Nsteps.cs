using System;

public class Nsteps {
    public static long CoordsToNumber(long x, long y) {
        if (y != (x-2) && y != x) {
            throw new ArgumentOutOfRangeException();
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
            try {
                long number = CoordsToNumber(Convert.ToInt64(tuple[0]), Convert.ToInt64(tuple[1]));
                Console.WriteLine(number);
            } catch (ArgumentOutOfRangeException) {
                Console.WriteLine("No Number");
            }
        }
    }
}
