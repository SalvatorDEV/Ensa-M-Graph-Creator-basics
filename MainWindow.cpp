#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QInputDialog>
#include <QtDebug>
#include <sommet.h>

int maxSom=0;
int maxArret=0;
int maxPoid=0;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , my_ui(new Ui::MainWindow)
{
    my_ui->setupUi(this);
    mongraphe = new MainWindow(mascene);
    mascene = new QGraphicsScene();

    mascene->setItemIndexMethod(QGraphicsScene::NoIndex);
    mascene->setSceneRect(-260, -40, 600, 280);
    my_ui->graphicsView->setScene(mascene);
    my_ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    my_ui->graphicsView->setRenderHint(QPainter::HighQualityAntialiasing);
    my_ui->graphicsView->scale(qreal(1), qreal(1));

    setMinimumSize(200, 200);
    setWindowTitle(tr("Graph Creator Basic "));

}
MainWindow::MainWindow(QGraphicsScene *scene) :
    mascene(scene)
{}
int counter=0;
void MainWindow::addNode()

{
    counter++;
    sommet* newNode2 = new sommet(counter);
    //newNode2->number=counter;
    qInfo()<<"sommet valeur iiiis"<<newNode2->number;
    mascene->addItem(newNode2);
   newNode2->setPos(-50,10);
   listeSom.push_back(newNode2);

}
sommet* MainWindow::GetSomById(int id){
    for (int a=0;a<listeSom.size();a++) {
        if((listeSom[a]->number)==id){

        return listeSom[a];}
    }

}

void MainWindow::addEdge(int a,int b ,int c){


     // ajouter une condition if( sommet a different du sommet b)
    edge* newOne = new edge(GetSomById(a),GetSomById(b),c);
    mascene->addItem(newOne);
    listeEdge.push_back(newOne);
    qInfo()<<"le size de la liste edge est "<<listeEdge.size();


}
void MainWindow::randomOne(int som,int aret,int maxP){
    for(int e=0;e<som;e++){
        int x= rand() %  200+ (0);
        int y= rand() %  200+ (0);
        addNode();
        listeSom[e]->setPos(x,y);
    }
    for(int i=0;i<aret;i++){
        int Poi=rand() % maxP;
        //ajouter un while dst est diff de src
        int dst;
        int src;
        do{
         dst=rand() % listeSom.size() + 1 ;
         src=rand() % listeSom.size() + 1 ;}while(dst==src);

        addEdge(src,dst,Poi);

    }
    //  methode pour ne pas generer la meme arete :
    // §§§methode facile mais peut etre lente dans des graphs de tres grande taille >  500 aretes ?
    //on peut faire int  nombreAreteAcreer= aret ;
    //do {....if(cette arret nexiste pas ){ créer cette arete;a--}}while(nombreAreteAcreer != 0);
        // comment savoir si cette arrete existe deja ou pas ? on creera une fonction qui return un bool et qui prend en parametre une arete
        //la fonction : for(i<listeEdge.size()) { if(areteAcreer==listeEdge[i] return false }} return true;
        //pour le == on va ecrire areteAcreer.src.id ==listeEdge[i].src.id && meme chose pour dst ( de preference surchargé le == pour le sommet
        //pour ne pas metre le .id sinon c pas grave mais pour future utilisation dans dautre fonction vaut mieux de le surchargé;
        // !!!!! pour optimisé: si lutilisateur par exemple entre 2 sommets et 1000 aretes on veut comme meme pas boucler sur les 1000 arretes pour
        //un seul graph de 2 sommets cad on va ajouter une autre condition du max de nombre darete que peut avoir un graphe de n sommet;
        // alors si la valeur darrete est plus que le max on va la changer au max .
         //if(le nombre donner d arete par lutilisateur > le maximum possible darrete qu'on peut créer avec le nombre de sommets donné)
        // alors le nombre donner d arete par lutilisateur = le maximum possible darrete qu'on peut créer avec le nombre de sommets donné !!!!
        //§§§ methode un peux plus compliqué mais vraiment plus rapide surtout dans les graphs de grande taille :
            // meme principe que la derniere sauf qu'on va changer la boucle for que pour boucler sur une liste darrete qui ont le sommet 'src'
            // et le sommet 'dst' : pour cela vous devez créer une autre liste darrete dans la classe sommet qui sera la liste des arretes d'un sommet


}



MainWindow::~MainWindow()
{
    delete my_ui;
}


void MainWindow::on_pushButton_clicked()
{
    addNode();
}

void MainWindow::on_pushButton_2_clicked()
{  bool ok=false;
    int  a= QInputDialog::getInt(nullptr,"node src","Quel est l id du source?",1,1,listeSom.size(),1,&ok);
    int b=QInputDialog::getInt(nullptr,"node dest","Quel est l id du destination?",1,1,listeSom.size(),1,&ok);
    int c=QInputDialog::getInt(nullptr,"poid de larete","entrer le poid",1,1,10000,1,&ok);
    addEdge( a, b, c);
}

void MainWindow::on_pushButton_3_clicked()
{   // ajouter des spin box pour savoir les valeurs donner par lutilisateur
    //sinon utiliser la meme methode de bouton d'ajout d'arete mais je vous conseille d'utiliser les spin box c'est plus pratique.
    randomOne(maxSom,maxArret,maxPoid);
}
//exemple de coloration d'un resultat
void MainWindow::colorier(){
    //on veut par exemple colorier les aretes de poids > de 10
    //on utilisera un bool avec la fonction de painter d'arrete
    // dans cette fonction le bool du coloriage va etre true pour chaque arete du resultat et a la fin on va faire appel a update();
    for(int e=0;e<listeEdge.size();e++){

        if(listeEdge[e]->poid>10){

            listeEdge[e]->colorier=true;
            listeEdge[e]->update();

        }
    }

}

void MainWindow::on_pushButton_4_clicked()
{
    colorier();

}


void MainWindow::on_spinBox_valueChanged(int arg1)
{
   maxSom=arg1;
}

void MainWindow::on_spinBox_2_valueChanged(int arg1)
{
    maxArret=arg1;
}

void MainWindow::on_spinBox_3_valueChanged(int arg1)
{
    maxPoid=arg1;
}

void MainWindow::deleteSommet(int id){

    GetSomById(id);

    mascene->removeItem(GetSomById(id));
    listeSom.remove(id-1);
    qInfo()<<"le size de la liste de sommet est "<<listeSom.size();
}

void MainWindow::on_pushButton_5_clicked()
{
    bool ok=false;
        int  id= QInputDialog::getInt(nullptr,"node src","Quel est l id du source?",1,1,listeSom.size(),1,&ok);
        deleteSommet(id);
}
