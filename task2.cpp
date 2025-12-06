#include <iostream>
#include <sstream>
#include <string>
#include <cctype>

class numfilterbuf : public std::streambuf {
private:
	std::istream *in;
	std::ostream *out;
	
	int cur; //последнее считанное значение, используется в underflow()
protected:

	/* функции записи в поток: */
	
	virtual int overflow(int c) override {
		if (c == traits_type::eof()) {
            return traits_type::eof();
        }
        
        char ch = static_cast<char>(c);
        if (std::isdigit(static_cast<unsigned char>(ch)) || ch == ' ') {
            if (out) {
                *out << ch;
            }
        }
        return c;
	}
	
	/* функции чтения из потока: */
	
	//реализация по-умолчанию инкрементирует позицию указателя в буфере и вызывает segmentation fault
	virtual int uflow() override {
		int result = underflow();
        cur = traits_type::eof(); 
        return result;
	}
	
	virtual int underflow() override {
		if (cur == traits_type::eof()) {
            read_next_filtered_char();
        }
        return cur;		
	}
private:
    void read_next_filtered_char() {
        char ch;
        while (true) {
            if (!in || !in->get(ch)) {
                cur = traits_type::eof();
                break;
            }
            
            if (std::isdigit(static_cast<unsigned char>(ch)) || ch == ' ') {
                cur = static_cast<unsigned char>(ch);
                break;
            }
        }
    }
public:
	numfilterbuf(std::istream &_in, std::ostream &_out)
		: in(&_in), out(&_out), cur(traits_type::eof())
	{}
};

int main(int argc, char **argv){
	const char str1[] = "In 4 bytes contains 32 bits";
	const char str2[] = "Unix time starts from Jan 1, 1970";
	std::istringstream str(str1);
	
	numfilterbuf buf(str, std::cout); // читать из stringstream, выводить в консоль
	std::iostream numfilter(&buf); // таким образом обходимся без реализации своего наследника iostream
	
	std::string val;
	std::getline(numfilter, val);
	numfilter.clear(); // сбросить невалидное состояние после EOF в процессе чтения из stringstream
	
	std::cout << "Original: '" << str1 << "'" << std::endl;
	std::cout << "Read from numfilter: '" << val << "'" << std::endl;
	
	std::cout << "Original: '" << str2 << "'" << std::endl;
	std::cout << "Written to numfilter: '";
	numfilter << str2;
	std::cout << "'" << std::endl;
	
	return 0;
}
