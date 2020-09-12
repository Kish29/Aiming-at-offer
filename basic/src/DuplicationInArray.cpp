//
// Created by asus on 9/12/2020.
//

// 面试题3（一）：找出数组中重复的数字
// 题目：在一个长度为n的数组里的所有数字都在0到n-1的范围内。数组中某些数字是重复的，但不知道有几个数字重复了，
// 也不知道每个数字重复了几次。请找出数组中任意一个重复的数字。例如，如果输入长度为7的数组{2, 3, 1, 0, 2, 5, 3}，
// 那么对应的输出是重复的数字2或者3。

// 参数:
//        numbers:     一个整数数组
//        length:      数组的长度
//        duplication: (输出) 数组中的一个重复的数字
// 返回值:
//        true  - 输入有效，并且数组中存在重复的数字
//        false - 输入无效，或者数组中没有重复的数字

#include "cstdio"

bool has_duplication(int nums[], int len, int *duplication) {
    // 空指针
    if (!nums || len <= 0) {
        return false;
    } else {
        // 非法输入
        // 必须用一个单独的循环，防止交换后的nums[j]是非法输入
        for (int j = 0; j < len; ++j) {
            if (nums[j] < 0 || nums[j] >= len)
                return false;
        }
        for (int i = 0; i < len; ++i) {
            while (nums[i] != i) {
                if (nums[i] == nums[nums[i]]) {
                    *duplication = nums[i];
                    return true;
                }
                // 交换元素
                /*注意数组元素交换不能使用异或算法*/
                // int temp = nums[i];
                // nums[i] = nums[temp];
                // nums[temp] = temp;
                // 优化的顺序
                int temp = nums[nums[i]];
                nums[nums[i]] = nums[i];
                nums[i] = temp;
            }
        }
        return false;
    }
}

/***********测试***********/

// 通过标准
bool contains(const int std[], int std_len, int to_be_tested) {
    for (int i = 0; i < std_len; i++) {
        if (std[i] == to_be_tested)
            return true;
    }
    return false;
}

void test(char *test_name, int input_nums[], int nums_len, const int std[], int std_len, bool is_valid) {
    printf("%s\n", test_name);

    int duplication;

    bool valid = has_duplication(input_nums, nums_len, &duplication);

    // 和标准判定一样
    if (is_valid == valid) {
        // 含有重复数字
        if (valid) {
            if (contains(std, std_len, duplication))
                printf("Passed.\n");
            else
                printf("Failed.\n");
        } else
            printf("Passed.\n");
    } else
        printf("Failed.\n");
}

// 1 重复一个随机数字
void Test1() {
    int input_nums[] = {2, 3, 1, 2, 4};
    int duplications[] = {2};
    test((char *) "Test1", input_nums, 5, duplications, 1, true);
}

// 2 重复数字是数组中的最大数字
void Test2() {
    int input_nums[] = {0, 3, 1, 2, 3};
    int duplications[] = {3};
    test((char *) "Test2", input_nums, 5, duplications, 1, true);
}

// 3 重复数字是数组中的最小数字
void Test3() {
    int input_nums[] = {2, 3, 1, 4, 1};
    int duplications[] = {1};
    test((char *) "Test3", input_nums, 5, duplications, 1, true);
}

// 4 不含有重复数字
void Test4() {
    int input_nums[] = {2, 3, 1, 0, 4};
    int duplications[] = {-1};
    test((char *) "Test4", input_nums, 5, duplications, 1, false);
}

// 5 多个重复数字
void Test5() {
    int input_nums[] = {2, 3, 1, 2, 3};
    int duplications[] = {2, 3};
    test((char *) "Test5", input_nums, 5, duplications, 2, true);
}

// 6 数组中有元素的大小在 0 ~ n-1 之外
void Test6() {
    int input_nums[] = {2, 3, 7, -1, 5};
    int duplications[] = {-1};
    test((char *) "Test6", input_nums, 5, duplications, 1, false);
}

// 7 空指针输入
void Test7() {
    int *input_nums = nullptr;
    int duplications[] = {-1};
    test((char *) "Test7", input_nums, 5, duplications, 1, false);
}

void TestAll() {
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();
    Test7();
}

int main() {
    TestAll();
}





























