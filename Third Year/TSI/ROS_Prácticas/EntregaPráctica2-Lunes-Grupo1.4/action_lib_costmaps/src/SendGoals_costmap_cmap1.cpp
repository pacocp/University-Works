#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
//gestion de costmaps
#include "tf/transform_listener.h"
#include "costmap_2d/costmap_2d_ros.h"
#include <costmap_2d/costmap_2d.h>


#include <boost/thread.hpp>



typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

//imprime en pantalla el contendio de un costmap
void printCostmap (costmap_2d::Costmap2DROS * costmap_ros) {
        //typedef basic_string<unsigned char> ustring;


        costmap_2d::Costmap2D *costmap;
        costmap = costmap_ros->getCostmap();

        for (int x=0; x < costmap->getSizeInCellsX(); x++)
                for (int y= 0; y < costmap->getSizeInCellsY(); y++) {
                        std::cout << (int) costmap->getCost(x,y) << " ";
                }
}


//
//  /*******************************************************************************
// * Function Name: findFreeNeighborCell
//  * Inputs: the row and columun of the current Cell
//  * Output: a vector of free neighbor cells of the current cell
//  * Description:it is used to find the free neighbors Cells of a the current Cell in the grid
//  * Check Status: Checked by Anis, Imen and Sahar
//*********************************************************************************/
std::vector <unsigned int> findFreeNeighborCell (unsigned int CellID, costmap_2d::Costmap2D *costmap){
//
        unsigned int mx, my;
        //convertir el índice de celda en coordenadas del costmap
        costmap->indexToCells(CellID,mx,my);
        ROS_INFO("CellID = %d, mx = %d, my= %d", CellID, mx, my);
        std::vector <unsigned int>  freeNeighborCells;

        for (int x=-1; x<=1; x++)
                for (int y=-1; y<=1; y++) {
                        //comprobar si el índice es válido
                        if ((mx+x>=0)&&(mx+x < costmap->getSizeInCellsX())&&(my+y >=0 )&&(my+y < costmap->getSizeInCellsY())) {

                                ROS_WARN("Index valid!!!!! costmap[%d,%d] = %d", mx+x,my+y,costmap->getCost(mx,my));
                                if(costmap->getCost(mx+x,my+y) == costmap_2d::FREE_SPACE   && (!(x==0 && y==0))) {
                                        unsigned int index = costmap->getIndex(mx+x,my+y);
                                        ROS_INFO("FREECELL: %d con valor %d", index, costmap_2d::FREE_SPACE);
                                        freeNeighborCells.push_back(index);
                                }
                                else {
                                        unsigned int index = costmap->getIndex(mx+x,my+y);
                                        ROS_INFO("OCCUPIEDCELL: %d con valor %d", index, costmap->getCost(mx+x,my+y));
                                }
                        }
                }
        return freeNeighborCells;

}
//función para rellenar una PoseStamped a partir de las coordenadas del mundo obtenidas del costmap.

void rellenaPoseStamped (double wx, double wy, geometry_msgs::PoseStamped &pose, costmap_2d::Costmap2DROS *costmap){

        pose.header.stamp =  ros::Time::now();
        //el marco de coordendas de la posición debe ser el mismo frame que el del goal y este, a su vez, el mismo que el del costmap, por defecto debe tenerlo
        pose.header.frame_id = costmap->getGlobalFrameID();
        pose.pose.position.x = wx;
        pose.pose.position.y = wy;
        pose.pose.position.z = 0.0;
        pose.pose.orientation.x = 0.0; //la orientación en principio no interesa.
        pose.pose.orientation.y = 0.0;
        pose.pose.orientation.z = 0.0;
        pose.pose.orientation.w = 1.0;
}

bool localPlanner(const geometry_msgs::PoseStamped& start, const geometry_msgs::PoseStamped& goal, std::vector<geometry_msgs::PoseStamped>& plan, costmap_2d::Costmap2DROS *costmap_ros){


        ROS_INFO("localPlanner: Got a start: %.2f, %.2f, and a goal: %.2f, %.2f", start.pose.position.x, start.pose.position.y, goal.pose.position.x, goal.pose.position.y);

        plan.clear();
        costmap_2d::Costmap2D *costmap = costmap_ros->getCostmap();

        //pasamos el goal y start a coordenadas del costmap
        double goal_x = goal.pose.position.x;
        double goal_y = goal.pose.position.y;
        unsigned int mgoal_x, mgoal_y;
        //transformamos las coordenadas del mundo a coordenadas del costmap
        costmap->worldToMap(goal_x,goal_y,mgoal_x, mgoal_y);
        if ((mgoal_x>=0)&&(mgoal_x < costmap->getSizeInCellsX())&&(mgoal_y>=0 )&&(mgoal_y < costmap->getSizeInCellsY()))
                unsigned int indice_goal = costmap->getIndex(mgoal_x, mgoal_y);
        else ROS_WARN("He recibido unas coordenadas del mundo para el objetivo que está fuera de las dimensiones del costmap");

        //transformamos las coordenadas de la posición inicial a coordenadas del costmap.
        double start_x = start.pose.position.x;
        double start_y = start.pose.position.y;
        unsigned int mstart_x, mstart_y;
        costmap->worldToMap(start_x,start_y, mstart_x, mstart_y);
        unsigned int start_index = costmap->getIndex(mstart_x, mstart_y);


        //*************************************************************************
        // ya tenemos transformadas las coordenadas del mundo a las del costmap,
        // ahora hay que implementar la búsqueda de la trayectoria, a partir de aquí.
        //*************************************************************************
        //calcular la ruta leyendo del costmap y evaluando las celdas mas bajas (las de menos peligro)
        double x, y;
        geometry_msgs::PoseStamped position;
        for (int i = (int) start_y - 1; i < costmap->getSizeInCellsY(); i++) {
                int coste=1000;
                int equis;
                for (int j = 0; j < costmap->getSizeInCellsX(); j++) {
                        int aux = costmap->getCost(i, j);
                        if(coste > aux) {
                                coste = aux;
                                equis = j;
                        }
                }
                costmap->mapToWorld(i, equis, x, y);
                position.pose.position.x = x;
                position.pose.position.y = y;
                plan.push_back(position);
        }
}

