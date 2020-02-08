
/* ------------------------
-     0. 각종 수학 팁      -
------------------------- */

// x ^ y 분할정복 //

ll power(ll x, ll y) { 
    ll ret = 1;
    while (y > 0) {
        if (y % 2) {
            ret *= x;
            ret %= P;
        }
        x *= x;
        x %= P;
        y /= 2;
    }
    return ret;
}



// x C y (Combination) 구하기 (범위 큼) //

문제에서 모듈러 소수 P가 주어졌을 때

1) 페르마 소정리 이용
x C y = x! / y!(x-y)!
fac[x] = (fac[x-1] * x) % P (1 ~ x)
inverse[y!] = y! ^ (P-2)
inv[y-1] = inv[y] * y (y-1 ~ 1)
ans = (fac[x] * inv[y]) % P
ans = (ans * inv[x-y]) % P

2) 뤼카의 정리 이용 (추천)
x C y mod P = x,y를 P진법으로 변환 후 각 자리수마다 Combination 후 곱셈
ex. 
152 C 35 mod 10
= 1 C 0 * 5 C 3 * 2 C 5 mod 10
//주의점 : 이 경우 x C y 에서 y>x 인 경우가 존재할 수 있으므로 예외처리 필수
//주의점2: dp[x][y] = (combi(x-1, y-1) + combi(x-1, y)) % m  ...  <<% m 필수>>





/* ------------------------
-      1. 알고리즘들       -
---------------------------
<차례>
1. LIS(순증가하는 가장 긴 수열)
2. segment tree (합을 저장하는 트리)
-------------------------*/



// 1. LIS (증가하는 가장 긴 수열) //

1) lower_bound 이용 
vector<int> v;
v.push(-INF); //중요!
if(v.back()<arr[i]) v.push_back(arr[i]), len++;
else auto it = lower_bound(v.begin(), v.end(), arr[i]); *it = arr[i];
cout << v.size()-1;
//주의점 : result != LIS 이다. 오직 LIS length만 알 수 있다.

1-1) 실제 LIS 배열 알아내는 방법
vector v를 pair<int, int> 로 만들고 first는 value, second는 index로 매핑
입력배열에 대해 value와 vector v에서 연결된 직전 노드의 index를 저장하는 ex를 가지는 node 배열 생성
node.value 엔 a[i]값이, node.ex엔 직전노드의 index값이, v.first엔 LIS_DP value값이, v.second엔 i값이 들어간다
//주의점 : lower_bound 함수 호출 시 pair<int, int> 에 대한 정렬함수 cmp 잊지 말 것



// 2. segment tree //

1) 기본 segment tree
int sn;
for(sn = 1; sn < n; sn *= 2);
//이 때 시작넘버는 sn, root node의 범위는 1~sn

2) with Lazy Propagate (게으른 전파)
// 사용처 : 만약 update query가 수열의 단일 노드가 아닌 수열의 범위 안에 모든 노드를 업데이트 하라는 query일 경우
수열에 대응되는 lazy 배열 생성
void propagate(int s, int e, int ind){
    if(lazy[ind]){
            tree[ind] += (e-s+1) * lazy[ind];
            if(s!=e){
            lazy[x*2] += lazy[x];
            lazy[x*2+1] += lazy[x];
        }
        lazy[x] = 0;
    }
}
update 함수와 query 함수 시작 시 먼저 propagate
// 주의점 : update 진행 시 자식노드 재귀로 update 후 tree[x] = tree[x*2] + tree[x*2+1] 해주어야 리프에서 정상적으로 위까지 전파