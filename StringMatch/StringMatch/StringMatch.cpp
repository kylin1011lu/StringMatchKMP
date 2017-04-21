#include "stdafx.h"

#pragma region 实现代码

int StringMatchBF(char*strSrc, char*strDest, int pos)
{
	if (strSrc == NULL || strDest == NULL)
	{
		return -1;
	}

	if (strSrc + pos == NULL || *(strSrc + pos) == '\0')
	{
		return -1;
	}

	strSrc = strSrc + pos;

	char* tSrc = strSrc;
	char* tDest = strDest;

	int j = pos;

	while (*strSrc != '\0')
	{
		while (*tSrc == *tDest)
		{
			tDest++;
			tSrc++;
			if (*tDest == '\0')
			{
				return j;
			}
		}

		strSrc++;
		tSrc = strSrc;
		tDest = strDest;
		j++;
	}
	return -1;
}

int index_bf(char *s, char *t, int index)
{
	int i = index;
	int j = 0;
	while (s[i] != '\0')
	{
		while (*(t + j) != '\0' && *(s + i + j) != '\0')
		{
			if (*(t + j) != *(s + i + j))
				break;
			j++;
		}
		if (*(t + j) == '\0')
		{
			return i;
		}
		i++;
		j = 0;
	}
	return -1;
}

//BBC ABCDAB ABCAABCDABDE
//	  ABCDABD

void next_1(char pattern[], int next[], int n)
{
	int i = 0; //首字符位置
	int j = 1; //匹配失败的位置

	next[0] = -1;
	next[1] = -1;

	j = 2;
	for (; j < n;j++)
	{
		next[j] = -1;
		for (int k = 1; k < j;k++)
		{
			if (pattern[i] == pattern[k])
			{
				next[j] = k;
				break;
			}
		}
	}

	for (int i = 0; i < n; i++)
	{
		printf("%3c", pattern[i]);
	}
	printf("\n");
	for (int i = 0; i < n;i++)
	{
		printf("%3d", next[i]);
	}
	printf("\n");
}

int index_bf_1(char *s, char *t, int* n, int size, int index)
{
	int i = index;
	int j = 0;
	next_1(t, n, size);

	while (s[i] != '\0')
	{
		while (*(t + j) != '\0' && *(s + i + j) != '\0')
		{
			if (*(t + j) != *(s + i + j))
				break;
			j++;
		}
		if (*(t + j) == '\0')
		{
			return i;
		}
		
		if (n[j] == -1)
		{
			i++;
		}
		else
		{
			i += n[j];
		}

		//i++;
		j = 0;
	}
	return -1;
}

//ABCDABDABCD
//AACDAADABCD
//AACDAADABCD
void next_2(char pattern[], int next[], int n)
{
	int i = 0; //首字符
	int j = 1; //匹配失败的位置

	next[0] = 0;
	next[1] = 0;

	j = 2;
	for (; j < n; j++)
	{
		int num = 0;
		for (int k = 1; k < j; k++)
		{
			if (pattern[i] == pattern[k])
			{
				i++;
				num++;
			}
			else
			{
				num = 0;
				i = 0;

				if (pattern[i] == pattern[k])
				{
					i++;
					num++;
				}
			}
		}
		next[j] = num;
		i = 0;
	}

	for (int i = 0; i < n; i++)
	{
		printf("%3c", pattern[i]);
	}
	printf("\n");
	for (int i = 0; i < n; i++)
	{
		printf("%3d", next[i]);
	}
	printf("\n");
}

//AAAAAABBAAAABBAA
//AACDAADABCD
void next_3(char pattern[], int next[], int n)
{
	int i = 0; //首字符
	int j = 1; //匹配失败的位置

	next[0] = 0;
	next[1] = 0;

	j = 2;
	for (; j < n; j++)
	{
		int num = 0;
		i = next[j - 1];
		for (int k = 1+next[j-1]; k < j; k++)
		{
			if (pattern[i] == pattern[k])
			{
				i++;
				num++;
			}
			else
			{
				num = 0;
				i = 0;

				if (pattern[i] == pattern[k])
				{
					i++;
					num++;
				}
			}
		}

		next[j] = num;
		//i = 0;
	}

	for (int i = 0; i < n; i++)
	{
		printf("%3c", pattern[i]);
	}
	printf("\n");
	for (int i = 0; i < n; i++)
	{
		printf("%3d", next[i]);
	}
	printf("\n");
}


//char s[] = "BBC ABCDAB ABCAABCDABDE";
//char p[] =     "ABCDABDABCD";
int index_bf_2(char *s, char *t, int *n, int size, int index)
{
	int i = index;
	int j = 0;
	next_2(t, n, size);

	while (s[i] != '\0')
	{
		while (*(t + j) != '\0' && *(s + i + j) != '\0')
		{
			if (*(t + j) != *(s + i + j))
				break;
			j++;
		}

		if (*(t + j) == '\0')
		{
			return i;
		}

		if (n[j] == 0)
		{
			i += j==0?1:j;
			j = 0;
		}
		else
		{
			i += j - n[j];
			j = n[j];
		}

		//i++;
		//j = 0;
	}
	return -1;
}


