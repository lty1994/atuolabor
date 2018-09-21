#ifndef KEYBOARD_CONTROL_NODE_H
#define KEYBOARD_CONTROL_NODE_H

#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

//input_event键值重定义
#define KEYBOARD_UP     103
#define KEYBOARD_DOWN   108
#define KEYBOARD_LEFT   105
#define KEYBOARD_RIGHT  106

#define KEYBOARD_1      2
#define KEYBOARD_2      3
#define KEYBOARD_3      4
#define KEYBOARD_4      5
#define KEYBOARD_9      10
#define KEYBOARD_0      11

namespace autolabor_tool {//节点消息的封装
class KeyboardControl
{
public:
  KeyboardControl();
  ~KeyboardControl();

  void run();
private:
  ros::NodeHandle nh_;//实例化节点
  ros::Publisher twist_pub_;//实例化发布话题
  ros::Timer twist_pub_timer_;//发布时间频率

  int fd_; //上下文
  struct input_event ev_; //实例化关键结构体,定义了键盘输入

  int linear_state_, angular_state_;

  std::string port_name_;
  double rate_;//话题发布频率
  double linear_scale_, angular_scale_;
  double linear_min_, linear_max_, linear_step_;
  double angular_min_, angular_max_, angular_step_;
  bool send_flag_;

  bool init();
  void parseKeyboard();
  void twistCallback(const ros::TimerEvent&);
  void buttonTwistCheck(int value, int& state, int down, int up);
  void buttonScaleCheck(int value, double& scale, double step, double limit);
};

}

#endif // KEYBOARD_CONTROL_NODE_H
