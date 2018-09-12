/* Copyright 2018 Sandiagal. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

// MIPID 算法接口标准模板。
//
// MIPID 框架下所有算法都将采用该接口以便主程序调用。算法编译成 exe 后再由软件调
// 用，这样算法与软件之间的关系类似于电路元件与芯片，凡是符合该接口模板的 exe 都
// 可以自由替换。需要修改算法时，只需用新的 exe 替换旧的即可。这样跳过了重新编译
// 软件的步骤，后续维护极其方便。开发者之间各司其职，只用维护自己的源码，最后在
// exe 的级别上由 Sandiagal 进行汇总。软件开源的同时，算法依旧闭源，既维护了专利
// 持有者的权利，也迎合了开源共享的趋势。
//
// 该模板包括一个 Solution 类，用于封装所有算法。Solution 内包含了3大主要函数。
// Solution::parser 用于对命令行模式下的参数进行解析，已经包含了常见的数据结构的
// 操作范例。Solution::algorithm 和 Solution::output 是算法的主体和输出，已经基于
// "LeetCode 9 回文数"做出了算法级范例。题目为：判断一个整数是否是回文数。回文数
// 是指正序（从左向右）和倒序（从右向左）读都是一样的整数。例121是回文数，-121不是。
//
// Debug：该接口需要外部输入参数，你可以使用编译器的"命令参数"来模拟输入。该设置
// 在MSVC2015中位于项目属性页的“调试”中。注意 C++ 11 标准会用空格分割字符串，请
// 不要使用带空格的路径的文件名。在必要时请用"image size"的方式保护空格。最后发给
// Sandiagal 的文件请用 Release x64 的方式进行编译。
//
// dev_mode：相信你们发给我的 exe 已经通过了自己的测试，但在实际运行中还会出现意
// 外问题。而该软件架构是不能对编译后 exe 进行 debug 的，所以请参照文中 dev_mode 
// 的方法，在关键位置输出内部信息，以便排查 bug。
//
// 如果你有更好的建议，欢迎致电：sandiagal2525@gmail.com。

#include <iostream>
#include <vector>
#include <String>
#include<windows.h>

class Solution {
public:
	Solution();

	// ==============================================================================
	// 声明参数。以下5种应该包含了所有可能需要的类型。请根据算法需要自行设置。
	int number; //判断该整数是否是回文数。
	std::string image;
	int input_width;
	float input_mean;
	std::vector<float> input_std;
	bool self_test;
	bool dev_mode;
	// ==============================================================================


	// ==============================================================================
	// 你的算法需要的各种内部变量。
	bool ifPalindrome;




	// ==============================================================================

	int parser( int argc, char* argv[] );

	int algorithm();

	int output();

	//为了调试方便，不设置 private 成员。
private:

};

Solution::Solution() {

	// ==============================================================================
	// 初始化参数。以下5种应该包含了所有可能需要的类型。请根据算法需要自行设置。
	number; //不需要初始化。
	image = "aaa.jpg";
	input_width = 224;
	input_mean = 25.45;
	input_std = std::vector<float>( 2, 255 );
	self_test = false;
	dev_mode = false;
	// ==============================================================================

	// ==============================================================================
	// 初始化内部变量。
	ifPalindrome = true;




	// ==============================================================================
}

// 参数解释器。用于对形如"example.exe -i bbb.jpg -input_width 434"的调用方式进行解析。
int Solution::parser( int argc, char* argv[] ) {

	// ==============================================================================
	// 请设置说明文档。
	if( argc < 3 ) { // 输入参数数量不足时，输出使用说明。
		std::cout << "Usage: " << argv[0] << " -n,-number <int>" << std::endl
			<< "Mandatory:" << std::endl
			<< "\t-n,-number\t\t输入数字" << std::endl
			<< "Optional:" << std::endl
			<< "\t-i,--image\t\t图像路径" << std::endl
			<< "\t-iw,--input_width\t缩放到该像素宽" << std::endl
			<< "\t-im,--input_mean\t缩放到该像素均值" << std::endl
			<< "\t-is,--input_std\t\t缩放到该像素标准差" << std::endl
			<< "\t-st,--self_test\t\t进行自我检测" << std::endl
			<< "\t-dm,--dev_mode\t\t开发模式" << std::endl;
		// ==============================================================================

		std::cin.get();
		return -1;
	} else { // 参数数量够了。
		for( int i = 1; i < argc; i += 2 ) {
			if( dev_mode == true ) { // 开发模式：跟踪字符串的传入情况。
				std::cout << argv[i] << ": " << argv[i + 1] << std::endl;
			}

			// ==============================================================================
			// 从"-i bbb.jpg -input_width 434"字符串中解析参数。请根据例子自行修改。
			if( !strcmp( argv[i], "-n" ) || !strcmp( argv[i], "-number" ) ) {
				input_width = atoi( argv[i + 1] );
			} else if( !strcmp( argv[i], "-i" ) || !strcmp( argv[i], "-image" ) ) {
				image = argv[i + 1];
			} else if( !strcmp( argv[i], "-iw" ) || !strcmp( argv[i], "-input_width" ) ) {
				input_width = atoi( argv[i + 1] );
			} else if( !strcmp( argv[i], "-im" ) || !strcmp( argv[i], "-input_mean" ) ) {
				input_mean = atof( argv[i + 1] );
			} else if( !strcmp( argv[i], "-is" ) || !strcmp( argv[i], "-input_std" ) ) {
				input_std.pop_back();
				char *next_token;
				char * token = strtok_s( argv[i + 1], ",", &next_token );
				while( token != NULL ) {
					input_std.push_back( atof( token ) );
					token = strtok_s( NULL, ",", &next_token );
				}
			} else if( !strcmp( argv[i], "-st" ) || !strcmp( argv[i], "-self_test" ) ) {
				self_test = !strcmp( argv[i + 1], "true" ) ? true : false;
				// ==============================================================================

			} else if( !strcmp( argv[i], "-dm" ) || !strcmp( argv[i], "-dev_mode" ) ) {
				dev_mode = !strcmp( argv[i + 1], "true" ) ? true : false;
			} else {
				std::cout << "Not enough or invalid arguments, please try again.\n";
				return -1;
			}
		}
	}

	if( dev_mode == true ) { // 开发模式：输出参数的实际解析情况。

		// ==============================================================================
		std::cout << "Usage: " << argv[0] << std::endl
			<< "Argments:" << std::endl
			<< "\t--number=" << number << "\t\t" << "int\t" << "判断该整数是否是回文数" << std::endl
			<< "\t--image=\"" << image << "\"\t\t" << "string\t" << "图像路径" << std::endl
			<< "\t--input_width=" << input_width << "\t\t" << "int\t" << "缩放到该像素宽" << std::endl
			<< "\t--input_mean=" << input_mean << "\t\t" << "float\t" << "缩放到该像素均值" << std::endl;

		for( int i = 0; i < input_std.size(); i++ ) {
			std::cout << "\t--input_std" << i << "=" << input_std.at( i ) << "\t\t" << "vector<float>\t" << "缩放到该像素标准差" << std::endl;
		}

		std::cout << "\t--self_test=" << self_test << "\t\t" << "bool\t" << "进行自我检测" << std::endl
			<< "\t--dev_mode=" << dev_mode << "\t\t" << "bool\t" << "开发模式" << std::endl;
		// ==============================================================================
	}

	return 0;
}


// 算法主体。注意到 Solution::parser 只包含了字符串级的参数解析，所以对于图像这样
// 的大型文件，请利用 Solution::parser 中设置的路径，自行读取。
int Solution::algorithm() {

	// ==============================================================================
	// 判断回文数
	if( number < 0 ) {
		ifPalindrome = false;
	}

	std::string x_str = std::to_string( number );
	int x_length = x_str.size();
	for( int i = 0; i < x_length / 2; i++ ) {
		if( x_str.at( i ) != x_str.at( x_length - 1 - i ) ) {
			ifPalindrome = false;
		}
	}

	ifPalindrome = true;




	// ==============================================================================

	return 0;
}

// 输出什么？请思考什么是医生想看到的内容，什么是开发者需要的。例如视盘分割中的模板，
// 只有开发时需要用，医生则不需要。请选择最重要的内容输出。
//
// 输出格式：同 Solution::parser 类似，该接口本身只能直接传递字符串级的结果。对于
// 分类结果，请用如下格式进行输出：
//		C2 (1) : 0.797799
//		C1 (0) : 0.0811951
//		C4 (3) : 0.0603684
//		C5 (4) : 0.0466736
//		C3 (2) : 0.0139642
// 对于图像级的结果，请用文件形式保存在根目录。
//
// 注意：针对传统方法那种瀑布式的处理流程，如果医生需要中间结果或者调试参数，请
// 编译多个 exe 以便调用。软件只会使用形如"example.exe -i bbb.jpg -input_width 434"
// 的方式进行调用，请自行设计 exe 之间的参数传递方式。如果医生只想看结果，请在一
// 个 exe 中完成所有算法处理，并只输出关键信息。
int Solution::output() {

	// ==============================================================================
	// 判断回文数
	if( ifPalindrome == 1 ) {
		std::cout << "true" << std::endl;
	} else {
		std::cout << "false" << std::endl;
	}




	// ==============================================================================

	return 0;
}


int main( int argc, char* argv[] ) {
	// 你有更好的架构的话，请随意修改。

	Solution *s = new Solution();

	// 参数解析
	if( s->parser( argc, argv ) == -1 ) {
		return -1;
	}

	// 算法主体
	if( s->algorithm() == -1 ) {
		return -1;
	}

	// 输出
	if( s->output() == -1 ) {
		return -1;
	}

	if( s->dev_mode == true ) { // 开发模式：不要闪退。
		Sleep( 1 * 1000 );
	}
	return 0;
}
