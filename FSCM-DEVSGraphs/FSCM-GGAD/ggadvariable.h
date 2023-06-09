#if !defined(__GGADVARIABLE_H__)
#define __GGADVARIABLE_H__

/** A std::map of variable values. The key is variable name. At init time the std::map should
    copied to the model instance dynamic state so each model would have
    its own variables. */
typedef std::map<std::string, GgadValue> GgadVariableValues;

#endif        //  #if !defined(__GGADVARIABLE_H__)

