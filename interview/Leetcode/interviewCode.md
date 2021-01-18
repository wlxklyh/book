
```cpp
#include <iostream>
using namespace std;
template<typename T>
class shared_ptr
{
private:
    int* count;
    void *ptr;
public:
    //create
    static shared_ptr createSharePtr(void *ptr){
        shared_ptr newPtr();
        newPtr.ptr = ptr;
        newPtr.count = molloc(4);
        *newPtr.count  =1;
    }
    shared_ptr(const shared_ptr &sharedPtr){
        count = ptr.count;
        *count++;
        ptr = sharedPtr.ptr;
    }
    ~shared_ptr(){
        *count--;
        if(count == 0 && ptr != NULL) {
            delete ptr;
        }
        free(count);
    }
}
int main() {
    //int a;
    //cin >> a;
    cout << "Hello World!" << endl;
}
```