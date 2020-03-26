package com.dongkyoo.equations;

import java.util.ArrayList;

public class Equations extends ArrayList<Equation> {

    private int varCount;

    public Equations(int varCount) {
        if (varCount > Equation.MAX_VARIABLE_NUM)
            throw new IllegalArgumentException("최대 " + Equation.MAX_VARIABLE_NUM + "개의 변수까지만 지정 가능합니다.");
        this.varCount = varCount;
    }

    public EquationResultList calculate() {
        EquationResultList resultManager = new EquationResultList(varCount);

        for (int i = 0; i < varCount; i++) {
            Equation anchor = findEquationHasVariable(i);
            if (anchor == null)
                continue;

            anchor.setCalculated(true);
            for (Equation equation : this) {
                if (equation.isCalculated() || !equation.hasVariable(i))
                    continue;

                double factor = equation.get(i) / anchor.get(i);
                equation.subtract(anchor.multiply(factor));

                if (equation.getVariableCount() == 1) {
                    int varIndex = equation.getFirstVariable();
                    equation.normalize();
                    resultManager.set(varIndex, equation.getValue());
                }
            }

            System.out.println(toString());
            resultManager.applyResult(this);
        }
        return resultManager;
    }

    private Equation findEquationHasVariable(int variableIndex) {
        for (Equation equation : this) {
            if (equation.isCalculated())
                continue;

            if (equation.hasVariable(variableIndex))
                return equation;
        }
        return null;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (Equation eq : this) {
            sb.append(eq.toString())
                    .append("\n");
        }
        return sb.toString();
    }
}
