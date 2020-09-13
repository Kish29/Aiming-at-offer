//
// Created by asus on 9/13/2020.
//

// 面试题3（二）：不修改数组找出重复的数字
// 题目：在一个长度为n+1的数组里的所有数字都在1到n的范围内，所以数组中至
// 少有一个数字是重复的。请找出数组中任意一个重复的数字，但不能修改输入的
// 数组。例如，如果输入长度为8的数组{2, 3, 5, 4, 3, 2, 6, 7}，那么对应的
// 输出是重复的数字2或者3。

#include "cstdio"

/*
 * 使用hash表
 * 时间复杂度 O(log(n))
 * 空间复杂度 O(long(n))
 */

bool duplicationsByHash(const int nums[], int len, int *duplication) {
    if (!nums || len <= 0 || !duplication)
        return false;
    for (int i = 0; i < len; ++i) {
        if (nums[i] < 1 || nums[i] >= len)
            return false;
    }

    int *aid = new int[len]{0};

    for (int j = 0; j < len; ++j) {
        aid[nums[j] - 1]++;
    }

    for (int k = 0; k < len; ++k) {
        if (aid[k] > 1) {
            *duplication = k + 1;
            return true;
        }
    }
    return false;
}


/*
 * 使用二分查找算法
 * 时间复杂度 O(log(n)) * O(n) = O(n log(n))
 * 空间复杂度 O(1)
 */
int countsInRange(const int inputNums[], int inputLen, int rangeStart, int rangeEnd);

bool duplications(const int inputNums[], int inputLen, int *duplication) {
    // 空指针以及非法输入
    if (inputNums == nullptr || inputLen <= 0 || duplication == nullptr)
        return false;
    for (int i = 0; i < inputLen; ++i) {
        if (inputNums[i] < 1 || inputNums[i] >= inputLen)
            return false;
    }
    int rangeStart = 1;
    int rangeEnd = inputLen - 1;
    while (rangeEnd >= rangeStart) {
        int middle = (rangeStart + rangeEnd) >> 1;
        int count = countsInRange(inputNums, inputLen, rangeStart, middle);
        // 如果二分查找结束
        if (rangeEnd == rangeStart) {
            // 如果count == 1表示该范围无重复
            if (count > 1) {
                *duplication = rangeStart;
                return true;
            }
            return false;
        }

        if (count > (middle - rangeStart + 1))  //有重复
            rangeEnd = middle;
        else
            rangeStart = middle + 1;
    }

    return false;
}

int countsInRange(const int inputNums[], int inputLen, int rangeStart, int rangeEnd) {
    int count = 0;
    for (int i = 0; i < inputLen; ++i) {
        if (inputNums[i] >= rangeStart && inputNums[i] <= rangeEnd) {
            count++;
        }
    }
    return count;
}

/**********测试用例**********/
bool contains(int std[], int stdLen, int toBeTest) {
    for (int i = 0; i < stdLen; ++i) {
        if (std[i] == toBeTest)
            return true;
    }
    return false;
}

void Test(char *testName, int inputNums[], int inputLen, int std[], int stdLen, bool isValid) {
    printf("%s start.\n", testName);
    int duplication = 0;
    bool testValid = duplicationsByHash(inputNums, inputLen, &duplication);
    if (testValid == isValid) {
        if (isValid) {
            if (contains(std, stdLen, duplication))
                printf("Passed.\n");
            else
                printf("Failed.\n");
        } else
            printf("Passed.\n");
    } else
        printf("Failed.\n");
}

// 1 普通输入，含重复数字
void Test1() {
    int test[] = {1, 2, 3, 2, 5, 4};
    int std[] = {2};
    Test((char *) "Test1", test, 6, std, 1, true);
}

// 2 普通输入不含重复
void Test2() {
    int test[] = {1, 2, 3, 6, 5, 4};
    int std[] = {-1};
    Test((char *) "Test2", test, 6, std, 1, false);
}


// 3 重复数字是数组最大数字
void Test3() {
    int test[] = {1, 2, 5, 3, 5, 4};
    int std[] = {5};
    Test((char *) "Test3", test, 6, std, 1, true);
}

// 4 重复数字是数组最小数字
void Test4() {
    int test[] = {1, 2, 3, 1, 5, 4};
    int std[] = {1};
    Test((char *) "Test4", test, 6, std, 1, true);
}

// 5 多个重复数字
void Test5() {
    int test[] = {1, 2, 1, 4, 5, 4};
    int std[] = {1, 4};
    Test((char *) "Test5", test, 6, std, 2, true);
}

// 6 含有非法输入
void Test6() {
    int test[] = {1, 2, 0, 6, -5, 4};
    int std[] = {-1};
    Test((char *) "Test6", test, 6, std, 1, false);
}

// 7 传入空指针
void Test7() {
    int *test = nullptr;
    int std[] = {-1};
    Test((char *) "Test7", test, 6, std, 1, false);
}

int main() {
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();
    Test7();
}
