#ifndef IGLOO_OROPERATOR_H
#define IGLOO_OROPERATOR_H

namespace igloo {
  
  struct OrOperator : public ConstraintOperator
  {
    template <typename ConstraintListType, typename ActualType>
    void Evaluate(ConstraintListType& list, ResultStack& result, OperatorStack& operators, const ActualType& actual)
    {
      EvaluateOperatorsWithLessOrEqualPrecedence(operators, result); 
      
      operators.push(this);
      
      EvaluateConstraintList(list.m_tail, result, operators, actual);
    }
    
    void PerformOperation(ResultStack& result)
    {
      bool right = result.top();
      result.pop();
      bool left = result.top();
      result.pop();
      
      result.push(left || right);
    }
    
    int Precedence()
    {
      return 4;
    }
  };
  
  inline std::string Stringize(const OrOperator&)
  {
    return "or";
  }
  
}
#endif