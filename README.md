# Text-Statistics-Tool
## 一、功能
读取指定文本文件，统计字符数（含/不含空格和标点符号）、单词数、行数、高频词（TOP10）。

## 二、训练重点
ifstream大文件读取、string的遍历与处理、map<string, int>统计词频、对map值排序、STL算法（count/replace），过滤停用词（is/a/an/the等等）、支持多文件统计、输出统计结果到新文件。

## 三、我的思路
将任务分为两部分：（1）读取文本；（2）将单词出现频率从高到低排序；（3）输出统计结果。最后的执行函数`run`也是按照这个顺序进行的。

### 1)读取文本
1. 使用`getline`一行一行地读取，读取一行字符串**text**后，进行分析。
2. 先将这一行字符串所有大写字母转换为小写形式，再遍历字符串：
  - **if (text[idx] == (空格 || 标点符号)) idx++**，跳过该字符；
  - **else text[i] == 单词**，使用`read_word`函数读取这个单词：
    - 如果读取到的单词在要过滤的名单中（过滤名单见代码），则不予理睬
    - 否则将该单词出现次数++

### 2)将单词出现频率从高到低排序
这一步我直接使用STL中的`sort`了。

### 3)输出统计结果
共5+n行（n == 高频词数量num >= 10 ? 10 : num），前4行分别是：字符数（含空格和标点符号）、字符数（不含空格和标点符号）、单词数、行数。第五行是**High-frequency words(Top 10)**，接下来10行是高频词 Top 10（若不足10个则按实际个数输出）。

## 四、注意事项
1. 代码需要在C++ 20及以上才能运行（因为使用了`ranges`头文件范围库及相关操作）；
2. 读取的文本仅支持全英文文本，不能包含任何中文（中文统计功能本来是想加入的，但是我能力不够）；
3. 读取的文本的每一行的末尾不能包含不完整的单词，即不能有使用**连字符**将本行放不下的单词放在下一行的情况，否则读取的单词不完整；
4. 不能识别**复合词**；
5. 代码中可能有未知Bug和可以优化的地方，如果您发现了，希望您能告知作者，因为作者是在读大学生，希望提高自己的能力。

## 五、演示示例
### 文章（不知道什么原因，一个段落都显示到一行中了）：
```txt
Food and Health: The Foundation of a Good Life
"You are what you eat" is an old saying that holds more truth today than ever before. Our diet is not just about satisfying hunger—it directly shapes our physical health, energy levels, mental clarity, and even our long-term lifespan. In a world dominated by fast food and ultra-processed snacks, understanding the connection between what we eat and how we feel has become essential.
A balanced diet is the cornerstone of good health. It does not mean strict restrictions or giving up all the foods we love. Instead, it means eating a variety of nutrient-dense foods in the right proportions. This includes plenty of colorful fruits and vegetables, which are packed with vitamins, minerals, and antioxidants that protect our bodies from diseases. Whole grains like brown rice and oats provide sustained energy, while lean proteins such as fish, chicken, and beans help build and repair our muscles. Healthy fats from nuts, avocados, and olive oil are crucial for brain function and heart health.
Unfortunately, modern lifestyles have led many people to rely heavily on processed foods. These convenient options are often loaded with added sugars, salt, and unhealthy trans fats, but lack essential nutrients. Regular consumption of these foods can lead to a range of health problems, including obesity, heart disease, type 2 diabetes, and high blood pressure. They can also cause energy crashes, leaving us feeling tired and sluggish throughout the day.
What many people do not realize is that diet also has a profound impact on our mental health. Research has shown that a diet rich in whole foods can reduce the risk of depression and anxiety. The gut is often called our "second brain," and the food we eat affects the production of neurotransmitters like serotonin, which regulates our mood. On the contrary, a diet high in sugar and processed foods can disrupt this balance and worsen mood swings.
Making small, sustainable changes to your eating habits can have a huge impact on your overall health. Start by adding one extra serving of vegetables to your meals each day. Swap sugary drinks for water or herbal tea. Try cooking at home more often, so you can control the ingredients in your food. Remember, healthy eating is a journey, not a destination. It is okay to enjoy your favorite treats occasionally, as long as you maintain balance most of the time.
In conclusion, the food we choose to eat is one of the most powerful tools we have for taking care of our health. By nourishing our bodies with wholesome foods, we can increase our energy, improve our mood, and reduce the risk of chronic diseases. A healthy diet is not just about living longer—it is about living better.
```

### 输出的统计结果：
```txt
character count including spaces: 3193
character count excluding spaces: 2212
Totally words: 151
Totally lines: 7
High-frequency words(Top 10)
our: 12
health: 8
foods: 7
diet: 6
food: 5
not: 5
your: 5
energy: 4
eat: 4
healthy: 3
```
