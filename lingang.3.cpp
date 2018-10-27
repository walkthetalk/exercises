/*
 * 字符串处理
 * @描述
 *  定义字符串的以下几种操作：
 *  reverse(A)获得A字符串的逆序字符串，例如reverse("abc") = "cba"
 *  shuffle(A)获得A随机重排的字符串，例如shuffle("dog") ∈ {"dog", "dgo", "odg", "ogd", "gdo", "god"}
 *  merge(A1, A2)，合并A1和A2两个字符串，合并过程中只保证A1和A2本身字母的顺序，
 *  例如merge("qwe", "asd")的可能结果有很多， “qweasd”和“qwased”都是可能的取值。
 *  现在给定一个字符串S，S ∈merge(reverse(A), shuffle(A))。求以字母表顺序排序的A的最小值。
 * 
 * @输入描述
 *  输入一个字符串S。
 *
 * @输出描述
 *  输出一个字符串，为A的最小取值。
 *
 * @样例输入 1  
 *  abcdefgabcdefg
 * @样例输出 1
 *  agfedcb
 * @提示
 *  reverse("agfedcb") = "bcdefga"
 *  shuffle("agfedcb") = "abcdefg"
 *  merge("bcdefga", "abcdefg") = "abcdefgabcdefg"
 */

#include <iostream>
#include <string>

typedef std::string::reverse_iterator it;

// NOTE: valid char number
constexpr int vcharnum = 256;
// NOTE: must bigger than any valid character.
constexpr int bcharlimit = 256;

/*
 * @flg:  flag array, store processed state.
 * @sidx: range start close index
 * @eidx: range end close index
 * @ret:  return string
 */
void process(bool * flg, it & sidx, const it eidx, std::string & ret)
{
	while (sidx <= eidx) {
		// 查找区间内最小字符
		unsigned int tmp = bcharlimit;
		for (auto i = sidx; i <= eidx; ++i) {
			const int c = (unsigned int)*i;
			if (c < tmp && !flg[c]) {
				sidx = i + 1;	// 更新区间起始位置
				tmp  = c;
			}
		}
		// 找到新字符，更新返回结果
		if (tmp != bcharlimit) {
			ret += (char)tmp;
			flg[tmp] = true;
		}
		// 所有字符均处理过，结束查找
		else {
			sidx = eidx + 1;
			break;
		}
	}
}

int main()
{
	std::string str;
	std::cin >> str;

	// 每个字符出现的次数
	int cnt[vcharnum] = { 0 };
	// 每个字符是否已输出过
	bool flg[vcharnum] = { false };

	// 存储最终结果
	std::string ret = "";
	auto sidx = str.rbegin();
	for (auto i = str.rbegin(); i != str.rend(); ++i) {
		const unsigned int tmp = (unsigned int)*i;
		++cnt[tmp];
		// 此字符必定在目前已扫描过的字符序列中
		if (cnt[tmp] >= 2) {
			process(flg, sidx, i, ret);
		}
	}

	std::cout << ret << std::endl;

	return 0;
}
