
__kernel void fft(__global double *a, __global double2 *b)
{
        int i = get_global_id(0);
        b[i].x = a[i] * a[i];
}