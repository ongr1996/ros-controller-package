/*
This source file was written to control Jackal Gazebo by using the keyboard rather than directly using RViz. This code uses the ROS, std_msgs, math, keyboard, and geometry_msgs packages to call various nodes to control the jackal. The user can change the linear and angular velocity of the rover by using the following keyboard keys: Q, W, E, A, S, D, 1, 2, and 3. 
Note: By defining more keys and adding more cases the user can add additional features such as rebinding other keys to allow for slower movement 
Ryan Ong 
 */
// Calling packages / topics that will be used to create the controller
#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <math.h>
#include <keyboard/Key.h>
#include <geometry_msgs/Twist.h>
#define RATE_LOOP 0.1
#define XVEL 1
#define ZVEL 1

// Redefining the keys that were located in the Ros-Keyboard Package
#define Q_KEY 113
#define W_KEY 119
#define E_KEY 101
#define A_KEY 97
#define S_KEY 115
#define D_KEY 100
#define ONE_KEY 49
#define TWO_KEY 50
#define THREE_KEY 51

class test{
	public:
		test();
	private:
        ros::NodeHandle nh;                         //ROS Node Handle
        ros::Subscriber keyup_sub;                  //subscriber for float topic
				ros::Subscriber keydown_sub;                  //subscriber for float topic
				ros::Publisher vel_pub;                   //Publishes float
        ros::Timer timer;                           //ROS timer object

				geometry_msgs::Twist vel;                        //var for float test
        //callback defines
				void keydown_cb(const keyboard::KeyConstPtr& keydown);
		   	void keyup_cb(const keyboard::KeyConstPtr& keyup);
				void timer_cb(const ros::TimerEvent& event);
};
test::test(){
    	timer = nh.createTimer(ros::Duration(RATE_LOOP), &test::timer_cb, this);
			keyup_sub = nh.subscribe<keyboard::Key>("/keyboard/keyup", 1, &test::keyup_cb, this);
			keydown_sub = nh.subscribe<keyboard::Key>("/keyboard/keydown", 1, &test::keydown_cb, this);
			vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
			vel.linear.x=0;
			vel.linear.y=0;
			vel.linear.z=0;
			vel.angular.x=0;
			vel.angular.y=0;
			vel.angular.z=0;
}
void test::timer_cb(const ros::TimerEvent& event){
	vel_pub.publish(vel);
}
void test::keyup_cb(const keyboard::KeyConstPtr& keyup){
    	int x = keyup -> code;
			switch(x){
	         case Q_KEY:
	             break;
	         case W_KEY:
			vel.linear.x=0;
	             break;
	         case E_KEY:
	             break;
	         case A_KEY:
			vel.angular.z=0;
	             break;
	         case S_KEY:
			vel.linear.x=0;
	             break;
	         case D_KEY:
			vel.angular.z=0;
	             break;
	     }
}
void test::keydown_cb(const keyboard::KeyConstPtr& keydown){
	int x = keydown -> code;
	switch(x){
		 case Q_KEY:
		     break;
		 case A_KEY:
		 	vel.angular.z=ZVEL;
		     break;
		 case W_KEY:
		 	vel.linear.x=XVEL;
		     break;
		 case S_KEY:
		 	vel.linear.x=-XVEL;
		     break;
		 case E_KEY:
		     break;
		 case D_KEY:
		 	vel.angular.z=-ZVEL;
		     break;
 }
}
int main(int argc, char **argv){
	ros::init(argc, argv, "test");
	ROS_INFO_STREAM("testTimer Node Active!");
	test t;
	while(ros::ok()){
		ros::spinOnce();
	}
}
