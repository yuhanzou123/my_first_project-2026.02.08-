#include <iostream>
#include <cstring>  // 包含memcpy所需的头文件
// 移除using namespace std; 避免命名冲突，或重命名自定义类
// 自定义类改名MyVector，避免和std::vector冲突
class MyVector {
private:
    int* mpArr;     // 指向动态数组的指针
    int mCap_;      // 数组总容量
    int mCur;       // 有效元素个数

    // 扩容函数：将数组容量扩展到指定size
    void expand(int size) {
        if (size <= mCap_) return;  // 避免无效扩容
        int* p = new int[size];
        // 拷贝原有有效元素（注意是mCur个，不是mCap_个）
        memcpy(p, mpArr, sizeof(int) * mCur);//注意：memcpy函数拷贝内存是按照字节数拷贝
        delete[] mpArr;  // 释放原有内存
        mpArr = p;
        mCap_ = size;
    }

public:
    // 构造函数：指定初始容量，默认容量设为4（避免容量为0）
    MyVector(int size = 4) : mCur(0), mCap_(size <= 0 ? 4 : size) {
        mpArr = new int[mCap_];
        std::cout << "MyVector创建，初始容量：" << mCap_ << std::endl;
    }

    // 拷贝构造函数：深拷贝，避免浅拷贝导致的double free
    MyVector(const MyVector& other) {
        mCap_ = other.mCap_;
        mCur = other.mCur;
        mpArr = new int[mCap_];
        memcpy(mpArr, other.mpArr, sizeof(int) * mCur);
        std::cout << "MyVector拷贝构造" << std::endl;
    }

    // 赋值运算符重载：深拷贝
    MyVector& operator=(const MyVector& other) {
        if (this == &other) return *this;  // 防止自赋值

        // 释放当前对象的内存
        delete[] mpArr;

        // 深拷贝
        mCap_ = other.mCap_;
        mCur = other.mCur;
        mpArr = new int[mCap_];
        memcpy(mpArr, other.mpArr, sizeof(int) * mCur);
        std::cout << "MyVector赋值重载" << std::endl;
        return *this;
    }

    // 析构函数：释放动态内存
    ~MyVector() {
        delete[] mpArr;
        mpArr = nullptr;  // 空指针，避免野指针
        std::cout << "MyVector销毁，释放内存" << std::endl;
    }

    // 尾部添加元素
    void push_back(int m) {
        if (mCur == mCap_) {
            expand(2 * mCap_);  // 容量不足时扩容为2倍
        }
        mpArr[mCur++] = m;
    }

    // 尾部删除元素（修复语法错误：缺少()）
    void pop_back() {
        if (mCur == 0) {
            std::cout << "无元素可删除！" << std::endl;
            return;
        }
        mCur--;  // 只需减少有效元素计数，无需真正删除内存
    }

    // 在指定位置插入元素
    void insert(int pos, int val) {
        if (pos < 0 || pos > mCur) {  // pos范围：0~mCur（mCur位置是尾部）
            std::cout << "插入位置非法！" << std::endl;
            return;
        }
        if (mCur == mCap_) {
            expand(2 * mCap_);
        }
        // 从后往前移动元素，腾出pos位置
        for (int i = mCur; i > pos; i--) {
            mpArr[i] = mpArr[i - 1];
        }
        mpArr[pos] = val;
        mCur++;
    }

    // 删除所有值为val的元素
    void erase(int val) {
        int newCur = 0;  // 记录新的有效元素个数
        // 遍历数组，保留不等于val的元素
        for (int i = 0; i < mCur; i++) {
            if (mpArr[i] != val) {
                mpArr[newCur++] = mpArr[i];
            }
        }
        mCur = newCur;  // 更新有效元素个数
    }

    // 查找指定值是否存在
    bool find(int val) {
        for (int i = 0; i < mCur; i++) {
            if (mpArr[i] == val) {
                return true;
            }
        }
        return false;
    }

    // 辅助函数：返回有效元素个数
    int size() const {
        return mCur;
    }

    // 辅助函数：返回数组容量
    int capacity() const {
        return mCap_;
    }

    // 辅助函数：打印所有元素
    void print() const {
        if (mCur == 0) {
            std::cout << "数组为空！" << std::endl;
            return;
        }
        std::cout << "数组元素：";
        for (int i = 0; i < mCur; i++) {
            std::cout << mpArr[i] << " ";
        }
        std::cout << "\n有效元素数：" << mCur << "，容量：" << mCap_ << std::endl;
    }
};

