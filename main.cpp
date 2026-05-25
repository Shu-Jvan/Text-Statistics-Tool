#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <unordered_set>
#include <ranges>
using namespace std;

class Text_Statistics {
private: // 类成员变量
	int chars_with_spaces, chars_without_spaces;	// 字符数（含/不含空格与标点符号）
	map<string, int> words_frequency;				// 词频
	vector<pair<string, int>> high_frequency_words;	// 高频词
	int word_count, line_count;						// 单词数目、文本行数
	unordered_set<char> punctuation;				// 空格与标点符号

private: // 辅助函数
	/*----- 获得单词 -----*/
	void read_word(const string& text, int& i)
	{
		const int SIZE = text.size();
		string word;
		while (i < SIZE)
		{
			chars_with_spaces++;
			if (punctuation.count(text[i])) break; // 遇见空格或标点符号
			word += text[i];
			i++;
			chars_without_spaces++;
		}
		if (filter(word)) words_frequency[word]++; // 添加
		if (words_frequency.count(word)) word_count++;
	}

	/*----- 过滤器 -----*/
	bool filter(const string& word)
	{
		// 过滤空字符串
		if (word.empty()) return false;
 
		// 过滤常见虚词
		static const unordered_set<string> stop_words = {
			"a", "an", "the", "am", "is", "are", "was", "were",
			"be", "been", "being", "have", "has", "had", "do", "does", "did",
			"will", "would", "shall", "should", "may", "might", "can", "could",
			"of", "in", "on", "at", "to", "for", "with", "by", "about", "as",
			"but", "and", "or", "so", "if", "because", "when", "where", "which",
			"that", "this", "these", "those", "he", "she", "it", "we", "you", "they",
			"i", "me"
		};
		return !stop_words.count(word);
	}

	/*----- 词频排序 -----*/
	void sort_by_value()
	{
		high_frequency_words.assign(words_frequency.begin(), words_frequency.end());
		sort(high_frequency_words.begin(), high_frequency_words.end(), [](const pair<string, int>& a, const pair<string, int>& b)
		{
			return a.second > b.second;
		});
	}

private: // 关键函数
	/*----- 加载文本 -----*/
	void load_from_local()
	{
		ios::sync_with_stdio(false);
		cin.tie(nullptr);
 
		ifstream ifs;
		ifs.open("Text.txt", ios::in);
		if (!ifs.is_open()) throw runtime_error("Error: Failed to open file 'data.txt'!");
 
		string buf;
		while (getline(ifs, buf))
		{
			line_count++;
			int idx = 0;
			const int SIZE = buf.size();
			// 将所有大写字母转为小写
			auto lowerView = buf | views::transform([](unsigned char c)
			{
				return tolower(c);
			});
			string lowerStr(lowerView.begin(), lowerView.end());
			// 读取单词
			while (idx < SIZE)
			{
				const char character = buf[idx];
				// 碰到空格或标点符号
				if (punctuation.count(character))
				{
					idx++;
					chars_with_spaces++;
				}
				else read_word(lowerStr, idx);
			}
		}
		ifs.close();
	}

	/*----- 保存统计结果 -----*/
	void save_to_local()
	{
		ofstream ofs;
		ofs.open("Result.txt", ios::out);
		ofs << "character count including spaces: " << chars_with_spaces << endl;		// 字符数（含空格与标点符号）
		ofs << "character count excluding spaces: " << chars_without_spaces << endl;	// 字符数（不含空格与标点符号）
		ofs << "Totally words: " << word_count << endl;	// 单词数（包括被过滤了的单词）
		ofs << "Totally lines: " << line_count << endl;	// 文本行数
		ofs << "High-frequency words(Top 10)" << endl;	// 高频词（前10）
		for (const auto& p : high_frequency_words | views::take(10))
		{
			ofs << p.first << ": " << p.second << endl;
		}
		ofs.close();
	}

public:
	/*----- 构造函数 -----*/
	Text_Statistics()
	{
		chars_with_spaces = chars_without_spaces = 0;
		word_count = line_count = 0;
 
		// 添加标点符号
		for (int i = 32; i <= 47; i++) punctuation.insert(i);
		for (int i = 58; i <= 64; i++) punctuation.insert(i);
		for (int i = 91; i <= 96; i++) punctuation.insert(i);
		for (int i = 123; i <= 126; i++) punctuation.insert(i);
	}
 
	/*----- 接口 -----*/
	void run()
	{
		load_from_local();	// 先加载
		sort_by_value();	// 再排序
		save_to_local();	// 再输出
	}
};

int main()
{
	try
	{
		Text_Statistics text_statistics;
		text_statistics.run();
		cout << "Statistics completed successfully!" << endl << "Results saved to Result.txt!" << endl;
	}
	catch (const runtime_error& e)
	{
		cerr << e.what() << endl;
		return 1;
	}
	return 0;
}