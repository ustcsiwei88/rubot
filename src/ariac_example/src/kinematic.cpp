#include<iostream>
#include<vector>
#include<cmath>
#include<Eigen/Dense>

using namespace Eigen;
using namespace std;

double PI = std::acos(-1);
std::vector<double> a{0, -0.612, -0.5723, 0, 0, 0};
std::vector<double> d{0.1273, 0, 0, 0.163941, 0.1157, 0.0922};
std::vector<double> alpha{PI/2, 0, 0, PI/2, -PI/2, 0};

vector<double> kinematic(vector<double> theta){
	Matrix4d Z[6];
	Matrix4d X[6];
	for(int i=0; i<6; i++){
		Z[i] << cos(theta[i]), -sin(theta[i]), 0, 0, sin(theta[i]), cos(theta[i]),
				0, 0, 0, 0, 1, d[i], 0, 0, 0, 1;
		X[i] << 1, 0, 0, a[i], 0, cos(alpha[i]), -sin(alpha[i]), 0,
				0, sin(alpha[i]), cos(alpha[i]), 0, 0, 0, 0, 1;
	}
	Matrix4d res = Z[0]*X[0];
	for(int i=1; i<6; i++){
		res *= Z[i] * X[i];
	}
	//std::cout << res << std::endl;
	return vector<double>{res(0,3), res(1,3), res(2,3)};
}

vector<double> invkinematic(vector<double> pose){
	
	double x=-pose[1], y=-pose[0];
	double h=pose[2]-d[0]+d[5];

	double tmp1 = sqrt(x*x + y*y - d[3]*d[3]);
	double tmp = sqrt(pow(tmp1 - d[4],2) + h*h);
	vector<double> theta(6,0);
	if(y>=0){
		theta[0] = (y==0? PI/2:atan(x/y)) + atan(d[3]/tmp1) + PI;
		theta[1] = -PI+(asin(h/tmp) + acos(-(a[1]*a[1]+tmp*tmp-a[2]*a[2])/(2*a[1]*tmp)));
		theta[2] = - PI + acos((a[1]*a[1]+a[2]*a[2]-tmp*tmp)/(2*a[1]*a[2]));
		theta[3] = acos(h/tmp) + acos(-(a[2]*a[2]+tmp*tmp-a[1]*a[1])/(2*a[2]*tmp)) - PI;
		theta[4] = PI/2;
		if(theta[0]>PI) theta[0]-=2*PI;
		theta[5] = theta[0];
	}
	else{
		y=-y;
		theta[0] = -(atan(x/y)) + atan(d[3]/tmp1);
		theta[1] = -PI+(asin(h/tmp) + acos(-(a[1]*a[1]+tmp*tmp-a[2]*a[2])/(2*a[1]*tmp)));
		theta[2] = - PI + acos((a[1]*a[1]+a[2]*a[2]-tmp*tmp)/(2*a[1]*a[2]));
		theta[3] = acos(h/tmp) + acos(-(a[2]*a[2]+tmp*tmp-a[1]*a[1])/(2*a[2]*tmp)) - PI;
		theta[4] = PI/2;
		if(theta[0]>PI) theta[0]-=2*PI;
		theta[5] = theta[0];
	}
	#if 0
	double tmp1 = sqrt(x*x + y*y - d[3]*d[3]);
	double tmp = sqrt(pow(tmp1 + d[4],2) + h*h);
	vector<double> theta(6,0);
	if(y>=0){
		theta[0] = (y==0? PI/2:atan(x/y)) - atan(d[3]/tmp1);
		theta[1] = -(asin(h/tmp) + acos(-(a[1]*a[1]+tmp*tmp-a[2]*a[2])/(2*a[1]*tmp)));
		theta[2] = PI - acos((a[1]*a[1]+a[2]*a[2]-tmp*tmp)/(2*a[1]*a[2]));
		theta[3] = PI - acos(h/tmp) - acos(-(a[2]*a[2]+tmp*tmp-a[1]*a[1])/(2*a[2]*tmp));
		theta[4] = PI/2;
	}
	else{
		y=-y;
		theta[0] = -(atan(x/y)) - atan(d[3]/tmp1) + PI;
		theta[1] = -(asin(h/tmp) + acos(-(a[1]*a[1]+tmp*tmp-a[2]*a[2])/(2*a[1]*tmp)));
		theta[2] = PI - acos((a[1]*a[1]+a[2]*a[2]-tmp*tmp)/(2*a[1]*a[2]));
		theta[3] = PI - acos(h/tmp) - acos(-(a[2]*a[2]+tmp*tmp-a[1]*a[1])/(2*a[2]*tmp));
		theta[4] = PI/2;
	}
	#endif
	// for(auto i: theta){
	// 	cout<<i<<endl;
	// }

	return theta;
}

vector<double> invkinematic_belt(vector<double> pose){
	
	double x=-pose[1], y=-pose[0];
	double h=pose[2]-d[0]+d[5];


	double tmp1 = sqrt(x*x + y*y - d[3]*d[3]);
	double tmp = sqrt(pow(tmp1 + d[4],2) + h*h);
	vector<double> theta(6,0);
	if(y>=0){
		theta[0] = (y==0? PI/2:atan(x/y)) - atan(d[3]/tmp1);
		theta[1] = -(asin(h/tmp) + acos(-(a[1]*a[1]+tmp*tmp-a[2]*a[2])/(2*a[1]*tmp)));
		theta[2] = PI - acos((a[1]*a[1]+a[2]*a[2]-tmp*tmp)/(2*a[1]*a[2]));
		theta[3] = PI - acos(h/tmp) - acos(-(a[2]*a[2]+tmp*tmp-a[1]*a[1])/(2*a[2]*tmp));
		theta[4] = PI/2;
		theta[5] = theta[0];
	}
	else{
		y=-y;
		theta[0] = -(atan(x/y)) - atan(d[3]/tmp1) + PI;
		theta[1] = -(asin(h/tmp) + acos(-(a[1]*a[1]+tmp*tmp-a[2]*a[2])/(2*a[1]*tmp)));
		theta[2] = PI - acos((a[1]*a[1]+a[2]*a[2]-tmp*tmp)/(2*a[1]*a[2]));
		theta[3] = PI - acos(h/tmp) - acos(-(a[2]*a[2]+tmp*tmp-a[1]*a[1])/(2*a[2]*tmp));
		theta[4] = PI/2;
		theta[5] = theta[0];
	}
	// for(auto i: theta){
	// 	cout<<i<<endl;
	// }

	return theta;
}

/*

#ifndef MAIN_FILE
#define MAIN_FILE


int main(){
	double x,y,z;
	cin>>x>>y>>z;
	auto res1 = invkinematic(vector<double>{x, y, z});
	auto res = kinematic(res1);
	for(auto i:res1)cout<<i<<" ";
		cout<<endl;
	for(auto i:res)cout<<i<<" ";
		cout<<endl;

	//invkinematic(res);
	return 0;
}

#endif
*/