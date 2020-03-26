package com.dongkyoo;

import com.dongkyoo.equations.Equation;
import com.dongkyoo.equations.EquationResultList;
import com.dongkyoo.equations.Equations;

import java.util.Scanner;

/*
 3
 3 -6 7 3
 9 0 -5 3
 5 -8 6 -4
 */
public class Main {

    public static void main(String[] args) {
        int varCount;
        Scanner scanner = new Scanner(System.in);

        System.out.print("변수의 갯수를 입력하세요 : ");
        varCount = scanner.nextInt();
        Equations equations = new Equations(varCount);

        for (int i = 0; i < varCount; i++) {
            Equation equation = new Equation();

            System.out.println("방정식의 계수만을 입력하세요");
            System.out.println("예) 1X1 + 2X2 - 3X3 = 4  ->  1 2 -3 4");
            for (int j = 0; j < varCount; j++) {
                equation.add(scanner.nextDouble());
            }
            equation.setValue(scanner.nextDouble());
            equations.add(equation);
            System.out.println(equation);
        }

        EquationResultList result = equations.calculate();
        System.out.println(result.toString());
    }
}