// 测试代码
int main() {
    // 1. 创建对象并测试push_back和扩容
    MyVector vec(2);  // 初始容量2
    vec.push_back(10);
    vec.push_back(20);
    vec.print();  // 输出：10 20，size=2，cap=2

    vec.push_back(30);  // 触发扩容（容量变为4）
    vec.print();  // 输出：10 20 30，size=3，cap=4

    // 2. 测试insert
    vec.insert(1, 15);  // 在位置1插入15
    vec.print();  // 输出：10 15 20 30，size=4，cap=4

    // 3. 测试find
    if (vec.find(15)) {
        std::cout << "找到元素15" << std::endl;
    }
    if (!vec.find(99)) {
        std::cout << "未找到元素99" << std::endl;
    }

    // 4. 测试erase
    vec.erase(20);  // 删除值为20的元素
    vec.print();  // 输出：10 15 30，size=3，cap=4

    // 5. 测试pop_back
    vec.pop_back();
    vec.print();  // 输出：10 15，size=2，cap=4

    // 6. 测试空数组pop_back
    MyVector vec2;
    vec2.pop_back();  // 提示无元素可删除

    return 0;
}
// struct houzi{
// int id;
// int skill;
// int against;
// };
// int main(){
//     int n,k;
//     cin>>n>>k;
//     vector<houzi> v(n+1);
//     int x1,x2;
//     for(int i=1;i<=n;i++){
//         cin>>v[i].skill;
//         v[i].id=i;
//     }
//     for(int i=0;i<k;i++){
//       cin>>x1>>x2;
//       v[x1].against=x2;
//       v[x2].against=x1;
//     }
//     vector<int> v1(n+1,0);
//     for(int i=1;i<=n;i++){
//         for(int j=1;j<=n;j++){
//             if(j==i)continue;
//             else if(v[i].against!=j&&v[i].skill>v[j].skill){
//                 v1[i]++;
//             }
//         }
//     }
//     for(int i=1;i<=n;i++){
//         cout<<v1[i]<<' ';
//     }
// }



/* int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> A(n), B(n);
    vector<int> posA(n + 1), posB(n + 1); // posA[x] = x在A中的位置
    // 读取排列A并记录位置
    for (int i = 0; i < n; ++i) {
        cin >> A[i];
        posA[A[i]] = i;
    }
    // 读取排列B并记录位置
    for (int i = 0; i < n; ++i) {
        cin >> B[i];
        posB[B[i]] = i;
    }

    long long total = 0; // 统计符合条件的子序列数量

    // 枚举所有连续数值区间 [l, r]（魔力数列的核心是数值连续）
    for (int l = 1; l <= n; ++l) {
        // 存储区间 [l, r] 内的元素，按在A中的位置排序
        vector<pair<int, int>> elements; // <posA[x], x>

        for (int r = l; r <= n; ++r) {
            // 将当前元素r加入区间，按A中的位置排序
            elements.emplace_back(posA[r], r);
            sort(elements.begin(), elements.end()); // 按A中的位置升序

            // 检查：按A排序后的元素，在B中的位置是否也是升序（相对顺序一致）
            bool is_common = true;
            for (int i = 1; i < elements.size(); ++i) {
                int prev_x = elements[i-1].second;
                int curr_x = elements[i].second;
                // 如果B中前一个元素的位置 > 当前元素，说明顺序不一致
                if (posB[prev_x] > posB[curr_x]) {
                    is_common = false;
                    break;
                }
            }

            if (is_common) {
                total++; // 该区间符合条件，计数+1
            }
        }
    }

    cout << total << endl;

    return 0;
}
 */


























































































































































// struct Train {
//     int direction;  // 1=出发，0=进入，-1=空车
//     set<int> passengers;  // 存储当前车上的旅客编号（自动去重）
//     Train() : direction(-1) {}  // 初始为空车
// };

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);

//     int a, b, c;  // 火车总数，人员总数，指令条数
//     cin >> a >> b >> c;

//     // 初始化火车：索引0不用，1~a为火车编号
//     vector<Train> trains(a + 1);
//     // 初始化旅客所在火车：索引0不用，1~b为旅客编号，初始为0（未分配）
//     vector<int> passenger_train(b + 1, 0);

//     while (c--) {
//         int op;
//         cin >> op;

//         if (op == 1) {
//             // 事件1：1 r s t u
//             int r, s, t, u;
//             cin >> r >> s >> t >> u;
//             // 设置火车r的方向
//             trains[r].direction = u;
//             // 遍历旅客s~t，分配给火车r
//             for (int pid = s; pid <= t; ++pid) {
//                 if (pid < 1 || pid > b) continue;  // 超出旅客范围，忽略
//                 // 从原火车移除该旅客
//                 int old_tid = passenger_train[pid];
//                 if (old_tid != 0) {
//                     trains[old_tid].passengers.erase(pid);
//                 }
//                 // 添加到新火车r
//                 trains[r].passengers.insert(pid);
//                 passenger_train[pid] = r;
//             }
//         } else if (op == 2) {
//             // 事件2：2 r s t
//             int r, s, t;
//             cin >> r >> s >> t;
//             // 目标火车t的方向
//             int dir_t = trains[t].direction;
//             if (dir_t == -1) continue;  // 目标火车是空车，转运全部失败

