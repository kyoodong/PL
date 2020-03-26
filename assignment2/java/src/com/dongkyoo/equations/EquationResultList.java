package com.dongkyoo.equations;

import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Queue;

public class EquationResultList extends ArrayList<Double> {

    private Queue<Integer> resultQueue;

    public EquationResultList(int varCount) {
        for (int i = 0; i <varCount; i++)
            add(0.);

        resultQueue = new ArrayDeque<>();
    }

    @Override
    public Double set(int index, Double element) {
        resultQueue.add(index);
        return super.set(index, element);
    }

    void applyResult(Equations equations) {
        while (!resultQueue.isEmpty()) {
            int varIndex = resultQueue.poll();

            for (Equation equation : equations) {
                equation.setVariable(varIndex, get(varIndex));

                if (equation.getVariableCount() == 1) {
                    int varIndex2 = equation.getFirstVariable();
                    if (get(varIndex2) == 0) {
                        equation.normalize();
                        set(varIndex2, equation.getValue());
                    }
                }
            }
        }
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < size(); i++) {
            sb.append("X")
                    .append(i + 1)
                    .append(" = ")
                    .append(String.format("%.2f", get(i)))
                    .append("\n");
        }
        return sb.toString();
    }
}
