#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Operation {
	public:
		Operation(string x, string y) : str_x(x), str_y(y) {}
		string add();
		string subtract();
		string multiply(); 
	private:
		string str_x;
		string str_y;
		string res;
};

string Operation::add() {
	//加法参考链接：https://blog.csdn.net/qq_41722217/article/details/80525524 
	//初始化存储结果的成员变量，排除保留上次运算的结果 
	res = "";
	int lx = str_x.size();
	int ly = str_y.size();
	int limit = lx + ly;
	int len = 0; //取lx和ly的最大长
	int up, j;
	int flag1 = 0; //str_x是否为负数，0正，1负
	int flag2 = 0; //str_y是否为负数，0正，1负
	vector<int> nx(limit, 0), ny(limit, 0);
	
	if(str_x[0] == '-') { //x为负数
		flag1 = 1; 
		//除负号外倒叙存放在nx中
		//负数长度多一个符号位，需减掉这个符号位数再进行存储
		//此处应lx - 1 - 1，一个1是索引从0开始，另一个为符号位数 
		for(int i = lx - 2, k = 1; i >= 0 && k < lx; -- i) {
			nx[i] = (str_x[k] - '0');
			//cout << "nx " << str_x[k] << endl;
			k ++;
		}
	} else { //x为正数
		for(int i = lx - 1, k = 0; i >= 0 && k < lx; -- i) {
			nx[i] = (str_x[k] - '0');
			k ++;
		}
	}
	if(str_y[0] == '-') { //y为负数
		flag2 = 1;
		//除负号外倒叙存放ny中
		//负数长度多一个符号位，需减掉这个符号位数再进行存储
		//此处应lx - 1 - 1，一个1是索引从0开始，另一个为符号位数 
		for(int i = ly - 2, k = 1; i >= 0 && k < ly; -- i) {
			ny[i] = (str_y[k] - '0');
			k ++;
		}
	} else { //y为正数
		for(int i = ly - 1, k = 0; i >= 0 && k < ly; -- i) {
			ny[i] = (str_y[k] - '0');
			k ++;
		}
	}

	//x和y都为正数
	if(flag1 == 0 && flag2 == 0) {
		for(j = 0, up = 0; j < limit; j ++) {
			nx[j] = nx[j] + ny[j] + up;
			up = nx[j] / 10;
			nx[j] %= 10;
		}
		
		for(j = limit - 1; j >= 0; -- j) {
			if(nx[j]) {
				break;
			}
		}
		while(j >= 0) {
			res += to_string(nx[j]);
			j --;
		}
		return res;
	}

	//x和y为负数
	if(flag1 == 1 && flag2 == 1) {
		for(j = 0, up = 0; j < limit; j ++) {
			nx[j] = nx[j] + ny[j] + up;
			up = nx[j] / 10;
			nx[j] %= 10;
		}
		
		for(j = limit - 1; j >= 0; -- j) {
			if(nx[j]) {
				break;
			}
		}
		//都为负数相加后的结果也为负数，故提前加负号
		res = '-';
		while(j >= 0) {
			res += to_string(nx[j]);
			j --;
		}
		return res;
	}

	//x为正，y为负
	if(flag1 == 0 && flag2 == 1) {
		int flagBig = 0; //判断x和y大小
		len = max(lx, ly);
		//判断x和y的绝对值大小
		if(lx < ly - 1) {
			flagBig = 1; //此时x绝对值长度小于y绝对值长度，绝对值y大
		} else {
			//绝对值长度相等判断每一位数字大小
			if(lx == ly - 1) {
				for(int i =len - 1; i >= 0; i --) {
					if(nx[i] < ny[i]) {
						flagBig = 1;
						break;
					}
				}
			}
		}

		//负数y绝对值比x绝对值大
		if(flagBig == 1) {
			for(j = 0; j < limit; j ++) {
				nx[j] = ny[j] - nx[j];
				if(nx[j] < 0) {
					nx[j] += 10;  //向高位借一位
					ny[j + 1] --; //被借高位减一
				}
			}
			for(j = limit - 1; j >= 0; -- j) {
				if(nx[j]) {
					break;
				}
			}
			//此时结果必为负数，故初始第一位为负号
			res = '-';
			while(j >= 0) {
				res += to_string(nx[j]);
				j --;
			}
			return res;
		}
		//绝对值x比绝对值y大或者两个相等 
		else {
			for(j = 0; j < limit; j ++) {
				nx[j] = nx[j] - ny[j];
				if(nx[j] < 0) {
					nx[j] += 10;  //向高位借一位
					nx[j + 1] --; //被借高位减一
				}
			}
			//当x和y一正一负，且两者绝对值相等，则存储结果都为0，故需保留最后一个0 
			for(j = limit - 1; j >= 1; -- j) {
				if(nx[j]) {
					break;
				}
			}
			
			while(j >= 0) {
				res += to_string(nx[j]);
				j --;
			}
			return res;
		} 
	}
	
	//x为负，y为正 
	if(flag1 == 1 && flag2 == 0) {
		int flagBig = 0;
		len = max(lx - 1, ly);
		if(lx - 1 > ly) {
			flagBig = 1;
		} 
		else {
			if(lx - 1 == ly) {
				for(int i = len - 1; i >= 0; i --) {
					if(nx[i] > ny[i]) {
						flagBig = 1;
						break;
					}
				}
			}
		}
		//负数x绝对值大 
		if(flagBig == 1) {
			for(j = 0; j < limit; j ++) {
				nx[j] = nx[j] - ny[j];
				if(nx[j] < 0) {
					nx[j] += 10;
					nx[j + 1] --; 
				}
			}
			for(j = limit - 1; j >= 1; -- j) {
				if(nx[j]) {
					break;
				}
			}
			//此时结果必为负数，故初始第一位为负号
			res = '-';
			while(j >= 0) {
				res += to_string(nx[j]);
				j --;
			}
			return res;
		}
		else { //绝对值y比绝对值x大或者两个相等 
			for(j = 0; j < limit; j ++) {
				nx[j] = ny[j] - nx[j];
				if(nx[j] < 0) {
					nx[j] += 10;
					ny[j + 1] --; 
				}
			}
			//当x和y一正一负，且两者绝对值相等，则存储结果都为0，故需保留最后一个0 
			for(j = limit - 1; j >= 1; -- j) {
				if(nx[j]) {
					break;
				}
			}
			
			while(j >= 0) {
				res += to_string(nx[j]);
				j --;
			}
			return res;
		}
	}
}

