/* 
 * File:   StringUtil.h
 * Author: Pham Minh Tuan
 *
 * Created on July 2, 2012, 11:09 AM
 */

#ifndef STRINGUTIL_H
#define	STRINGUTIL_H

#include <QString>
#include <string>
#include <map>

namespace Utils {

class StringUtil {
public:
	static std::string toLowerUTF8(const std::string& text);
	static std::wstring toLowerUTF16(const std::wstring& text);

	static std::string toUpperUTF8(const std::string& text);
	static std::wstring toUpperUTF16(const std::wstring& text);

	static std::string removeDiacriticsUTF8(const std::string& text);
	static std::wstring removeDiacriticsUTF16(const std::wstring& text);

	static int getLevenshteinDistanceUTF8(const std::string& text1, const std::string& text2);
	static int getLevenshteinDistanceUTF16(const std::wstring& text1, const std::wstring& text2);

	static int getLongestCommonStringUTF8(const std::string& text1, const std::string& text2);
	static int getLongestCommonStringUTF16(const std::wstring& text1, const std::wstring& text2);

private:
	static bool _Initialized;
	static std::map<wchar_t, wchar_t> _Diacritical2NonDiacriticalVowelsMap;

	static const std::string _VietnameseVowels;
	static const std::string _NonDiacriticalVietnameseVowels;

	static void init(void);
	static void initDiacritical2NonDiacriticalVowelsMap(void);
};

} // namespace
#endif	/* STRINGCONVERTER_H */