//             // 遍历火车r~s
//             for (int tid = r; tid <= s; ++tid) {
//                 if (tid < 1 || tid > a) continue;  // 超出火车范围，忽略
//                 int dir_cur = trains[tid].direction;
//                 if (dir_cur != dir_t) continue;  // 方向不同，转运失败

//                 // 方向相同，转运所有旅客
//                 set<int> tmp = trains[tid].passengers;  // 复制当前旅客列表
//                 for (int pid : tmp) {
//                     // 从原火车移除
//                     trains[tid].passengers.erase(pid);
//                     // 添加到目标火车t
//                     trains[t].passengers.insert(pid);
//                     passenger_train[pid] = t;
//                 }
//             }
//         } else if (op == 3) {
//             // 事件3：3 u v w
//             int u, v, w;
//             cin >> u >> v >> w;
//             // 目标火车w为空车，设置方向为1
//             if (trains[w].direction == -1) {
//                 trains[w].direction = 1;
//             }

//             // 遍历旅客u~v
//             for (int pid = u; pid <= v; ++pid) {
//                 if (pid < 1 || pid > b) continue;  // 超出旅客范围，忽略
//                 int old_tid = passenger_train[pid];
//                 if (old_tid == 0) continue;  // 未分配，跳过

//                 // 从原火车移除
//                 trains[old_tid].passengers.erase(pid);
//                 // 添加到目标火车w
//                 trains[w].passengers.insert(pid);
//                 passenger_train[pid] = w;
//             }
//         } else if (op == 4) {
//             // 事件4：4 c
//             int c_query;
//             cin >> c_query;
//             if (c_query == 0) {
//                 // 查询成功从首都发出的总人数（方向1的火车上的旅客总数，去重）
//                 int total = 0;
//                 set<int> counted;  // 记录已统计的旅客，避免重复
//                 for (int tid = 1; tid <= a; ++tid) {
//                     if (trains[tid].direction == 1) {
//                         for (int pid : trains[tid].passengers) {
//                             counted.insert(pid);
//                         }
//                     }
//                 }
//                 total = counted.size();
//                 cout << total << '\n';
//             } else {
//                 // 查询编号c_query的火车的成功运输人数（当前旅客数）
//                 if (c_query < 1 || c_query > a) {
//                     cout << 0 << '\n';
//                 } else {
//                     cout << trains[c_query].passengers.size() << '\n';
//                 }
//             }
//         } else if (op == 5) {
//             // 事件5：查询成功运输人数最多的火车
//             int max_cnt = 0;
//             int res_tid = 0;
//             for (int tid = 1; tid <= a; ++tid) {
//                 int cnt = trains[tid].passengers.size();
//                 if (cnt > max_cnt) {
//                     max_cnt = cnt;
//                     res_tid = tid;
//                 } else if (cnt == max_cnt && cnt > 0 && tid < res_tid) {
//                     res_tid = tid;
//                 }
//             }
//             cout << res_tid << '\n';
//         }
//     }

//     return 0;
// }


// struct train
// {
//     int orientaion;
//     int id;
// };

// struct event1
// {
//     int r,s,t,u;
// };
// struct event2
// {
//     int r,s,t;
// };
// struct event3
// {
//     int u,v,w;
// };
// struct event4
// {
//     int c;
// };
// struct event5
// {
//     int id;
// };


// int main()
// {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     cout.tie(nullptr);
// int a,b,c;
// cin>>a>>b>>c;
// vector<event1> v1;
// vector<event2> v2;
// vector<event3> v3;
// for(int i=0;i<c;i++){
//     int choice;
//     cin>>choice;
//     if(choice==1){
//         int r,s,t,u;
//         cin>>r>>s>>t>>u;
//         event1 vi;
//         vi.r=r;
//         vi.s=s;
//         vi.t=t;
//         vi.u=u;
//         v1.push_back(vi);
//     }
//     else if(choice==2){
//         int r,s,t;
//         cin>>r>>s>>t;
//         event2 vi;
//         vi.r=r;
//         vi.s=s;
//         vi.t=t;
//         v2.push_back(vi);
//     }
//     else if(choice==3){
//         int u,v,w;
//         cin>>u>>v>>w;
//         event3 vi;
//         vi.u=u;
//         vi.v=v;
//         vi.w=w;
//     }
//     else if(choice==4){

//     }
// }



// }































































// struct guest{
//     string name;
//     double remain;
//     int year;
// };
// int main(){
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     cout.tie(nullptr);
//     vector<guest> v;
   
//     while(true){
//         guest a;
//         string s;
//         cin>>s;
//         if(s=="end")break;
//         a.name=s;
//         cin>>a.remain>>a.year;
//         v.push_back(a);
//     }
//     sort(v.begin(),v.end(),[](guest& a1,guest& a2){
//         if(a1.remain!=a2.remain)return a1.remain>a2.remain;
//         else if(a1.year!=a2.year)return a1.year<a2.year;
//         else return a1.name<a2.name;

//     });
//     for(auto w:v){
//         cout<<w.name<<endl;
//     }
//     return 0;
// }