string Operation::subtract() {
	/*
	  减法运算可看为x+(-y)， 
	 因此，只需将y进行变号处理，
	 即进行减法运算时负y变正y，
	 正y变负y。对y进行便好处理后
	 再调用加法运算即可 。 
	*/
	int ly = str_y.size();
	string tmp_str_y = str_y; //暂存y的值 
	//初始化存储结果的成员变量，排除保留上次运算的结果 
	res = "";
	if(str_y[0] == '-') {
		string temp = "";
		for(int i = 1; i < ly; i ++) {
			temp += str_y[i];
		}
		str_y = str_y.replace(str_y.begin(), str_y.end(), temp);
	}
	else {
		str_y = str_y.replace(str_y.begin(), str_y.end(), '-' + str_y);
	}
	string result = add();
	//进行完减法运算后恢复y的值(即恢复成员变量str_y的初始值) 
	str_y = str_y.replace(str_y.begin(), str_y.end(), tmp_str_y);
	return result;
}


string Operation::multiply() {
	//参考博客：https://blog.csdn.net/weixin_41376979/article/details/79197186
	res = "";
	int lx = str_x.size(), lenx = 0;
	int ly = str_y.size(), leny = 0;
	int limit = lx + ly;  //多加10位，以防超出 
	int len = 0; //取lx和ly的最大长
	int r = 0;
	int flag1 = 0; //str_x是否为负数，0正，1负
	int flag2 = 0; //str_y是否为负数，0正，1负
	vector<int> nx(limit, 0), ny(limit, 0), nr(2 * limit, 0);
	
	if(str_x[0] == '-') { //x为负数
		flag1 = 1; 
		//除负号外倒叙存放在nx中
		//负数长度多一个符号位，需减掉这个符号位数再进行存储
		//此处应lx - 1 - 1，一个1是索引从0开始，另一个为符号位数 
		lenx = lx - 1;
		for(int i = lx - 2, k = 1; i >= 0 && k < lx; -- i) {
			nx[i] = (str_x[k] - '0');
			//cout << "nx " << str_x[k] << endl;
			k ++;
		}
	} else { //x为正数
		lenx = lx;
		for(int i = lx - 1, k = 0; i >= 0 && k < lx; -- i) {
			nx[i] = (str_x[k] - '0');
			k ++;
		}
	}
	if(str_y[0] == '-') { //y为负数
		flag2 = 1;
		//除负号外倒叙存放ny中
		//负数长度多一个符号位，需减掉这个符号位数再进行存储
		//此处应lx - 1 - 1，一个1是索引从0开始，另一个为符号位数 
		leny = ly - 1;
		for(int i = ly - 2, k = 1; i >= 0 && k < ly; -- i) {
			ny[i] = (str_y[k] - '0');
			k ++;
		}
	} else { //y为正数
		leny = ly;
		for(int i = ly - 1, k = 0; i >= 0 && k < ly; -- i) {
			ny[i] = (str_y[k] - '0');
			k ++;
		}
	}
	
	//进行乘运算 
	//将结果保存在nr 
	for(int i = 0; i < lenx; i ++) {
		for(int j = 0; j < leny; j ++) {
			nr[i + j] += nx[i] * ny[j];
		}
	}
	//进位运算
	for(int i = 0; i < 2 * limit; i ++) {
		if(nr[i] > 9) {
			nr[i + 1] += nr[i] / 10;
			nr[i] %= 10;
		}
	} 
	//x和y都为正数 
	if(flag1 == 0 && flag2 == 0) {
		for(r = 2 * limit - 1; r >= 0; -- r) {
			if(nr[r]) {
				break;
			}
		}
		while(r >= 0) {
			res += to_string(nr[r]);
			r --;
		}
		return res;
	}
	//x和y都为负数
	if(flag1 == 1 && flag2 == 1) {
		for(r = 2 * limit - 1; r >= 0; -- r) {
			if(nr[r]) {
				break;
			}
		}
		while(r >= 0) {
			res += to_string(nr[r]);
			r --;
		}
		return res;
	} 
	//x为负数，y为正数
	if(flag1 == 1 && flag2 == 0) {
		for(r = 2 * limit - 1; r >= 0; -- r) {
			if(nr[r]) {
				break;
			}
		}
		res += "-";
		while(r >= 0) {
			res += to_string(nr[r]);
			r --;
		}
		return res;
	} 
	//x为正数，y为负数 
	if(flag1 == 0 && flag2 == 1) {
		for(r = 2 * limit - 1; r >= 0; -- r) {
			if(nr[r]) {
				break;
			}
		}
		res += "-";
		while(r >= 0) {
			res += to_string(nr[r]);
			r --;
		}
		return res;
	} 
}

