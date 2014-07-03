#ifndef FWCALLBACK_H
#define FWCALLBACK_H

template <class Object, typename ReturnType, typename Parameter>
class FWCallBack
{
private:
    typedef ReturnType (Object::*Method)(Parameter);
    Object *class_instance;
    Method method;
public:
    FWCallBack(Object *_class_instance, Method _method);
    ReturnType operator () (Parameter parameter);
    ReturnType execute(Parameter parameter);
};

template <class Object, typename ReturnType, typename Parameter>
FWCallBack<Object, ReturnType, Parameter>::FWCallBack(Object *_class_instance, Method _method) :
    class_instance(_class_instance),
    method(_method)
{
}

template <class Object, typename ReturnType, typename Parameter>
ReturnType FWCallBack<Object, ReturnType, Parameter>::operator () (Parameter parameter)
{
    if (class_instance)
        return (class_instance->*method)(parameter);
    else /* Will this cause a crash */
    {
        ReturnType ret = 0;
        return ret;
    }
}


template <class Object, typename ReturnType, typename Parameter>
ReturnType FWCallBack<Object, ReturnType, Parameter>::execute(Parameter parameter)
{
    return operator()(parameter);
}
#endif // CALLBACK_H


