#include <iostream>

using namespace std;

void print_array(string name, int array[], int N)
{
    cout << name << ": ";
    for (int i = 0; i < N; i++)
        cout << array[i] << " ";
    cout << endl;
}

int main()
{
    srand(time(0));
    const int N = 10;
    int array_1[N];
    int array_2[N];
    for (int i = 0; i < N; i++) {
        array_1[i] = rand() % 100;
    }
    int* ptr_a1 = array_1;
    int* ptr_a2 = array_2;
    int rotate = 0;
    int* ptr_r = &rotate;
    print_array("Generated array", array_1, N);
    while (true){
        cout << "Enter rotate rounds for original array: ";
        cin >> rotate;
        rotate = (N + ((-rotate)%N)) % N;
        // cout << rotate << "\n";
        asm(
                "mov %[ptr_a1], %%rsi                       \n\t" 
                "mov %[ptr_a2], %%rdi                       \n\t" 
                "movl %[rotate], %%ebx                      \n\t"
                "movl %[N], %%ecx                           \n\t" 

            "main_loop:                                     \n\t"
                "movl (%%rsi,%%rbx,4), %%eax                \n\t"
                "cmp %%ebx, %[N]                            \n\t"
                "jg write                                   \n\t"
                "movl $0, %%ebx                             \n\t"
                "movl (%%rsi,%%rbx), %%eax                  \n\t"

            "write:                                         \n\t" 
                "add $1, %%ebx                              \n\t"
                "movl %%eax, (%%rdi)                        \n\t" 
                "add $4, %%rdi                              \n\t"
                "loop main_loop                             \n\t" 
                :

                :[ptr_a1]"m"(ptr_a1), [ptr_a2]"m"(ptr_a2), [N]"m"(N), [rotate]"m"(rotate)
                :"%rax", "%rbx", "%rcx", "%rsi", "%rdi"
        );
        print_array("Array after rotating", array_2, N);}
    return 0;
}