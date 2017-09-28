#ifndef LOCAL PLANNER_H
#define LOCAL PLANNER_H


#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/Twist.h"
#include <move_base_msgs/MoveBaseAction.h>
#include <vector>

typedef struct tupla {double x; double y; } Tupla;
typedef struct conf {double radius; double spread; double intens; } PFConf;


template <typename T> int signo(T val) {
        return  (val/abs(val));
}

class LocalPlanner
{
public:
        Tupla posGoal;  //Posición del objetivo
        Tupla posGoalOriginal;
        std::vector<Tupla> cola_goals;
        std::vector<Tupla> posiciones;
        Tupla pos;      //Posición actual
        double yaw;     //Angulo (en radianes) de orientación del robot
        Tupla deltaGoal; //Componente del campo atractivo
        Tupla deltaObst; //Componente del campo repulsivo (para todos los obstáculos)
        Tupla delta;    //Componente total
        Tupla deltaAlt;
        double v_angular; //velocidad angular
        double v_lineal;  //velocidad lineal
        std::vector<Tupla> posObs;    //Vector que contiene las posiciones de los obstáculos.
                                      //Calculado en scanCallback.
        nav_msgs::Odometry odometria;      //guarda el último mensaje de odometría recibido

        PFConf CAMPOATT; // = {0.01,3,5,0.07r de posiciones de ob};//Parámetros de configuración (radio, spread, alpha) del campo actractivo.
        PFConf CAMPOREP; //(0,01,1,0,01);//Parámetros de configuración (radio, spread, beta)del campo repulsivo.
        PFConf CAMPOALT;
        const static double TOLERANCIA = 0.009;  //Valor a partir del cual consideramos que el robot está e
        //en la posición objetivo (ver setDeltaAtractivo)
        const static double V_ANGULAR_CTE = M_PI/8;  //Valor de la velocidad angular constante.
        const static double EPSILON_ANGULAR = 0.0009; //Valor a partir del cual entendemos que el robot está en la orientación deseada
        double MIN_SCAN_ANGLE_RAD = -135.0/180*M_PI;
        double MAX_SCAN_ANGLE_RAD = +135.0/180*M_PI;

        LocalPlanner(); //constructor.

        void setGoal(const move_base_msgs::MoveBaseGoalConstPtr& goal) {
                posGoal.x = goal->target_pose.pose.position.x;
                posGoal.y = goal->target_pose.pose.position.y;
        }

        bool goalAchieved();    //Devuelve true cuando se ha alcanzado el objetivo
        void setDeltaAtractivo();
        void getOneDeltaRepulsivo(Tupla posO, Tupla &deltaO);
        void setTotalRepulsivo();
        void setDeltaTotal(){
                if (deltaAlt.x != 0 && deltaAlt.y != 0) {
                  delta.x = deltaAlt.x + deltaObst.x;
                  delta.y = deltaAlt.y + deltaObst.y;
                  deltaAlt.x = deltaAlt.y = 0;
                }else{
                  delta.x = deltaGoal.x + deltaObst.x + deltaAlt.x;
                  delta.y = deltaGoal.y + deltaObst.y + deltaAlt.y;
              }

              ROS_INFO("delta total: %d, %d", delta.x, delta.y);
        };
        void setv_Angular();
        void setv_Lineal();
        double distancia(Tupla src, Tupla dst) {
                return sqrt((src.x - dst.x) * (src.x - dst.x) +
                            (src.y - dst.y) * (src.y - dst.y));
        }
        bool minimoLocal();
        void setMetaAlternativa();
        void escapaMinimoLocal();
        void setSpeed() {
                //rellenar y enviar Twist.
                geometry_msgs::Twist mensajeTwist;
                mensajeTwist.linear.x = v_lineal;
                mensajeTwist.angular.z =v_angular;
                commandPub.publish(mensajeTwist);
        }

protected:
private:
        ros::NodeHandle node;
        ros::Publisher commandPub;  //Publicador de velocidades
        ros::Subscriber laserSub;   //Suscriptor del scan laser
        ros::Subscriber odomSub;    //Suscriptor de la odometría.

        void scanCallBack(const sensor_msgs::LaserScan::ConstPtr& scan);
        void odomCallBack(const nav_msgs::Odometry::ConstPtr& msg);

};

#endif // LOCAL PLANNER_H