/*
KMP算法之next数组代码
next数组定义：当模式匹配串T失配的时候，next数组对应的元素知道应该用T串的哪个元素进行下一轮的匹配。
*/
//char p[] =     "AACDAADABCD";
void get_next(char *t, int *next)
{
	int i = 0; //Prefix 前缀  
	int j = 1; //Postfix 后缀  
	next[0] = 0; //自定义的，0和1都从0开始匹配  
	next[1] = 0;

	while (t[j] != '\0')
	{
		if (t[i] == t[j]) //若前后字符匹配，则向前推进  
		{
			i++;
			j++;
			next[j] = i;
			continue;
		}
		else
		{
			i = next[i]; //前后字符不匹配，则回溯。注意，此时是i和j不匹配，因此，根据next数组定义，要回溯到next[i]的值。  
		}
		if (0 == i) //当回溯到首字符时，单独进行处理  
		{
			if (t[i] == t[j])
			{
				next[++j] = ++i;
			}
			else
				next[++j] = i;
		}
	}

	i = 0;
	while (t[i] != '\0')
	{
		printf("%3c", t[i]);
		i++;
	}
	printf("\n");

	i = 0;
	while (t[i] != '\0')
	{
		printf("%3d", next[i]);
		i++;
	}
	printf("\n");
}

/*
在字符串s中，从下标index开始查找是否含有字符串t.如果有，返回t在s中的开始位置；如果没有，返回-1。
(使用KMP算法实现)
注：字符数组s和t中，不再保存字符串长度。
*/
int index_kmp(char *s, char *t, int*next, int index)
{
	//int next[strlen(t)]; 原文中该写法错误
	get_next(t, next);
	int i = index, j = 0;
	while (s[i] != '\0' && t[j] != '\0')
	{
		if (s[i] == t[j])
		{
			i++;
			j++;
			continue;
		}
		else
		{
			j = next[j]; //从模式匹配数组中，获取要回溯到的结点  
		}
		if (0 == j) //单独处理第一个字符  
		{
			if (s[i] == t[j])
			{
				i++;
				j++;
			}
			else
			{
				i++;
			}
		}
	}
	if (t[j] == '\0') //表示字符串t中，所有字符已匹配完毕  
	{
		return i - strlen(t); //因为i以匹配至s中t字符串的结尾。因为要返回的是s中t的开始下标，故i-strlen(t).  
	}
	else
	{
		return -1;
	}
}


//char p[] =     "AACDAADABCD";
void makeNext(const char P[], int next[], int size)
{
	int q, k;//q:模版字符串下标；k:最大前后缀长度
	int m = strlen(P);//模版字符串长度
	next[0] = 0;//模版字符串的第一个字符的最大前后缀长度为0
	for (q = 1, k = 0; q < m; ++q)//for循环，从第二个字符开始，依次计算每一个字符对应的next值
	{
		while (k > 0 && P[q] != P[k])//递归的求出P[0]···P[q]的最大的相同的前后缀长度k
			k = next[k - 1];          //不理解没关系看下面的分析，这个while循环是整段代码的精髓所在，确实不好理解  
		if (P[q] == P[k])//如果相等，那么最大相同前后缀长度加1
		{
			k++;
		}
		next[q] = k;
	}

	for (int i = 0; i < size; ++i)
	{
		printf("%3c", P[i]);
	}
	printf("\n");
	for (int i = 0; i < size; ++i)
	{
		printf("%3d", next[i]);
	}
	printf("\n");
}


#pragma endregion

int _tmain(int argc, _TCHAR* argv[])
{
	char s[] = "BBC ABCDAB ABCAABCDABDAECDABCDABDABCDAACDAADABCD";
	//char p[] = "ABCDABDABCD";
	char p[] = "AACDAADABCD";
	char p2[] = "ABDABABD";
	int n[11] = {};

	int index = -1;
	index = index_bf(s, p, 0);
	printf("index_bf result:%d\n", index);

	index = index_bf_1(s, p, n, 11, 0);
	printf("index_bf_1 result:%d\n", index);

	index = index_bf_2(s, p, n, 11, 0);
	printf("index_bf_2 result:%d\n", index);

	index = index_kmp(s, p,n, 0);
	printf("index_kmp result:%d\n", index);

	next_2(p, n, 11);
	next_3(p, n, 11);
	get_next(p, n);
	makeNext(p, n, 11);


	getchar();
	return 0;
}

//		允许结果
//		index_bf result : 37
//		A  A  C  D  A  A  D  A  B  C  D
//		- 1 - 1  1  1  1  1  1  1  1  1  1
//		index_bf_1 result : 37
//		A  A  C  D  A  A  D  A  B  C  D
//		0  0  1  0  0  1  2  0  1  0  0
//		index_bf_2 result : 37
//		A  A  C  D  A  A  D  A  B  C  D
//		0  0  1  0  0  1  2  0  1  0  0
//		index_kmp result : 37
//		A  A  C  D  A  A  D  A  B  C  D
//		0  0  1  0  0  1  2  0  1  0  0
//		A  A  C  D  A  A  D  A  B  C  D
//		0  0  1  0  0  1  2  0  1  0  0
//		A  A  C  D  A  A  D  A  B  C  D
//		0  0  1  0  0  1  2  0  1  0  0
//		A  A  C  D  A  A  D  A  B  C  D
//		0  1  0  0  1  2  0  1  0  0  0


