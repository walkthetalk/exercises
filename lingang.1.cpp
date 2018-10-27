/*
 * 时间转换
 * @描述
 *  给定一个12小时制的时间，请将其转换成24小时制的时间。
 *  说明：12小时制的午夜12：00：00AM，对应的24小时制时间为00：00：00。
 *  12小时制的中午12：00：00PM，对应的24小时制时间为12：00：00。
 * 
 * @输入描述
 *  一个描述12小时制时间的字符串。所有的输入都是合理的，不用考虑输入不合理的情况。
 * 
 * @输出描述
 *  一个描述24小时制时间的字符串。
 * 
 * @样例输入 1 
 *  08:03:45PM
 * @样例输出 1
 *  20:03:45
 */
#include <iostream>
#include <string>
using namespace std;

int main()
{
	char str[11] = "";
	std::cin >> str;
	str[2] = '\0';
	str[5] = '\0';
	str[9] = str[8];
	str[8] = '\0';
	
	int h = stoi(str);
	int m = stoi(&str[3]);
	int s = stoi(&str[6]);
	if (str[9] == 'P') {
		if (h != 12) {
			h += 12;
		}
	}
	else {
		if (h == 12) {
			h = 0;
		}
	}
	std::printf("%02d:%02d:%02d\n", h, m, s);
	return 0;
}
