#ifndef CALLBACK_H
#define CALLBACK_H

template <class Object, typename ReturnType, typename Parameter>
class Callback
{
private:
    typedef ReturnType (Object::*Method)(Parameter);
    Object *class_instance;
    Method method;
public:
    Callback(Object *_class_instance, Method _method);
    ReturnType operator () (Parameter parameter);
    ReturnType execute(Parameter parameter);
};

template <class Object, typename ReturnType, typename Parameter>
Callback<Object, ReturnType, Parameter>::Callback(Object *_class_instance, Method _method) :
    class_instance(_class_instance),
    method(_method)
{
}

template <class Object, typename ReturnType, typename Parameter>
ReturnType Callback<Object, ReturnType, Parameter>::operator () (Parameter parameter)
{
    return (class_instance->*method)(parameter);
}


template <class Object, typename ReturnType, typename Parameter>
ReturnType Callback<Object, ReturnType, Parameter>::execute(Parameter parameter)
{
    return operator()(parameter);
}
#endif // CALLBACK_H


