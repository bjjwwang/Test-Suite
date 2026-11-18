/* AE skips a function's component whose input is covered by its input at
 * the previous iteration. Both calls of wrap reach id through the same call
 * site, so id's input is wrap's n: [3, 3] at the first call, and at the
 * second the actuals of both calls joined, [0, 15]. The second input is not
 * covered by the first, so AE must analyse id again: skipping it would keep
 * the result of the first call, j = [3, 3], and miss the possible overflow
 * at a[j]. */
extern void SAFE_BUFACCESS(void *buffer, int size);
extern void UNSAFE_BUFACCESS(void *buffer, int size);

__attribute__((noinline)) static int id(int n)
{
    return n;
}

__attribute__((noinline)) static int wrap(int n)
{
    return id(n);
}

int main(int argc, char **argv)
{
    char a[10];
    int i = wrap(3);
    SAFE_BUFACCESS(a, i);
    int n = argc > 1 ? 15 : 0;
    int j = wrap(n);
    UNSAFE_BUFACCESS(a, j);
    return 0;
}
