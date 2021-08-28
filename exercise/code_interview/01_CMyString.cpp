/*
 * 1. pimpl 构造和拷贝构造
 * 2. pimpl 友元swap写法
 * 3. pimpl 赋值运算符写法
 * 4. pimpl copy and swap 技术
 */

#include <cstring>
#include <utility>
#include <iostream>

class CMyString{
	friend inline void swap(CMyString &, CMyString &); 
public:
	CMyString(const char *pData=nullptr);
	CMyString(const CMyString &str);
	~CMyString(){ if(m_pData) delete [] m_pData; }

	CMyString &operator=(const CMyString &);
	//CMyString &operator=(const CMyString str);
	
	void print();
private:
	char *m_pData;
};

CMyString::CMyString(const char *pData=nullptr){
	if(pData){
		m_pData=new char[strlen(pData)+1];
		strcpy(m_pData, pData);
	}else
		m_pData=nullptr;
}

CMyString::CMyString(const CMyString &str){
	if(str.m_pData){
		m_pData=new char[strlen(str.m_pData)+1];
		strcpy(m_pData, str.m_pData);
	}else
		m_pData=nullptr;
}

CMyString &CMyString::operator=(const CMyString &str){
	if(this == &str) return *this;
	char *oldm_pData=m_pData;	
	if(str.m_pData){
		m_pData=new char[strlen(str.m_pData)+1];
		strcpy(m_pData, str.m_pData);
	}else
		m_pData=nullptr;
	delete [] oldm_pData;
	return *this;
}

/*
CMyString &CMyString::operator=(const CMyString str){
	swap(*this, str);
	return *this;
}
*/

inline void swap(CMyString &lhs, CMyString &rhs){
	using std::swap; 
	std::swap(lhs.m_pData, rhs.m_pData);
}

void CMyString::print(){
	if(m_pData)
		std::cout<<m_pData<<std::endl;
}

int main(int argc, char *argv[]){
  const char *p="123";
  CMyString str1(p);
  CMyString str2;
  str2=str1;
  str2.print();
  return 0;
}

