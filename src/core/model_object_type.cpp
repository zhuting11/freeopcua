/******************************************************************************
 *   Copyright (C) 2013-2014 by Alexander Rykovanov                        *
 *   rykovanov.as@gmail.com                                                   *
 *                                                                            *
 *   This library is free software; you can redistribute it and/or modify     *
 *   it under the terms of the GNU Lesser General Public License as           *
 *   published by the Free Software Foundation; version 3 of the License.     *
 *                                                                            *
 *   This library is distributed in the hope that it will be useful,          *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of           *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            *
 *   GNU Lesser General Public License for more details.                      *
 *                                                                            *
 *   You should have received a copy of the GNU Lesser General Public License *
 *   along with this library; if not, write to the                            *
 *   Free Software Foundation, Inc.,                                          *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.                *
 ******************************************************************************/

#include "model_impl.h"

#include <opc/ua/model.h>

namespace OpcUa
{
  namespace Model
  {

    ObjectType::ObjectType(NodeID objectId, Services::SharedPtr services)
      : Node(services)
    {
      Id = objectId;
      ReadParameters attrs;
      attrs.AttributesToRead.push_back(AttributeValueID(objectId, AttributeID::DISPLAY_NAME));
      attrs.AttributesToRead.push_back(AttributeValueID(objectId, AttributeID::BROWSE_NAME));
      attrs.AttributesToRead.push_back(AttributeValueID(objectId, AttributeID::IS_ABSTRACT));
      std::vector<DataValue> values = services->Attributes()->Read(attrs);
      DisplayName = values[0].Value.As<LocalizedText>();
      BrowseName = values[1].Value.As<QualifiedName>();
      Abstract = values[2].Value.As<bool>();
    }

    bool ObjectType::IsAbstract() const
    {
      return false;
    }

    std::vector<Variable> ObjectType::Variables() const
    {
      return Browse<Variable>(GetID(), NODE_CLASS_VARIABLE, GetServices());
    }

    std::vector<Object> ObjectType::Objects() const
    {
      return Browse<Object>(GetID(), NODE_CLASS_OBJECT, GetServices());
    }

    std::vector<ObjectType> ObjectType::SubTypes() const
    {
      return Browse<ObjectType>(GetID(), NODE_CLASS_OBJECT_TYPE, GetServices());
    }

    ObjectType ObjectType::Parent() const
    {
      return ObjectType(ObjectID::Null, GetServices());
    }

  }
}
