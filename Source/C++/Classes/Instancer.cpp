

#include "Classes.h"

void sur::Instancer::Add(void* object, Types type)
{
    switch (type)
    {
    case Types::Rectangle:
        restricted::rectangles->push_back(static_cast<Rectangle*>(object));
        break;
    case Types::Line:
        restricted::lines->push_back(static_cast<Line*>(object));
        break;
    case Types::Object:
        restricted::objects->push_back(static_cast<Object*>(object));
        break;
    case Types::Triangle:
        restricted::triangles->push_back(static_cast<Triangle*>(object));
        break;
    }
}

template <typename RetTy>
RetTy* sur::Instancer::Get(std::string_view name, i32 index)
{
    using namespace sur::Instancer;
    for (i32 i = 0;; i++)
    {
        if (name != "")
        {
            if (typeid(RetTy) == typeid(sur::Rectangle))
                if (i < restricted::rectangles->size())
                {
                    if (name == restricted::rectangles->at(i)->GetName() && restricted::rectangles->at(i)->State())
                        return (RetTy*)restricted::rectangles->at(i);
                }
                else
                    return (RetTy*)restricted::Rdefault;

            if (typeid(RetTy) == typeid(sur::Line))
                if (i < restricted::lines->size())
                {
                    if (name == restricted::lines->at(i)->GetName() && restricted::lines->at(i)->State())
                        return (RetTy*)restricted::lines->at(i);
                }
                else
                    return (RetTy*)restricted::Ldefault;

            if (typeid(RetTy) == typeid(sur::Object))
                if (i < restricted::objects->size())
                {
                    if (name == restricted::objects->at(i)->GetName() && restricted::objects->at(i)->State())
                        return (RetTy*)restricted::objects->at(i);
                }
                else
                    return (RetTy*)restricted::Odefault;

            if (typeid(RetTy) == typeid(sur::Triangle))
                if (i < restricted::triangles->size())
                {
                    if (name == restricted::triangles->at(i)->GetName() && restricted::triangles->at(i)->State())
                        return (RetTy*)restricted::triangles->at(i);
                }
                else
                    return (RetTy*)restricted::Tdefault;

            if (typeid(RetTy) == typeid(sur::Shape))
                if (i < restricted::shapes->size())
                {
                    if (name == restricted::shapes->at(i)->GetName() && restricted::shapes->at(i)->State())
                        return (RetTy*)restricted::shapes->at(i);
                }
                else
                    return (RetTy*)restricted::Sdefault;

            if (typeid(RetTy) == typeid(sur::Triggers::Rectangle))
                if (i < restricted::trigger_rectangles->size())
                {
                    if (name == restricted::trigger_rectangles->at(i)->GetName() && restricted::trigger_rectangles->at(i)->State())
                        return (RetTy*)restricted::trigger_rectangles->at(i);
                }
                else
                    return (RetTy*)restricted::TRdefault;
        }
        else if (index >= 0)
        {
            if (typeid(RetTy) == typeid(sur::Rectangle))
                if (index < restricted::rectangles->size())
                    return (RetTy*)restricted::rectangles->at(index);
                else
                    return (RetTy*)restricted::Rdefault;

            if (typeid(RetTy) == typeid(sur::Line))
                if (index < restricted::lines->size())
                    return (RetTy*)restricted::lines->at(index);
                else
                    return (RetTy*)restricted::Ldefault;

            if (typeid(RetTy) == typeid(sur::Object))
                if (index < restricted::objects->size())
                    return (RetTy*)restricted::objects->at(index);
                else
                    return (RetTy*)restricted::Odefault;

            if (typeid(RetTy) == typeid(sur::Triangle))
                if (index < restricted::triangles->size())
                    return (RetTy*)restricted::triangles->at(index);
                else
                    return (RetTy*)restricted::Tdefault;

            if (typeid(RetTy) == typeid(sur::Shape))
                if (index < restricted::shapes->size())
                    return (RetTy*)restricted::shapes->at(index);
                else
                    return (RetTy*)restricted::Sdefault;

            if (typeid(RetTy) == typeid(sur::Triggers::Rectangle))
                if (index < restricted::trigger_rectangles->size())
                    return (RetTy*)restricted::trigger_rectangles->at(index);
                else
                    return (RetTy*)restricted::TRdefault;
        }
    }
}

template sur::Rectangle* sur::Instancer::Get(std::string_view name, i32 index);
template sur::Line* sur::Instancer::Get(std::string_view name, i32 index);
template sur::Object* sur::Instancer::Get(std::string_view name, i32 index);
template sur::Triangle* sur::Instancer::Get(std::string_view name, i32 index);
template sur::Shape* sur::Instancer::Get(std::string_view name, i32 index);
template sur::Triggers::Rectangle* sur::Instancer::Get(std::string_view name, i32 index);

u32 sur::Instancer::GetCount(Types type)
{
    switch (type)
    {
    case Types::Rectangle:
        return (i32)restricted::rectangles->size();
    case Types::Line:
        return (i32)restricted::lines->size();
    case Types::Object:
        return (i32)restricted::objects->size();
    case Types::Triangle:
        return (i32)restricted::triangles->size();
    case Types::Shape:
        return (i32)restricted::shapes->size();
    case Types::Trigger_Rectangle:
        return (i32)restricted::trigger_rectangles->size();
    default:
        return -1;
    }
}

