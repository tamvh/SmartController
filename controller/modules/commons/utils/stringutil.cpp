/*
 * File:   StringUtil.cpp
 * Author: Pham Minh Tuan
 *
 * Created on July 2, 2012, 11:10 AM
 */

#include <algorithm>
//#include "Poco/UnicodeConverter.h"
//#include "Poco/String.h"
#include "stringutil.h"

bool Utils::StringUtil::_Initialized = false;
std::map<wchar_t, wchar_t> Utils::StringUtil::_Diacritical2NonDiacriticalVowelsMap;

const std::string Utils::StringUtil::_VietnameseVowels = "àáảãạăằắẳẵặâầấẩẫậèéẻẽẹêềếểễệìíỉĩịòóỏõọôồốổỗộơờớởỡợùúủũụưừứửữựỳýỷỹỵđ";
const std::string Utils::StringUtil::_NonDiacriticalVietnameseVowels = "aaaaaaaaaaaaaaaaaeeeeeeeeeeeiiiiiooooooooooooooooouuuuuuuuuuuyyyyyd";

std::string Utils::StringUtil::toLowerUTF8(const std::string& text) {
    return QString::fromStdString(text).toLower().toStdString();
}

std::string Utils::StringUtil::toUpperUTF8(const std::string& text) {
    return QString::fromStdString(text).toUpper().toStdString();
}

std::wstring Utils::StringUtil::toLowerUTF16(const std::wstring& text) {
    return QString::fromStdWString(text).toLower().toStdWString();
}

std::wstring Utils::StringUtil::toUpperUTF16(const std::wstring& text) {
    return QString::fromStdWString(text).toUpper().toStdWString();
}

std::string Utils::StringUtil::removeDiacriticsUTF8(const std::string& text) {
    std::wstring text16, result16;
//	Poco::UnicodeConverter::toUTF16(text, text16);
    text16 = QString::fromStdString(text).toStdWString();
	result16 = removeDiacriticsUTF16(text16);

    std::string result, _return = "";
//	Poco::UnicodeConverter::toUTF8(result16, result);
    result = QString::fromStdWString(result16).toStdString();
    for (std::string::size_type i = 0; i < result.length(); i++) {
		if (((int)result[i]) != 0)
			_return += result[i];
	}
	return _return;
}

std::wstring Utils::StringUtil::removeDiacriticsUTF16(const std::wstring& text) {
	init();

    std::wstring result;
	result.clear();

    std::map<wchar_t, wchar_t>::const_iterator pos;
    for (std::wstring::size_type i = 0; i < text.length(); i++) {
		pos = _Diacritical2NonDiacriticalVowelsMap.find(text[i]);
		if (pos != _Diacritical2NonDiacriticalVowelsMap.end())
			result += pos->second;
		else
			result += text[i];
	}
	return result;
}

int Utils::StringUtil::getLevenshteinDistanceUTF8(const std::string& text1, const std::string& text2) {
    std::wstring text1_utf16, text2_utf16;
//	Poco::UnicodeConverter::toUTF16(text1, text1_utf16);
    text1_utf16 = QString::fromStdString(text1).toStdWString();
//	Poco::UnicodeConverter::toUTF16(text2, text2_utf16);
    text2_utf16 = QString::fromStdString(text2).toStdWString();
	return getLevenshteinDistanceUTF16(text1_utf16, text2_utf16);
}

int Utils::StringUtil::getLevenshteinDistanceUTF16(const std::wstring& text1, const std::wstring& text2) {
	int m = text1.length(), n = text2.length();
	if (m == 0)
		return n;
	if (n == 0)
		return m;

    int ** d = new int*[m+1];
    for (int i = 0; i < m+1; ++i) {
        d[i] = new int[n+1];
    }

//	int d[m + 1][n + 1];
	for (int i = 0; i < m; i++)
		d[i][0] = i;
	for (int i = 0; i < n; i++)
		d[0][i] = i;

	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			if (text1[i] == text2[j]) {
                d[i][j] = std::min<int>(d[i - 1][j - 1], std::min<int>(d[i - 1][j] + 1, d[i][j - 1] + 1));
			}
			else {
                d[i][j] = std::min<int>(d[i - 1][j - 1] + 1, std::min<int>(d[i - 1][j] + 1, d[i][j - 1] + 1));
			}
		}
	}

	return d[m][n];
}

int Utils::StringUtil::getLongestCommonStringUTF8(const std::string& text1, const std::string& text2) {
    std::wstring text1_utf16, text2_utf16;
    //	Poco::UnicodeConverter::toUTF16(text1, text1_utf16);
    text1_utf16 = QString::fromStdString(text1).toStdWString();
    //	Poco::UnicodeConverter::toUTF16(text2, text2_utf16);
    text2_utf16 = QString::fromStdString(text2).toStdWString();
	return getLongestCommonStringUTF16(toLowerUTF16(text1_utf16), toLowerUTF16(text2_utf16));
}

int Utils::StringUtil::getLongestCommonStringUTF16(const std::wstring& text1, const std::wstring& text2) {
	int m = text1.length(), n = text2.length();
	if (m == 0)
		return 0;
	if (n == 0)
		return 0;

//	int d[m + 1][n + 1];
    int ** d = new int*[m+1];
    for (int i = 0; i < m+1; ++i) {
        d[i] = new int[n+1];
    }

	for (int i = 0; i < m; i++)
		d[i][0] = 0;
	for (int i = 0; i < n; i++)
		d[0][i] = 0;

	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			if (text1[i] == text2[j]) {
				d[i][j] = d[i - 1][j - 1] + 1;
			}
			else {
                d[i][j] = std::max<int>(d[i - 1][j], d[i][j - 1]);
			}
		}
	}

	return d[m][n];
}

void Utils::StringUtil::init(void) {
	if (_Initialized)
		return;
	initDiacritical2NonDiacriticalVowelsMap();
	_Initialized = true;
}

void Utils::StringUtil::initDiacritical2NonDiacriticalVowelsMap(void) {
    std::wstring strVietnameseVowelsUTF16, strNonDiacriticalVietnameseVowelsUTF16;
//	Poco::UnicodeConverter::toUTF16(_VietnameseVowels, strVietnameseVowelsUTF16);
    strVietnameseVowelsUTF16 = QString::fromStdString(_VietnameseVowels).toStdWString();
//	Poco::UnicodeConverter::toUTF16(_NonDiacriticalVietnameseVowels, strNonDiacriticalVietnameseVowelsUTF16);
    strNonDiacriticalVietnameseVowelsUTF16 = QString::fromStdString(_NonDiacriticalVietnameseVowels).toStdWString();

    for (std::wstring::size_type i = 0; i < strVietnameseVowelsUTF16.length(); i++)
		_Diacritical2NonDiacriticalVowelsMap[strVietnameseVowelsUTF16[i]] = strNonDiacriticalVietnameseVowelsUTF16[i];

	strVietnameseVowelsUTF16 = toUpperUTF16(strVietnameseVowelsUTF16);
	strNonDiacriticalVietnameseVowelsUTF16 = toUpperUTF16(strNonDiacriticalVietnameseVowelsUTF16);
    for (std::wstring::size_type i = 0; i < strVietnameseVowelsUTF16.length(); i++)
		_Diacritical2NonDiacriticalVowelsMap[strVietnameseVowelsUTF16[i]] = strNonDiacriticalVietnameseVowelsUTF16[i];
}
