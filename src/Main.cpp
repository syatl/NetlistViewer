#include <string>
#include <sstream>
#include <iostream>
#include <memory>

using namespace std;

#include <QApplication>
#include <QtGui>

#include "Cell.h"
#include "CellViewer.h"

using namespace Netlist;


int main ( int argc, char* argv[] )
{
  cout << "Chargement des modeles..." << endl;
  Cell::load( "vdd" );
  Cell::load( "gnd" );
  Cell::load( "TransistorN" );
  Cell::load( "TransistorP" );
  Cell::load( "and2" );
  Cell::load( "or2" );
  Cell::load( "xor2" );
  Cell::load( "halfadder");
  Cell::load( "fulladder");

  QApplication* qa = new QApplication(argc, argv);

  CellViewer* viewer = new CellViewer ();

  viewer ->show ();

  int rvalue = qa ->exec ();
  delete qa;
  return rvalue;
}
