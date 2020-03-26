package com.dongkyoo.equations;

import java.util.ArrayList;

public class Equation extends ArrayList<Double> {

    public static final int MAX_VARIABLE_NUM = 100;
    private int variableCount;
    private double value;
    private boolean isCalculated;

    public Equation() {
    }

    public Equation(int variableCount, double value, boolean isCalculated) {
        this.variableCount = variableCount;
        this.value = value;
        this.isCalculated = isCalculated;
    }

    public Equation(Equation equation) {
        this(equation.variableCount, equation.value, equation.isCalculated);
        for (Double d : equation) {
            add(d);
        }
    }

    @Override
    public boolean add(Double aDouble) {
        if (aDouble != 0)
            variableCount++;

        return super.add(aDouble);
    }

    @Override
    public Double set(int index, Double element) {
        if (get(index) != 0 && element == 0)
            variableCount--;
        else if (get(index) == 0 && element != 0)
            variableCount++;

        return super.set(index, element);
    }

    void normalize() {
        if (variableCount != 1)
            throw new IllegalStateException("남은 변수가 1개 일 때만 호출가능합니다.");

        int index = getFirstVariable();
        value = value / get(index);
        set(index, 1.);
    }

    int getVariableCount() {
        return variableCount;
    }

    public void setValue(double value) {
        this.value = value;
    }

    void setVariable(int index, double value) {
        this.value -= get(index) * value;
        set(index, 0.);
    }

    double getValue() {
        return value;
    }

    int getFirstVariable() {
        for (int i = 0; i < size(); i++) {
            if (get(i) != 0)
                return i;
        }
        return -1;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < size(); i++) {
            if (get(i) != 0) {
                sb.append(String.format("%.2f", get(i)))
                        .append("X")
                        .append(i + 1)
                        .append(" ");
            } else {
                sb.append("\t");
            }
        }
        sb.append("= ")
                .append(value);
        return sb.toString();
    }

    boolean hasVariable(int variableIndex) {
        return get(variableIndex) != 0;
    }

    boolean isCalculated() {
        return isCalculated;
    }

    void setCalculated(boolean calculated) {
        isCalculated = calculated;
    }

    void subtract(Equation equation) {
        for (int i = 0; i < size(); i++) {
            set(i, get(i) - equation.get(i));
        }
        value -= equation.value;
    }

    Equation multiply(double factor) {
        Equation equation = new Equation(this);
        for (int i = 0; i < size(); i++) {
            equation.set(i, get(i) * factor);
        }
        equation.value *= factor;
        return equation;
    }
}
