///////////////////////////////////////////////////////////////////////////////
//
// wxFormBuilder - A Visual Dialog Editor for wxWidgets.
// Copyright (C) 2005 Jos� Antonio Hurtado
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//
// Written by
//   Jos� Antonio Hurtado - joseantonio.hurtado@gmail.com
//   Juan Antonio Ortega  - jortegalalmolda@gmail.com
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __OBJECT_TREE__
#define __OBJECT_TREE__

#include "rad/appobserver.h"
#include "rad/guirad.h"
#include "model/objectbase.h"
//#include <hash_map>
#include <map>
#include "rad/customkeys.h"

class ObjectTree : public DataObserver, public ObjectTreeGUI
{
 private:
   typedef map<PObjectBase, wxTreeItemId> ObjectItemMap;
   typedef map<string, int> IconIndexMap;
   typedef map<PObjectBase, bool> ItemExpandedMap;
   
   ObjectItemMap m_map;
   ItemExpandedMap m_expandedMap;
   
   wxImageList *m_iconList;
   IconIndexMap m_iconIdx;
   
   /**
    * Crea el arbol completamente.
    */
   void RebuildTree();
   void AddChildren(PObjectBase child, wxTreeItemId &parent, bool is_root = false);
   int GetImageIndex (string type);
   void UpdateItem(wxTreeItemId id, PObjectBase obj);
   
   void SaveItemStatus(PObjectBase obj);
   void RestoreItemStatus(PObjectBase obj);
   
   DECLARE_EVENT_TABLE()
   
 public:
  ObjectTree(wxWindow *parent, int id);
  void Create();
  
  void OnSelChanged(wxTreeEvent &event);
  void OnRightClick(wxTreeEvent &event);
   
  void ProjectLoaded();
  void ProjectSaved();
  void ObjectSelected(PObjectBase obj);
  void ObjectCreated(PObjectBase obj);
  void ObjectRemoved(PObjectBase obj);
  void PropertyModified(PProperty prop);
  void ProjectRefresh();
  
  void AddCustomKeysHandler(CustomKeysEvtHandler *h) { m_tcObjects->PushEventHandler(h); };
};

/**
 * Gracias a que podemos asociar un objeto a cada item, esta clase nos va
 * a facilitar obtener el objeto (ObjectBase) asociado a un item para 
 * seleccionarlo pinchando en el item.
 */
class ObjectTreeItemData : public wxTreeItemData
{
 private:
  PObjectBase m_object;   
 public:
  ObjectTreeItemData(PObjectBase obj);
  PObjectBase GetObject() { return m_object; }
};

/**
 * Menu popup asociado a cada item del arbol.
 *
 * Este objeto ejecuta los comandos incluidos en el menu referentes al objeto
 * seleccionado.
 */
class ItemPopupMenu : public wxMenu
{
 private:
  DataObservable *m_data;
  PObjectBase m_object;
  
  DECLARE_EVENT_TABLE()
     
 public:
  void OnUpdateEvent(wxUpdateUIEvent& e);
  ItemPopupMenu(DataObservable *data, PObjectBase obj);
  void OnMenuEvent (wxCommandEvent & event);
};
 
#endif //__OBJECT_TREE__