//consultado en http://wiki.ros.org/actionlib_tutorials/Tutorials/SimpleActionClient%28Threaded%29

void spinThread()
{
        ros::spin();
}

int main(int argc, char** argv) {

        ros::init(argc,argv, "send_goals_node");
        //el cliente usará un costmap local para poder tener una representación del entorno
        //en su vecindad próxima.
        tf::TransformListener tf(ros::Duration(10));
        costmap_2d::Costmap2DROS* localcostmap = new costmap_2d::Costmap2DROS("local_costmap", tf);
        costmap_2d::Costmap2DROS* globalcostmap = new costmap_2d::Costmap2DROS("global_costmap", tf);

        //detener el funcionamiento de los costmaps hasta que estemos conectados con el servidor.

        localcostmap->pause();
        globalcostmap->pause();

        //costmap_2d::Costmap2DROS globalcostmap("global_costmap", tf);


        //crear el "action client"
        // true hace que el cliente haga "spin" en su propia hebra
        //Ojo: "move_base" puede ser cualquier string, pero hay que pensarlo como un "published topic". Por tanto, es importante que
        // el action server con el que va a comunicar tenga el mismo topic. E.d., al llamar a "as(n,string,....)" en el lado del
        // action server hay que usar el mismo string que en el cliente.
        MoveBaseClient ac("mi_move_base", true); //<- poner "mi_move_base" para hacer mi propio action server.

        //creamos una hebra para que ros::spin se haga en paralelo y no interrumpa el procesamiento del cliente.
        //ros::spin es necesario para que los costmaps se actualicen adecuadamente.
        boost::thread spin_thread(&spinThread);

        //Esperar 60 sg. a que el action server esté levantado.
        ROS_INFO("Esperando a que el action server move_base se levante");
        //si no se conecta, a los 60 sg. se mata el nodo.
        ac.waitForServer(ros::Duration(60));

        ROS_INFO("Conectado al servidor mi_move_base");

        //Arrancar los costmaps una vez que estamos conectados al servidor
        localcostmap->start();
        globalcostmap->start();
        printCostmap(localcostmap);
        costmap_2d::Costmap2D *micostmap = localcostmap->getCostmap();
        std::vector<unsigned int> vecinas = findFreeNeighborCell(1096,micostmap);
	      std::vector<geometry_msgs::PoseStamped> plan;
        move_base_msgs::MoveBaseFeedbackConstPtr feedback;

        //ros::spin();

        move_base_msgs::MoveBaseGoal goal;

        goal.target_pose.header.frame_id =  "map";
        goal.target_pose.header.stamp = ros::Time::now();

        goal.target_pose.pose.position.x =  0.00; //-18.174;
        goal.target_pose.pose.position.y =  0.00; //25.876;
        goal.target_pose.pose.orientation.w = 1;

        //leer el feedback para saber la posicion inicial del robot

        geometry_msgs::PoseStamped start, goalLocalPlanner;
        start.pose.position.x = feedback->base_position.pose.position.x;
        start.pose.position.y = feedback->base_position.pose.position.y;

        goalLocalPlanner.pose.position.x = goal.target_pose.pose.position.x;
        goalLocalPlanner.pose.position.y = goal.target_pose.pose.position.y;

	//obtener posicion del robot al inicio
	localPlanner(start, goalLocalPlanner, plan, localcostmap);

	for(int i=0; i < plan.size(); i++){
		goal.target_pose.pose.position.x = plan[i].pose.position.x;
		goal.target_pose.pose.position.y = plan[i].pose.position.y;

		ac.sendGoal(goal);
		ac.waitForResult();

    if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
            ROS_INFO("Completada la fase %d del plan.", i);
    else ROS_INFO("Se ha fallado por alguna razón.");



	}

        //ROS_INFO("Enviando el objetivo");
        //ac.sendGoal(goal);


        //Esperar al retorno de la acción
        ROS_INFO("Esperando al resultado  de la acción");
        ac.waitForResult();


        // shutdown the node and join the thread back before exiting
        ros::shutdown();
        spin_thread.join();


        return 0;

}
