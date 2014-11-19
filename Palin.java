// This file doesn't pass PALIN test case :( I'm still trying to figure out why
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;


public class Palin {
    private int findFirstNotNine(StringBuilder sb, int idx) {
        while (idx >= 0) {
            if (sb.charAt(idx) < '9') {
                return idx;
            }
            --idx;
        }
        return idx;
    }

    private boolean firstHalfLessThanOrEqualToSecondHalf(StringBuilder sb) {
        int middle = sb.length() / 2;
        for (int i = middle; i < sb.length(); i++) {
            if (sb.charAt(sb.length() - i - 1) < sb.charAt(i))
                return true;
            else if (sb.charAt(sb.length() - i - 1) > sb.charAt(i))
                return false;
        }
        return true;
    }

    private void incrementSubstring(StringBuilder sb, int to) {
        int firstSmall = findFirstNotNine(sb, to);
        for (int i = firstSmall+1; i <= to; ++i) {
            sb.setCharAt(i, '0');
        }
        if (firstSmall < 0) {
            sb.insert(0, '1');
        } else {
            sb.setCharAt(firstSmall, (char)(sb.charAt(firstSmall) + 1));
        }
    }

    private void mirrorLeftHalf(StringBuilder sb) {
        int middle_index = sb.length() / 2;
        int last_index = sb.length() - 1;
        for (int i = 0; i < middle_index; ++i) {
            sb.setCharAt(last_index - i, sb.charAt(i));
        }
    }

    public String nextPalin(String number) {
        if (number.length() <= 1)
            return number;

        StringBuilder sb = new StringBuilder(number);

        if (firstHalfLessThanOrEqualToSecondHalf(sb)) {
            if (sb.length() % 2 == 0) {
                incrementSubstring(sb, sb.length() / 2 - 1);
            } else {
                incrementSubstring(sb, sb.length() / 2);
            }
        }

        mirrorLeftHalf(sb);

        return sb.toString();
    }

    public static void main(String args[]) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
 
        int tests = Integer.valueOf(br.readLine());
        Palin p = new Palin();
        for (int i = 0; i < tests; ++i) {
            String number = br.readLine();
            System.out.println(p.nextPalin(number));
        }
    }
}