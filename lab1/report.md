## 算法基础project1-实验报告

##### 廖佳怡PB19151776

### 1. 实验设备和环境



### 2. 实验内容及要求



### 3. 方法和步骤



### 4. 结果与分析

#### exp1

1. 最优链乘方案及最少乘法运算次数

2. 运行时间的曲线分析

   * 时间复杂度理论分析：

     由于MATRIX-CHAIN-ORDER包含三重for循环，每层的循环变量（l、i和k）最多取n-1个值，可知算法运行时间为$O(n^3)$。

     又最内层循环体内容的运行时间为$\Omega(1)$​​​​​的，故总运行时间为$\sum_{l=2}^{n}\sum_{i=1}^{n-l+1}\sum_{k=i}^{i+l-2}\Omega(1)=\sum_{l=2}^{n}\sum_{i=1}^{n-l+1}\Omega(l-1)=\sum_{l=2}^{n}\Omega((n-l+1)(l-1))=\Omega({\frac{n^3-n}{6}})$​​​可知运行时间为$\Omega(n^3)$​​​​​的。

     故得到算法运行时间为$\Theta(n^3)$的。

   * 运行时间的折线图如下：

   ![image-20211118091318349](C:\Users\广羽川人\AppData\Roaming\Typora\typora-user-images\image-20211118091318349.png)

   * 再画出time与$n^3$的散点图，由趋势线可知time与$n^3$呈线性关系，即符合$\Theta (n^3)$的时间复杂度理论分析。

   ![image-20211118092437537](C:\Users\广羽川人\AppData\Roaming\Typora\typora-user-images\image-20211118092437537.png)

3. n=5时的结果截图

   ![image-20211118090555923](C:\Users\广羽川人\AppData\Roaming\Typora\typora-user-images\image-20211118090555923.png)

#### exp2

