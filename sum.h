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
	//�ӷ��ο����ӣ�https://blog.csdn.net/qq_41722217/article/details/80525524 
	//��ʼ���洢����ĳ�Ա�������ų������ϴ�����Ľ�� 
	res = "";
	int lx = str_x.size();
	int ly = str_y.size();
	int limit = lx + ly;
	int len = 0; //ȡlx��ly�����
	int up, j;
	int flag1 = 0; //str_x�Ƿ�Ϊ������0����1��
	int flag2 = 0; //str_y�Ƿ�Ϊ������0����1��
	vector<int> nx(limit, 0), ny(limit, 0);
	
	if(str_x[0] == '-') { //xΪ����
		flag1 = 1; 
		//�������⵹������nx��
		//�������ȶ�һ������λ��������������λ���ٽ��д洢
		//�˴�Ӧlx - 1 - 1��һ��1��������0��ʼ����һ��Ϊ����λ�� 
		for(int i = lx - 2, k = 1; i >= 0 && k < lx; -- i) {
			nx[i] = (str_x[k] - '0');
			//cout << "nx " << str_x[k] << endl;
			k ++;
		}
	} else { //xΪ����
		for(int i = lx - 1, k = 0; i >= 0 && k < lx; -- i) {
			nx[i] = (str_x[k] - '0');
			k ++;
		}
	}
	if(str_y[0] == '-') { //yΪ����
		flag2 = 1;
		//�������⵹����ny��
		//�������ȶ�һ������λ��������������λ���ٽ��д洢
		//�˴�Ӧlx - 1 - 1��һ��1��������0��ʼ����һ��Ϊ����λ�� 
		for(int i = ly - 2, k = 1; i >= 0 && k < ly; -- i) {
			ny[i] = (str_y[k] - '0');
			k ++;
		}
	} else { //yΪ����
		for(int i = ly - 1, k = 0; i >= 0 && k < ly; -- i) {
			ny[i] = (str_y[k] - '0');
			k ++;
		}
	}

	//x��y��Ϊ����
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

	//x��yΪ����
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
		//��Ϊ������Ӻ�Ľ��ҲΪ����������ǰ�Ӹ���
		res = '-';
		while(j >= 0) {
			res += to_string(nx[j]);
			j --;
		}
		return res;
	}

	//xΪ����yΪ��
	if(flag1 == 0 && flag2 == 1) {
		int flagBig = 0; //�ж�x��y��С
		len = max(lx, ly);
		//�ж�x��y�ľ���ֵ��С
		if(lx < ly - 1) {
			flagBig = 1; //��ʱx����ֵ����С��y����ֵ���ȣ�����ֵy��
		} else {
			//����ֵ��������ж�ÿһλ���ִ�С
			if(lx == ly - 1) {
				for(int i =len - 1; i >= 0; i --) {
					if(nx[i] < ny[i]) {
						flagBig = 1;
						break;
					}
				}
			}
		}

		//����y����ֵ��x����ֵ��
		if(flagBig == 1) {
			for(j = 0; j < limit; j ++) {
				nx[j] = ny[j] - nx[j];
				if(nx[j] < 0) {
					nx[j] += 10;  //���λ��һλ
					ny[j + 1] --; //�����λ��һ
				}
			}
			for(j = limit - 1; j >= 0; -- j) {
				if(nx[j]) {
					break;
				}
			}
			//��ʱ�����Ϊ�������ʳ�ʼ��һλΪ����
			res = '-';
			while(j >= 0) {
				res += to_string(nx[j]);
				j --;
			}
			return res;
		}
		//����ֵx�Ⱦ���ֵy������������ 
		else {
			for(j = 0; j < limit; j ++) {
				nx[j] = nx[j] - ny[j];
				if(nx[j] < 0) {
					nx[j] += 10;  //���λ��һλ
					nx[j + 1] --; //�����λ��һ
				}
			}
			//��x��yһ��һ���������߾���ֵ��ȣ���洢�����Ϊ0�����豣�����һ��0 
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
	
	//xΪ����yΪ�� 
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
		//����x����ֵ�� 
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
			//��ʱ�����Ϊ�������ʳ�ʼ��һλΪ����
			res = '-';
			while(j >= 0) {
				res += to_string(nx[j]);
				j --;
			}
			return res;
		}
		else { //����ֵy�Ⱦ���ֵx������������ 
			for(j = 0; j < limit; j ++) {
				nx[j] = ny[j] - nx[j];
				if(nx[j] < 0) {
					nx[j] += 10;
					ny[j + 1] --; 
				}
			}
			//��x��yһ��һ���������߾���ֵ��ȣ���洢�����Ϊ0�����豣�����һ��0 
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
	  ��������ɿ�Ϊx+(-y)�� 
	 ��ˣ�ֻ�轫y���б�Ŵ���
	 �����м�������ʱ��y����y��
	 ��y�为y����y���б�ô����
	 �ٵ��üӷ����㼴�� �� 
	*/
	int ly = str_y.size();
	string tmp_str_y = str_y; //�ݴ�y��ֵ 
	//��ʼ���洢����ĳ�Ա�������ų������ϴ�����Ľ�� 
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
	//��������������ָ�y��ֵ(���ָ���Ա����str_y�ĳ�ʼֵ) 
	str_y = str_y.replace(str_y.begin(), str_y.end(), tmp_str_y);
	return result;
}


string Operation::multiply() {
	//�ο����ͣ�https://blog.csdn.net/weixin_41376979/article/details/79197186
	res = "";
	int lx = str_x.size(), lenx = 0;
	int ly = str_y.size(), leny = 0;
	int limit = lx + ly;  //���10λ���Է����� 
	int len = 0; //ȡlx��ly�����
	int r = 0;
	int flag1 = 0; //str_x�Ƿ�Ϊ������0����1��
	int flag2 = 0; //str_y�Ƿ�Ϊ������0����1��
	vector<int> nx(limit, 0), ny(limit, 0), nr(2 * limit, 0);
	
	if(str_x[0] == '-') { //xΪ����
		flag1 = 1; 
		//�������⵹������nx��
		//�������ȶ�һ������λ��������������λ���ٽ��д洢
		//�˴�Ӧlx - 1 - 1��һ��1��������0��ʼ����һ��Ϊ����λ�� 
		lenx = lx - 1;
		for(int i = lx - 2, k = 1; i >= 0 && k < lx; -- i) {
			nx[i] = (str_x[k] - '0');
			//cout << "nx " << str_x[k] << endl;
			k ++;
		}
	} else { //xΪ����
		lenx = lx;
		for(int i = lx - 1, k = 0; i >= 0 && k < lx; -- i) {
			nx[i] = (str_x[k] - '0');
			k ++;
		}
	}
	if(str_y[0] == '-') { //yΪ����
		flag2 = 1;
		//�������⵹����ny��
		//�������ȶ�һ������λ��������������λ���ٽ��д洢
		//�˴�Ӧlx - 1 - 1��һ��1��������0��ʼ����һ��Ϊ����λ�� 
		leny = ly - 1;
		for(int i = ly - 2, k = 1; i >= 0 && k < ly; -- i) {
			ny[i] = (str_y[k] - '0');
			k ++;
		}
	} else { //yΪ����
		leny = ly;
		for(int i = ly - 1, k = 0; i >= 0 && k < ly; -- i) {
			ny[i] = (str_y[k] - '0');
			k ++;
		}
	}
	
	//���г����� 
	//�����������nr 
	for(int i = 0; i < lenx; i ++) {
		for(int j = 0; j < leny; j ++) {
			nr[i + j] += nx[i] * ny[j];
		}
	}
	//��λ����
	for(int i = 0; i < 2 * limit; i ++) {
		if(nr[i] > 9) {
			nr[i + 1] += nr[i] / 10;
			nr[i] %= 10;
		}
	} 
	//x��y��Ϊ���� 
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
	//x��y��Ϊ����
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
	//xΪ������yΪ����
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
	//xΪ������yΪ���� 
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

