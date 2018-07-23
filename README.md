# Homework3
Gestione file bag di una scena registrata. Visualizzazione dei punti della scena tramite ORB-SLAM e relativa segmentazione degli oggetti presenti nella scena stessa.

# Corso ciberfisico univr
- Autore: Moreno Bragaglio
- Data: 6/06/2018

# Prerequisiti
Pangolin installato.<br>
Librerie OpenCv installate <br>
ORB_SLAM2 installato <br>

# Esecuzione:
Eseguire il clone della repository tramite "git clone https://github.com/MorenoBragaglio/homework3.git" dalla cartella "catkin_ws/src".<br>
Dalla directory "ORB_SLAM2/pcl/bin" eseguire "./clustering" per visualizzare la nuvola di punti clusterizzata.
Se si vuole eseguire completamente ORB_SLAM è necessario andare nella cartella ORB_SLAM2/src e sostituire il file "System.cc"
scaricato.<br>
In seguito andare nella directory ORB_SLAM2/include ed aggiungere la dichiarazione della funzione "void SaveMapPoints(const string &filename);" nel file "System.h".<br>
Andare nella directory ORB_SLAM2/Examples/ROS/ORB_SLAM2/src ed aggiungere la chiamata a funzione "SLAM.SaveMapPoints("MapPointsSave.txt");" sotto "ros::spin();" nel file ros_stereo.cc.<br>
Una volta volta sostituito tutto andare nella directory ORB_SLAM ed eseguire il comando "./build.sh" e di seguito "./build_ros.sh".<br>
Per eseguire ORB_SLAM2 è necessario lanciare:
- roscore su un terminale.<br>
- rosrun ORB_SLAM2 Stereo Vocabulary/ORBvoc.txt Examples/Stereo/EuRoC.yaml true (su un secondo terminale).<br>
- rosbag play PATH/V1_01_easy.bag /cam0/image_raw:=/camera/left/image_raw /cam1/image_raw:=/camera/right/image_raw (in un terzo terminale, dove PATH va sostituito con il percorso del file .bag, finito di eseguire la bag premere "Ctrl-c" per esportare il file .txt).<br>

Andare nella directory pcl scaricata ed eseguire il comando cmake per convertire il file .txt in .pcd e per compilre il codice per il clustering.<br>
Andare nella cartella pcl/bin ed eseguire "./clustering".<br>

# Progettazione:
Nella progettazione dell'homework3 è stato modificato il codice "System.cc", il quale si trova nella directory src di ORB_SLAM2, introducendo una funzione (void System::SaveMapPoints(const string &filename)) che esporta le coordinate (x,y,z) della nuvola di punti in un file .txt.<br>
Di seguito è stato implementato un codice "xyzTopcd.cpp" che converte il file .txt in .pcd.<br>
Infine sono stati modificati i parametri del file "clustering.cpp" in modo tale da rappresentare al meglio le nuvole di punti.<br>

# Immagini dimostrative:

![alt text](https://github.com/MorenoBragaglio/homework3/blob/master/Image/ORB_SLAM2.png)
Esecuzione di ORB_SLAM2 con la bag "V1_01_easy.bag".<br>
![alt text](https://github.com/MorenoBragaglio/homework3/blob/master/Image/Clustering_0.2.png)
Cluster di punti con tolleranza 0.2.<br>
![alt text](https://github.com/MorenoBragaglio/homework3/blob/master/Image/clustering_0.15.png)
Cluster di punti con tolleranza 0.15.<br>
