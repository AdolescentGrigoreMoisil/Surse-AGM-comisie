import java.io.OutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.InputMismatchException;
import java.io.IOException;
import java.io.InputStream;

/**
 * Built using CHelper plug-in
 * Actual solution is at the top
 *
 * @author George Marcus
 */
public class Main {
    public static void main(String[] args) {
        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        InputReader in = new InputReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);
        phone solver = new phone();
        solver.solve(1, in, out);
        out.close();
    }

    static class phone {
        public void solve(int testNumber, InputReader in, PrintWriter out) {
            int T = in.readInt();
            while (T-- > 0) {
                int N = in.readInt();
                int X = in.readInt();
                String S = in.readString();

                boolean ans = solve(N, X, S);
                if (ans) {
                    out.println("YES");
                } else {
                    out.println("NO");
                }
            }
        }

        private boolean solve(int N, int X, String S) {
            if (X == 1) {
                return true;
            }
            if (X == 2) {
                for (int i = 1; i < N; i++) {
                    if (S.charAt(i) != '0') {
                        return true;
                    }
                }
                return false;
            }

            for (int middleSize = 1; middleSize <= N; middleSize++) {
                for (int middleStart = 1; middleStart + middleSize - 1 < N - 1; middleStart++) {
                    long middleNumber = parseNumber(middleStart, middleSize, S);
                    int numberCount = 1;
                    if (middleNumber == 1) {
                        continue;
                    }
                    // first number
                    long firstNumber = middleNumber - 1;
                    String firstNumberStr = Long.toString(firstNumber);
                    int firstSize = firstNumberStr.length();
                    int firstEndingSize = middleStart;
                    if (firstSize < firstEndingSize) {
                        continue;
                    }
                    String firstEnding = firstNumberStr.substring(firstSize - firstEndingSize);
                    if (!firstEnding.equals(S.substring(0, firstEndingSize))) {
                        continue;
                    }
                    numberCount++;

                    // middle numbers and ending
                    long currentNumber = middleNumber;
                    int pos = middleStart + middleSize;
                    boolean ok = true;
                    do {
                        long nextNumber = currentNumber + 1;
                        int nextPos = scanNumber(pos, nextNumber, N, S);
                        if (nextPos == -1) {
                            ok = false;
                            break;
                        } else if (nextPos == -2) {
                            // check if it can be the last number
                            String lastNumberStr = Long.toString(nextNumber);
                            int lastStartSize = N - pos;
                            String lastStart = lastNumberStr.substring(0, lastStartSize);
                            numberCount++;
                            if (!lastStart.equals(S.substring(pos))) {
                                ok = false;
                            }
                            break;
                        } else {
                            pos = nextPos;
                            currentNumber = nextNumber;
                            numberCount++;
                        }
                    } while (pos < N);

                    if (ok && numberCount == X) {
                        return true;
                    }
                }
            }
            return false;
        }

        private int scanNumber(int start, long value, int N, String S) {
            int pos = start;
            long currentValue = 0;
            while (pos < N && currentValue < value) {
                currentValue = 10 * currentValue + S.charAt(pos) - '0';
                pos++;
            }
            if (currentValue == value) {
                return pos;
            } else {
                if (pos == N) {
                    return -2;
                } else {
                    return -1;
                }
            }
        }

        private long parseNumber(int start, int size, String S) {
            long ret = 0;
            for (int i = start; i < start + size; i++) {
                ret = 10 * ret + S.charAt(i) - '0';
            }
            return ret;
        }

    }

    static class InputReader {
        private InputStream stream;
        private byte[] buf = new byte[1024];
        private int curChar;
        private int numChars;
        private SpaceCharFilter filter;

        public InputReader(InputStream stream) {
            this.stream = stream;
        }

        public int read() {
            if (numChars == -1)
                throw new InputMismatchException();
            if (curChar >= numChars) {
                curChar = 0;
                try {
                    numChars = stream.read(buf);
                } catch (IOException e) {
                    throw new InputMismatchException();
                }
                if (numChars <= 0)
                    return -1;
            }
            return buf[curChar++];
        }

        public int readInt() {
            int c = read();
            while (isSpaceChar(c))
                c = read();
            int sgn = 1;
            if (c == '-') {
                sgn = -1;
                c = read();
            }
            int res = 0;
            do {
                if (c < '0' || c > '9')
                    throw new InputMismatchException();
                res *= 10;
                res += c - '0';
                c = read();
            } while (!isSpaceChar(c));
            return res * sgn;
        }

        public String readString() {
            int c = read();
            while (isSpaceChar(c))
                c = read();
            StringBuilder res = new StringBuilder();
            do {
                if (Character.isValidCodePoint(c))
                    res.appendCodePoint(c);
                c = read();
            } while (!isSpaceChar(c));
            return res.toString();
        }

        public boolean isSpaceChar(int c) {
            if (filter != null)
                return filter.isSpaceChar(c);
            return isWhitespace(c);
        }

        public static boolean isWhitespace(int c) {
            return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1;
        }

        public interface SpaceCharFilter {
            public boolean isSpaceChar(int ch);

        }

    }
}

