//字符串匹配BF算法和KMP算法 @kylin
#ifndef __STRING_MATCH_H__
#define __STRING_MATCH_H__

/**
* 字符串匹配BF算法
* 实现1
* @param strSrc   源字符串
* @param strDest  待匹配模式字符串
* @param pos	  查找开始位置
*
* @return 匹配成功返回开始索引，失败返回-1
*/
int StringMatchBF(char*strSrc, char*strDest, int pos);

/**
* 字符串匹配BF算法
* 实现2
* @param s			源字符串
* @param t			待匹配模式字符串
* @param index		查找开始位置
*
* @return 匹配成功返回开始索引，失败返回-1
*/
int index_bf(char *s, char *t, int index);


//BBC ABCDAB ABCAABCDABDE
//	  ABCDABD

/**
* 获取模式串next数组
* 在模式串比较i位置字符时不匹配，1-(i-1)串中第一个字符出现的位置 存储在next[i]处
*-1表示不存在
* @param pattern			模式串
* @param next				next数组
* @param n					数组大小
*
* @warning no 
*/
void next_1(char pattern[], int next[], int n);

/**
* 字符串匹配BF算法加入next
* @param s			源字符串
* @param t			待匹配模式字符串
* @param n			next数组
* @param size		数组和串的大小
* @param index		查找开始位置
*
* @return 匹配成功返回开始索引，失败返回-1
*/
int index_bf_1(char *s, char *t, int *n, int size, int index);

//ABCDABDABCD
/**
* 获取模式串next数组
* 在模式串比较i位置字符时不匹配，从1-(i-1)串中第一个字符出现的位置开始到i-1字符都连续相等的字符数 存储在next[i]处
* 0表示没有
* @param pattern			模式串
* @param next				next数组
* @param n					数组大小
*
* @warning no
*/
void next_2(char pattern[], int next[], int n);

/**
* 字符串匹配BF算法加入next
* @param s			源字符串
* @param t			待匹配模式字符串
* @param n			next数组
* @param size		数组和串的大小
* @param index		查找开始位置
*
* @return 匹配成功返回开始索引，失败返回-1
*/
int index_bf_2(char *s, char *t, int *n, int size, int index);

//AAAAAABBAAAABBAA
/**
* 获取模式串next数组
* 在模式串比较i位置字符时不匹配，从1-(i-1)串中第一个字符出现的位置开始到i-1字符都连续相等的字符数 存储在next[i]处
* 0表示没有
* @param pattern			模式串
* @param next				next数组
* @param n					数组大小
*
* @warning no
*/
void next_3(char pattern[], int next[], int n);

#pragma region 其他人博客分享
//浅谈字符串匹配算法—BF算法及KMP算法
//参考：http://blog.csdn.net/jiajiayouba/article/details/9178789
/*
*KMP算法之next数组代码
*next数组定义：当模式匹配串T失配的时候，next数组对应的元素知道应该用T串的哪个元素进行下一轮的匹配。
*/
//char p[] =     "AACDAADABCD";
void get_next(char *t, int *next);

/*
在字符串s中，从下标index开始查找是否含有字符串t.如果有，返回t在s中的开始位置；如果没有，返回-1。
(使用KMP算法实现)
注：字符数组s和t中，不再保存字符串长度。
//原文中该算法next数组定义错误,int next[strlen(t)] ，进行修改
*/
int index_kmp(char *s, char *t, int*next, int index);

#pragma endregion

//char p[] =     "AACDAADABCD";
void makeNext(const char P[], int next[], int size);
#endif




