/*
 *程序首先对加载的图像执行向下采样操作形成高斯金字塔
 *之后再利用向下采样得到的图像进行向上采样形成拉普拉斯金字塔
*/

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main()
{
  Mat srcImage = imread("../luna.jpg");

  //判断图像是否加载成功
  if(srcImage.empty())
  {
    cout << "图像加载失败!" << endl;
    return -1;
  }
  else
    cout << "图像加载成功!" << endl << endl;

  namedWindow("原图像", WINDOW_AUTOSIZE);
  imshow("原图像", srcImage);

  //两次向下采样操作分别输出
  Mat pyrDownImage_1, pyrDownImage_2;

  pyrDown(srcImage, pyrDownImage_1);
  namedWindow("向下采样-1", WINDOW_AUTOSIZE);
  imshow("向下采样-1", pyrDownImage_1);

  pyrDown(pyrDownImage_1, pyrDownImage_2);
  namedWindow("向下采样-2", WINDOW_AUTOSIZE);
  imshow("向下采样-2", pyrDownImage_2);

  //利用向下采样的结果进行向上采样操作
  Mat pyrUpImage_1, pyrUpImage_2;

  pyrUp(pyrDownImage_2, pyrUpImage_1);
  namedWindow("向上采样-1", WINDOW_AUTOSIZE);
  imshow("向上采样-1", pyrUpImage_1);

  pyrUp(pyrUpImage_1, pyrUpImage_2);
  namedWindow("向上采样-2", WINDOW_AUTOSIZE);
  imshow("向上采样-2", pyrUpImage_2);

  Mat resizeImage;
  Size sz(cvRound(30),  cvRound(30));

  // 一、 dsize和fx/fy不能同时为0
  // 要么指定好dsize的值，让fx和fy空置直接使用默认值，
  // 就像resize(img, imgDst, Size(30,30));
  // 要么让dsize为0，指定好fx和fy的值，比如fx=fy=0.5，那么就相当于把原图两个方向缩小一倍！
  // 二、插值方法
  // 图像缩放之后，肯定像素要进行重新计算的，就靠这个参数来指定重新计算像素的方式
  // INTER_NEAREST - 最邻近插值
  // INTER_LINEAR - 双线性插值，如果最后一个参数你不指定，默认使用这种方法
  // INTER_AREA - 用像素面积关系重采样
  // resampling using pixel area relation. It may be a preferred method for image decimation, as it gives moire’-free results.
  // But when the image is zoomed, it is similar to the INTER_NEAREST method.
  // 详细参考，里面说的还可以，够入门了 https://zhuanlan.zhihu.com/p/38493205
  // INTER_CUBIC - 4x4像素邻域内的双立方插值
  // INTER_LANCZOS4 - 8x8像素邻域内的Lanczos插值
  resize(srcImage, resizeImage, sz, 0, 0, INTER_LINEAR);
  namedWindow("resize", WINDOW_AUTOSIZE);
  imshow("resize", resizeImage);

  waitKey(0);

  return 0;
}