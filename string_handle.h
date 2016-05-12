#ifndef STRING_HANDLE_H_
#define STRING_HANDLE_H_

#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>

namespace utilities {
namespace string {

//ת���ַ���Ϊ��д
inline void ToUpper(std::string *s) {
  std::transform(s->begin(), s->end(), s->begin(), ::toupper);
}

//ת���ַ���ΪСд
inline void ToLower(std::string *s) {
  std::transform(s->begin(), s->end(), s->begin(), ::tolower);
}

//ȥ��ǰ��Ŀհ׷�
inline void Trim(std::string *s) {
  s->erase(0, s->find_first_not_of(" \t\r\n"));
  s->erase(s->find_last_not_of(" \t\r\n") + 1);
}

//�ж��Ƿ���ָ���ַ�����ͷ
inline bool StartWith(const std::string &s, const std::string &start) {
  int res = s.compare(0, start.size(), start);
  return res == 0 ? true : false;
}

//�ж��Ƿ���ָ���ַ�������
inline bool EndWith(const std::string &s, const std::string &end) {
  int res = s.compare(s.size() - end.size(), end.size(), end);
  return res == 0 ? true : false;;
}

//�з��ַ���
void Split(const std::string &s, const std::string &sep,
           std::vector<std::string> *v);

//���������е������ַ���
//������Ҫ����Ч������
inline std::string ConcatAll(const std::vector<std::string> &v) {
   return std::accumulate(v.begin(), v.end(), std::string(""));
}

//ɾ���ַ���������ָ�����ַ�
inline void EraseAll(std::string *s, char c) {
  s->erase(std::remove_if(s->begin(), s->end(),
          std::bind2nd(std::equal_to<char>(), c)), s->end());
}

}  // namespace string
}  // namespace utilities

#endif // STRING_HANDLE_H_
