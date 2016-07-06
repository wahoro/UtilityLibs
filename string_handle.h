#ifndef STRING_HANDLE_H_
#define STRING_HANDLE_H_

#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>

namespace utilities {
namespace string {

//转换字符串为大写
inline void ToUpper(std::string *s) {
  std::transform(s->begin(), s->end(), s->begin(), ::toupper);
}

//转换字符串为小写
inline void ToLower(std::string *s) {
  std::transform(s->begin(), s->end(), s->begin(), ::tolower);
}

//去除前后的空白符
inline void Trim(std::string *s) {
  s->erase(0, s->find_first_not_of(" \t\r\n"));
  s->erase(s->find_last_not_of(" \t\r\n") + 1);
}

//判断是否以指定字符串开头
inline bool StartWith(const std::string &s, const std::string &start) {
  int res = s.compare(0, start.size(), start);
  return res == 0 ? true : false;
}

//判断是否以指定字符串结束
inline bool EndWith(const std::string &s, const std::string &end) {
  int res = s.compare(s.size() - end.size(), end.size(), end);
  return res == 0 ? true : false;;
}

//切分字符串
//支持同时使用多种分隔符
//但分隔符长度只能为1位
void SplitWithMutilSep(const std::string &s, const std::string &sep,
                       std::vector<std::string> *v) {
  if (!s.empty() && !sep.empty()) {
    size_t last = 0;
    size_t index = s.find_first_of(sep, last);
    while (index != std::string::npos) {
      v->push_back(s.substr(last, index - last));
      last = index + 1;
      index = s.find_first_of(sep, last);
    }

    if (index - last > 0) {
      v->push_back(s.substr(last, index - last));
    }
  }
}

//切分字符串
void Split(const std::string &s, const std::string &sep,
           std::vector<std::string> *v) {
  if (!s.empty() && !sep.empty()) {
    size_t last = 0;
    size_t index = s.find(sep, last);
    while (index != std::string::npos) {
      v->push_back(s.substr(last, index - last));
      last = index + sep.size();
      index = s.find(sep, last);
    }

    if (index - last > 0) {
      v->push_back(s.substr(last, index - last));
    }
  }
}

//连接容器中的所有字符串
//可能需要考虑效率问题
inline std::string ConcatAll(const std::vector<std::string> &v) {
   return std::accumulate(v.begin(), v.end(), std::string(""));
}

//删除字符串中所有指定的字符
inline void EraseAll(std::string *s, char c) {
  s->erase(std::remove_if(s->begin(), s->end(),
          std::bind2nd(std::equal_to<char>(), c)), s->end());
}

}  // namespace string
}  // namespace utilities

#endif // STRING_HANDLE_H_