void sur::Instancer::State(Types type, bool active, std::string_view name, i32 index)
{
    if (type == Types::Rectangle)
        if (name != "")
        {
            for (i32 j = 0; j < restricted::rectangles->size(); ++j)
                if (restricted::rectangles->at(j)->GetName() == name)
                    restricted::rectangles->at(j)->active = active;
        }
        else if (index >= 0)
            restricted::rectangles->at(index)->active = active;
    if (type == Types::Line)
        if (name != "")
        {
            for (i32 j = 0; j < restricted::lines->size(); ++j)
                if (restricted::lines->at(j)->GetName() == name)
                    restricted::lines->at(j)->active = active;
        }
        else if (index >= 0)
            restricted::lines->at(index)->active = active;
    if (type == Types::Object)
        if (name != "")
        {
            for (i32 j = 0; j < restricted::objects->size(); ++j)
                if (restricted::objects->at(j)->GetName() == name)
                    restricted::objects->at(j)->active = active;
        }
        else if (index >= 0)
            restricted::objects->at(index)->active = active;
    if (type == Types::Triangle)
        if (name != "")
        {
            for (i32 j = 0; j < restricted::triangles->size(); ++j)
                if (restricted::triangles->at(j)->GetName() == name)
                    restricted::triangles->at(j)->active = active;
        }
        else if (index >= 0)
            restricted::triangles->at(index)->active = active;
    if (type == Types::Shape)
        if (name != "")
        {
            for (i32 j = 0; j < restricted::shapes->size(); ++j)
                if (restricted::shapes->at(j)->GetName() == name)
                    restricted::shapes->at(j)->active = active;
        }
        else if (index >= 0)
            restricted::shapes->at(index)->active = active;
    if (type == Types::Trigger_Rectangle)
        if (name != "")
        {
            for (i32 j = 0; j < restricted::trigger_rectangles->size(); ++j)
                if (restricted::trigger_rectangles->at(j)->GetName() == name)
                    restricted::trigger_rectangles->at(j)->active = active;
        }
        else if (index >= 0)
            restricted::trigger_rectangles->at(index)->active = active;
}

void sur::Instancer::Delete(Types type, std::string_view name, i32 index)
{
    if (type == Types::Rectangle)
        if (name != "")
        {
            for (i32 j = 0; j < restricted::rectangles->size(); ++j)
                if (restricted::rectangles->at(j)->GetName() == name)
                {
                    restricted::rectangles->erase(restricted::rectangles->begin() + j);
                }
        }
        else if (index >= 0)
            restricted::rectangles->erase(restricted::rectangles->begin() + index);
    if (type == Types::Line)
        if (name != "")
        {
            for (i32 j = 0; j < restricted::lines->size(); ++j)
                if (restricted::lines->at(j)->GetName() == name)
                    restricted::lines->erase(restricted::lines->begin() + j);
        }
        else if (index >= 0)
            restricted::lines->erase(restricted::lines->begin() + index);
    if (type == Types::Object)
        if (name != "")
        {
            for (i32 j = 0; j < restricted::objects->size(); ++j)
                if (restricted::objects->at(j)->GetName() == name)
                {
                    restricted::objects->erase(restricted::objects->begin() + j);
                    if (!restricted::objects->at(j)->parentmem)
                        delete restricted::objects->at(j);
                }
        }
        else if (index >= 0)
            restricted::objects->erase(restricted::objects->begin() + index);
    if (type == Types::Triangle)
        if (name != "")
        {
            for (i32 j = 0; j < restricted::triangles->size(); ++j)
                if (restricted::triangles->at(j)->GetName() == name)
                    restricted::triangles->erase(restricted::triangles->begin() + j);
        }
        else if (index >= 0)
            restricted::triangles->erase(restricted::triangles->begin() + index);
    if (type == Types::Shape)
        if (name != "")
        {
            for (i32 j = 0; j < restricted::shapes->size(); ++j)
                if (restricted::shapes->at(j)->GetName() == name)
                    restricted::shapes->erase(restricted::shapes->begin() + j);
        }
        else if (index >= 0)
            restricted::shapes->erase(restricted::shapes->begin() + index);
    if (type == Types::Trigger_Rectangle)
        if (name != "")
        {
            for (i32 j = 0; j < restricted::trigger_rectangles->size(); ++j)
                if (restricted::trigger_rectangles->at(j)->GetName() == name)
                    restricted::trigger_rectangles->erase(restricted::trigger_rectangles->begin() + j);
        }
        else if (index >= 0)
            restricted::trigger_rectangles->erase(restricted::trigger_rectangles->begin() + index);
}

void sur::Instancer::ClearAll()
{
    for (i32 i = 0; i < restricted::rectangles->size(); ++i)
        delete restricted::rectangles->at(i);
    restricted::rectangles->clear();
    for (i32 i = 0; i < restricted::objects->size(); ++i)
        delete restricted::objects->at(i);
    restricted::objects->clear();
    for (i32 i = 0; i < restricted::lines->size(); ++i)
        delete restricted::lines->at(i);
    restricted::lines->clear();
    for (i32 i = 0; i < restricted::triangles->size(); ++i)
        delete restricted::triangles->at(i);
    restricted::triangles->clear();
    for (i32 i = 0; i < restricted::shapes->size(); ++i)
        delete restricted::shapes->at(i);
    restricted::shapes->clear();
    for (i32 i = 0; i < restricted::trigger_rectangles->size(); ++i)
        delete restricted::trigger_rectangles->at(i);
    restricted::trigger_rectangles->clear();
}
