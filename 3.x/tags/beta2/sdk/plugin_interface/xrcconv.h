///////////////////////////////////////////////////////////////////////////////
//
// wxFormBuilder - A Visual Dialog Editor for wxWidgets.
// Copyright (C) 2005 José Antonio Hurtado
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
//   José Antonio Hurtado - joseantonio.hurtado@gmail.com
//   Juan Antonio Ortega  - jortegalalmolda@gmail.com
//
///////////////////////////////////////////////////////////////////////////////

#include "wx/wx.h"
#include "component.h"
#include "tinyxml.h"

#define XRC_TYPE_TEXT    0
#define XRC_TYPE_INTEGER 1
#define XRC_TYPE_BOOL    2
#define XRC_TYPE_COLOUR  3
#define XRC_TYPE_FONT    4
#define XRC_TYPE_BITLIST 5
#define XRC_TYPE_SIZE    6
#define XRC_TYPE_POINT   7
#define XRC_TYPE_STRINGLIST 8
#define XRC_TYPE_BITMAP  9

/**
 * Filtro para exportar un objeto a formato XRC.
 *
 * Esta clase sirve de ayuda para exportar un objeto a formato XRC, tan sólo
 * hay que configurar el "mapeado" de los nombres de las propiedades con su tipo
 * y se creará el elemento XML en formato XRC.
 *
 * Por ejemplo:
 *
 * @code
 *  ...
 *  ObjectToXrcFilter xrc(obj, "wxButton", "button1");
 *  xrc.AddProperty("label", "label", XRC_TYPE_STRING);
 *  xrc.AddProperty("style", "style", XRC_TYPE_BITLIST);
 *  xrc.AddProperty("default", "default", XRC_TYPE_BOOL);
 *  TiXmlElement *xrcObj = xrc.GetXrcObject();
 * @endcode
 */
class ObjectToXrcFilter
{
 public:
  ObjectToXrcFilter(IObject *obj,
                    const wxString &classname,
                    const wxString &objname = wxT(""),
                    const wxString &base = wxT(""));

  ~ObjectToXrcFilter();

  void AddProperty (const wxString &objPropName,
                    const wxString &xrcPropName,
                    const int &propType);

  void AddPropertyValue (const wxString &xrcPropName,
                         const wxString &xrcPropValue);

  void AddWindowProperties();

  TiXmlElement* GetXrcObject();

 private:
  TiXmlElement *m_xrcObj;
  IObject *m_obj;

  void LinkText(const wxString &text, TiXmlElement *propElement, bool xrcFormat = false);
  void LinkColour(const wxColour &colour, TiXmlElement *propElement);
  void LinkFont(const wxFont &font, TiXmlElement *propElement);
  void LinkInteger(const int &integer, TiXmlElement *propElement);
  void LinkStringList(const wxArrayString &array, TiXmlElement *propElement,  bool xrcFormat = false);
};

/**
 * Filtro para exportar un objeto de formato XRC a formato XFB (Xml-FormBuilder)
 *
 * La forma de uso es muy similar al filtro ObjectToXrcFilter, basta con ir
 * añadiendo las propiedades con su tipo.
 *
 */
class XrcToXfbFilter
{
 public:

  XrcToXfbFilter(TiXmlElement *obj,
                 const wxString &classname);

  XrcToXfbFilter(TiXmlElement *obj,
                 const wxString &classname,
                 const wxString &objname);
  ~XrcToXfbFilter();

  void AddProperty (const wxString &xrcPropName,
                    const wxString &xfbPropName, const int &propType);

  void AddPropertyValue (const wxString &xfbPropName,
                         const wxString &xfbPropValue);

  void AddWindowProperties();

  TiXmlElement* GetXfbObject();

 private:
  TiXmlElement *m_xfbObj;
  TiXmlElement *m_xrcObj;

  void ImportTextProperty(const wxString &xrcPropName, TiXmlElement *property, bool parseXrcText = false);
  void ImportIntegerProperty(const wxString &xrcPropName, TiXmlElement *property);
  void ImportBitlistProperty(const wxString &xrcPropName, TiXmlElement *property);
  void ImportBitmapProperty(const wxString &xrcPropName, TiXmlElement *property);
  void ImportColourProperty(const wxString &xrcPropName, TiXmlElement *property);
  void ImportFontProperty(const wxString &xrcPropName, TiXmlElement *property);
  void ImportStringListProperty(const wxString &xrcPropName, TiXmlElement *property, bool parseXrcText = false);

  void AddStyleProperty();

  TiXmlElement *GetXrcProperty(const wxString &name);
};

