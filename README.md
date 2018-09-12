# MIPID 算法接口标准模板

MIPID 框架下所有算法都将采用该接口以便主程序调用。算法编译成`exe`后再由软件调用，这样算法与软件之间的关系类似于电路元件与芯片，凡是符合该接口模板的 `exe `都可以自由替换。需要修改算法时，只需用新的 `exe `替换旧的即可。这样跳过了重新编译软件的步骤，后续维护极其方便。开发者之间各司其职，只用维护自己的源码，最后在`exe `的级别上由 [Sandiagal](https://github.com/Sandiagal) 进行汇总。软件开源的同时，算法依旧闭源，既维护了专利持有者的权利，也迎合了开源共享的趋势。

## 下载

- 通过[releases](https://github.com/Sandiagal/MIPID_API_example/releases)下载完成内容，包括接口源码和测试平台，首次下载请用该方法。

- 使用`git`命令更新接口源码，只包含一个cpp文件，后续维护请用该方法。

    ```powershell
    git clone https://github.com/Sandiagal/MIPID_API_example.git
    ```

## 接口源码

该模板包括一个 Solution 类，用于封装所有算法。Solution 内包含了3大主要函数。Solution::parser 用于对命令行模式下的参数进行解析，已经包含了常见的数据结构的操作范例。Solution::algorithm 和 Solution::output 是算法的主体和输出，已经基于 [LeetCode 9 回文数](https://leetcode-cn.com/problems/palindrome-number/description/) 做出了算法级范例。题目为：判断一个整数是否是回文数。回文数是指正序（从左向右）和倒序（从右向左）读都是一样的整数。例121是回文数，-121不是。

Debug：该接口需要外部输入参数，你可以使用编译器的"命令参数"来模拟输入。该设置在MSVC2015中位于项目属性页的“调试”中。注意 C++ 11 标准会用空格分割字符串，请不要使用带空格的路径的文件名。在必要时请用"image size"的方式保护空格。最后发给 [Sandiagal](https://github.com/Sandiagal) 的文件请用 Release x64 的方式进行编译。

dev_mode：相信你们发给我的 exe 已经通过了自己的测试，但在实际运行中还会出现意外问题。而该软件架构是不能对编译后 exe 进行 debug 的，所以请参照文中 dev_mode 的方法，在关键位置输出内部信息，以便排查 bug。

如果你有更好的建议，欢迎上传自己的模板。

## 测试平台

已经包含所有运行库，只要是符合接口源码模式的`exe`都能用该平台进行测试。

应该具备了足够的自明性，先不详细介绍了。

请通过了该平台测试后，再将`exe`发给 [Sandiagal](https://github.com/Sandiagal) 。



